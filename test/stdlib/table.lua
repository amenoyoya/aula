print("❤❤❤ test for table library ❤❤❤")

--- テーブルシリアライズ
local tbl = {
    test = [==[
Hello,
"World"]==],
    {
        1, 2, "\t\a\b"
    }
}

local serialized = table.serialize(tbl)
assert(serialized == '{{1,2,"\\t\\u0007\\b"},["test"]="Hello,\\n\\"World\\""}')

serialized = table.serialize(tbl, 2)
assert(serialized == [==[
{
  {
    1,
    2,
    "\t\u0007\b"
  },
  ["test"]="Hello,\n\"World\""
}]==])
printf("✅ OK table.serialize\n%s\n", serialized)


--- 新規クラス'App'作成
local App = class {
    constructor = function(self, id) -- コンストラクタ
        -- classメンバはコンストラクタで宣言する
        self.id = 0
        self.map = {}
        self:setID(id)
    end,
    destructor = function(self) -- デストラクタ
        self.map = {}
        print "✅ OK: class App.destructor called"
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
assert(app:getID() == 100)
assert(app[1] == "Hello")

printf("✅ OK: class App\n\tgetID: %d\n\t[1]: %s\n", app:getID(), app[1])

app = nil
collectgarbage "collect" --> "✅ OK: class App.destructor called"


--- クラス'App'を継承して'MyApp'クラス作成
local MyApp = class(App) {
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
assert(myapp:getID() == 500)
printf("✅ OK: class MyApp extend App\n\tgetID: %d\n", myapp:getID())

print ""
