--- UTF-8文字列ライブラリ ---

--[=[
・utf8.escape(str) -> utf8 string
    escape a str to UTF-8 format string.
・utf8.charpos(s[[, charpos], offset]) -> charpos, code point
    convert UTF-8 position to byte offset. if only offset is given, return byte offset of this UTF-8 char index. if charpos and offset is given, a new charpos will calculate, by add/subtract UTF-8 char offset to current charpos. in all case, it return a new char position, and code point (a number) at this position.
・utf8.next(s[, charpos[, offset]]) -> charpos, code point
    iterate though the UTF-8 string s. If only s is given, it can used as a iterator:
        for pos, code in utf8.next, "utf8-string" 
・utf8.width(s[, ambi_is_double[, default_width]]) -> width
    calculate the width of UTF-8 string s. if ambi_is_double is given, the ambiguous width character's width is 2, otherwise it's 1. fullwidth/doublewidth character's width is 2, and other character's width is 1. if default_width is given, it will be the width of unprintable character, used display a non-character mark for these characters. if s is a code point, return the width of this code point.
・utf8.widthindex(s, location[, ambi_is_double[, default_width]]) -> idx, offset, width
    return the character index at given location in string s. this is a reverse operation of utf8.width(). this function return a index of location, and a offset in in UTF-8 encoding. e.g. if cursor is at the second column (middle) of the wide char, offset will be 2. the width of character at idx is returned, also.
・utf8.title(s) -> new_string
・utf8.fold(s) -> new_string
    convert UTF-8 string s to title-case, or folded case used to compare by ignore case. if s is a number, it's treat as a code point and return a convert code point (number). utf8.lower/utf8.upper has the same extension.
・utf8.ncasecmp(a, b) -> [-1,0,1]
    compare a and b without case, -1 means a < b, 0 means a == b and 1 means a > b.
]=]

-- i～jのUTF8文字コードを取得
function string:u8byte(i, j)
    return utf8.byte(self, i, j)
end

-- 数値からUTF8文字を作成
function string:u8char(...)
    return utf8.char(self, ...)
end

-- patternを探し、開始位置と終了位置のインデックスを返す
-- キャプチャが設定されていれば、3つ目以降の戻り値に一致文字列が返る
-- selfparam init=1: 検索開始インデックス, plain=false: trueなら正規表現を使わない
function string:u8find(pattern, init, plain)
    return utf8.find(self, pattern, init, plain)
end

-- patternに一致する文字列を次々返すイテレータを返す(for文で使う)
function string:u8gmatch(pattern)
    return utf8.gmatch(self, pattern)
end

-- patternを全てrepl(string/table/function)に置き換える
-- selfparam n=nil: 置き換える回数(デフォルトは全て)
function string:u8gsub(pattern, repl, n)
    return utf8.gsub(self, pattern, repl, n)
end

-- 文字列の長さを取得
function string:u8len()
    return utf8.len(self)
end

-- 小文字変換
function string:u8lower()
    return utf8.lower(self)
end

-- patternに一致した部分文字列を返す
function string:u8match(pattern, init)
    return utf8.match(self, pattern, init)
end

-- 逆順文字列を返す
function string:u8reverse()
    return utf8.reverse(self)
end

-- i～jの部分文字列取得
function string:u8sub(i, j)
    return utf8.sub(self, i, j)
end

-- i番目からn文字分の部分文字列を取得
function string:u8substr(i, n)
    return utf8.sub(self, i, i-1 + (n or utf8.len(self)-i))
end

-- 大文字変換
function string:u8upper()
    return utf8.upper(self)
end

-- index(デフォルトは最後尾)の前にsubstringを挿入
function string:u8insert(index, substring)
    return utf8.insert(self, index, substring)
end

-- start(=-1)～stop(=-1)の部分文字列を削除
function string:u8remove(start, stop)
    return utf8.remove(self, start, stop)
end

-- 指定文字が何バイト文字か判定(戻り値: 1～4, nil=エラー)
function utf8.bsize(c)
    if c <= 0x7f then
        return 1
    elseif c >= 0xc2 and c <= 0xdf then
        return 2
    elseif c >= 0xe0 and c <= 0xef then
        return 3
    elseif c >= 0xf0 and c <= 0xf7 then
        return 4
    end
end

-- エンコーディング
function string:encode(toEnc, fromEnc)
    return Aula.Encoding.encode(self, toEnc, fromEnc or Aula.Encoding.Type.UNKNOWN)
end


-- UTF-8文字列出力関数
function println(...)
    local list = {...}
    local n = #list
    if n == 0 then
        Aula.IO.Stdout:write "nil"
    else
        Aula.IO.Stdout:write(tostring(list[1]), false)
        for i = 2, n do
            Aula.IO.Stdout:write("\t"..tostring(list[i]), false)
        end
        Aula.IO.Stdout:write "" -- \n
    end
end

function printf(format, ...)
    Aula.IO.Stdout:write(format:format(...), false)
end

-- コマンドラインから文字列を読み込む(UTF-8)
function readln(message)
    if type(message) == 'string' then
        Aula.IO.Stdout:write(message)
    end
    return io.read():u8encode()
end


--[[ 文字列拡張ライブラリ ]]--
-- 文字列strのini～finの部分を文字列replで置換
local function replaceString(str, ini, fin, repl)
    return str:sub(1, ini-1)..repl..str:sub(fin+1)
end

-- 文字列strのold文字列をnew文字列で置換
-- @param start: 検索開始インデックス(=1), usepatt: パターンマッチング使用するか(=false)
local function updateString(str, old, new, start, usepatt)
    local ini, fin = str:find(old, start or 1, not (usepatt))
    if ini and fin then return replaceString(str, ini, fin, new) end
    return str
end

function string:replace(var1, var2, var3, var4)
    if type(var1) == 'number' and type(var2) == 'number' then
        return replaceString(self, var1, var2, var3)
    elseif type(var1) == 'string' then
        return updateString(self, var1, var2, var3, var4)
    else
        error("function 'string.replace' requires arguments\n"
            .."(string, number, number, string)\n\tor\n(string, string, string [,number, boolean])")
    end
end

-- UTF-8用replace
local function replaceUTF8String(str, ini, fin, repl)
    return str:u8sub(1, ini-1)..repl..str:u8sub(fin+1)
end

local function updateUTF8String(str, old, new, start, usepatt)
    local ini, fin = str:u8find(old, start or 1, not (usepatt))
    if ini and fin then return replaceString(str, ini, fin, new) end
    return str
end

function string:u8replace(var1, var2, var3, var4)
    if type(var1) == 'number' and type(var2) == 'number' then
        return replaceUTF8String(self, var1, var2, var3)
    elseif type(var1) == 'string' then
        return updateUTF8String(self, var1, var2, var3, var4)
    else
        error("function 'string.replace' requires arguments\n"
            .."(string, number, number, string)\n\tor\n(string, string, string [,number, boolean])")
    end
end

-- 大文字・小文字を無視して文字列比較
function string:equal(str, len)
    return Aula.String.isEqualFold(self, str, len or -1)
end
