--- テーブル関連ライブラリ ---

-- 逆順ipairs
function rpairs(t)
    local it = function(t,i)
        i = i - 1
        local v = t[i]
        if v == nil then return v end
        return i, v
    end
    return it, t, #t + 1
end

-- テーブルにテーブルをコピーする
-- selfparam copytable[=false]: trueならテーブルを再帰的にコピー
-- selfprama overwrite[=nil]: (destKey)->(destAnotherKey, srcAnotherKey)
--        destに既にsrcのキーが存在する場合、
--       ・コピー先のキーdestAnotherKeyを指定
--       ・destAnotherKeyを指定しない場合、コピーをスキップ
--       ・コピー先の値を別名キーsrcAnotherKeyに退避する
function table.copy(src, dest, copytable, overwrite)
    local write = (type(overwrite) == 'function')
    
    if type(src) == 'table' and type(dest) == 'table' then
        for k, v in pairs(src) do
            if dest[k] ~= nil and write then -- コピー先に値が存在する場合の処理
                local key, esckey = overwrite(k)
                -- コピー先の値を退避
                if esckey then dest[esckey] = dest[k] end
                -- コピー先に値をコピー
                if key then
                    if type(v) == 'table' and copytable then
                        local meta = getmetatable(v)
                        
                        dest[key] = {}
                        table.copy(v, dest[key], copytable, overwrite)
                        if meta then
                            setmetatable(dest[key], meta)
                        end
                    else
                        dest[key] = v
                    end
                end
            else -- 単純コピー
                if type(v) == 'table' and copytable then
                    dest[k] = {}
                    table.copy(v, dest[k], copytable, overwrite)
                else
                    dest[k] = v
                end
            end
        end
    end
end

-- 値、テーブルのクローンを作る
function table:getclone()
    if type(self) == 'table' then
        local new = {}
        table.copy(self, new, true)
        return new
    else
        return self
    end
end


--- テーブルシリアライズ ---
local escape_char_map = {
    [ "\\" ] = "\\",
    [ "\"" ] = "\"",
    [ "\b" ] = "b",
    [ "\f" ] = "f",
    [ "\n" ] = "n",
    [ "\r" ] = "r",
    [ "\t" ] = "t",
}

local function escape_char(c)
    return "\\" .. (escape_char_map[c] or string.format("u%04x", c:u8byte()))
end

-- @private 文字列のエスケープシーケンスをエスケープ処理
local function escape_string(str)
    return str:u8gsub('[%z\1-\31\\"]', escape_char)
end

-- @private Luaの値を文字列化
-- @param {boolean} all: true なら関数やユーザデータも文字列化
local function value2str(v, all)
    local vt = type(v)
    
    if vt == 'nil' then
        return "nil"
    elseif vt == 'number' then
        return tostring(v)
    elseif vt == 'string' then
        return '"' .. escape_string(v) .. '"'
    elseif vt == 'boolean' then
        return tostring(v)
    elseif all then
        return tostring(v)
    end
end

-- @private Luaテーブルのフィールド部分を文字列化
-- if field is number: return ''
-- if field is not number: return '["$field"]='
local function field2str(v)
    if type(v) == 'number' then return "" end
    return '["' .. escape_string(v) .. '"]='
end

-- @private テーブルシリアライズ（基底）
-- @param {table} tbl
-- @param {boolean} all: true なら関数やユーザデータも文字列化
-- @param {number} space_count: テーブル階層のインデント幅
-- @param {string} space: テーブル階層の現在のインデント
local function serialize_table(tbl, all, space_count, space)
    local buf = ""
    local f, v = next(tbl, nil)
    local next_space = space

    if space_count > 0 then
        next_space = space .. (" "):rep(space_count)
    end
    
    while f do
        if type(v) == 'table' then
            if buf ~= "" then
                buf = buf .. "," .. next_space
            end
            buf = buf.. field2str(f) .. serialize_table(v, all, space_count, next_space)
        else
            local value = value2str(v, all)
            if value then
                if buf ~= "" then
                    buf = buf .. "," .. next_space
                end
                buf = buf .. field2str(f) .. value
            end
        end
        -- 次の要素
        f, v = next(tbl, f)
    end

    return '{' .. next_space .. buf .. space .. '}'
end

-- テーブルシリアライズ
-- @param {number} space_count (default: 0): テーブル階層のインデント幅
-- @param {boolean} all (default: false): true なら関数やユーザデータも文字列化
function table:serialize(space_count, all)
    if type(self) ~= 'table' then
        return value2str(self, all) -- not table
    end

    space_count = space_count == nil and 0 or space_count
    all = all or false
    return serialize_table(self, all, space_count, space_count > 0 and "\n" or "")
end


--- クラス定義関数 ---

--[[
-- 新規クラス'App'作成
App = class {
    constructor = function(self, id) -- コンストラクタ
        -- classメンバはコンストラクタで宣言する
        self.id = 0
        self.map = {}
        self:setID(id)
    end,
    destructor = function(self) -- デストラクタ
        self.map = {}
        print "See you..."
    end,
    operator = { -- 演算子定義
        __newindex = function(self, index, val) self.map[index] = val end,
        __index = function(self, index) return self.map[index]  end,
    },
    getID = function(self) return self.id end,
    setID = function(self, id) self.id = id or 0 end,
}

local app = App.new(100)
app[1] = "Hello"
print(app:getID()) --> 100
print(app[1]) --> "Hello"
app = nil
collectgarbage "collect" --> "See you..."

-- クラス'App'を継承して'MyApp'クラス作成
MyApp = class(App) {
    constructor = function(self, ...)
        -- コンストラクタで親クラスのコンストラクタを呼ぶ
        App.constructor(self, ...)
    end,
    
    setID = function(self, id)
        -- オーバーライドした親クラスのメソッドは直接指定で呼び出す
        App.setID(self, (id or 0) * 5)
    end
}

local myapp = MyApp.new(100)
print(myapp:getID()) --> 500
--]]

local function createclass(define)
    define.new = function (...)
        local obj = table.getclone(define) -- インスタンス作成
        -- デストラクタ追加
        if type(obj.destructor) == 'function' then
            obj.__udata__ = newproxy(true)
            getmetatable(obj.__udata__).__gc = function()
                obj:destructor()
            end
        end
        -- コンストラクタ実行
        if type(obj.constructor) == 'function' then
            obj:constructor(...)
        end
        -- operatorテーブルをメタテーブルにセット
        if type(obj.operator) == 'table' then
            setmetatable(obj, obj.operator)
            obj.operator = nil
        end
        return obj
    end
    return define
end

function class(define)
    local extend = (type(define.__extend) == 'function') -- 継承するか
    -- 継承用関数定義
    define.__extend = function(child)
        table.copy(define, child, false, function(name) end) -- 子クラスに同名のメンバがある場合は，親メンバのコピーは行わない
        return createclass(child)
    end
    -- クラス定義
    if extend then
        return define.__extend -- 継承クラス定義
    else
        return createclass(define) -- 基底クラス定義
    end
end

--[[
    各演算子
    +:__add, -:__sub, *:__mul, /:__div, %:__mod, ^:__pow,
    ..(結合演算子):__concat, -(変数前のマイナス記号として):__unm,
    []: __index, []=: __newindex
    #(変数前の要素数取得記号として):__len, ==:__eq, <:__lt, <=:__le
]]


--- 名前空間をグローバル化 ---
-- @param overwrite[=nil]: (destKey)->(destAnotherKey, srcAnotherKey)
--        destに既にsrcのキーが存在する場合、
--        ・コピー先のキーdestAnotherKeyを指定
--        ・destAnotherKeyを指定しない場合、コピーをスキップ
--        ・コピー先の値を別名キーsrcAnotherKeyに退避
--         するための関数
function using(namespace, overwrite)
    table.copy(namespace, _G, false, overwrite)
end
