--- LPeg (Parsing Expression Grammar for Lua)
lpeg = require "lpeg"

-- lpegテーブルに以下の文字クラスを追加
-- * alnum  : アルファベット + 数字
-- * alpha  : アルファベット
-- * cntrl  : 制御文字
-- * digit  : 10進数の数字
-- * graph  : 表示文字(空白、改行を除く)
-- * lower  : 小文字アルファベット
-- * print  : 表示文字(改行を除く)
-- * punct  : 区切り文字
-- * space  : 空白文字
-- * upper  : 大文字アルファベット
-- * xdigit : 16進数の数字
lpeg.locale(lpeg)
lpeg.crlf = lpeg.P"\r"^-1 * lpeg.P"\n" + lpeg.P"\r"
lpeg.utf8 =   lpeg.R"\0\127"                                                            -- 1バイト文字
            + lpeg.R"\194\223" * lpeg.R"\128\191"                                       -- 2バイト文字
            + lpeg.R"\224\239" * lpeg.R"\128\191" * lpeg.R"\128\191"                    -- 3バイト文字
            + lpeg.R"\224\239" * lpeg.R"\128\191" * lpeg.R"\128\191" * lpeg.R"\128\191" -- 4バイト文字

--[[
    Balaced Parentheses (括弧などの囲み文字)にマッチングするパターン
    -- 囲み文字内部の文字列をキャプチャする --
    @param  head: 囲み文字の開始記号(パターン)  例: "("など
    @param  tail: 囲み文字の終了記号(パターン)  例: ")"など
    @option skip: 囲み文字の内部でスキップするパターンを指定  例: "..."のマッチングをする時 \" などはスキップする
    @option head_inner: 開始記号の直後のパターンを指定  例："<html>"などのタグにマッチングさせたい時に使う
    @option inner_tail: 終了記号の直前のパターンを指定
    @return: 囲み文字内部の文字列がキャプチャされるため，不要な場合は /0 する
--]]
lpeg.Bp = function(head, tail, skip, head_inner, inner_tail)
    head, tail = lpeg.P(head), lpeg.P(tail)
    local inner = skip and (skip + 1 - head - tail) or (1 - head - tail)
    
    if head_inner then
        head = head * head_inner
    end
    if inner_tail then
        tail = inner_tail * tail
    end
    return lpeg.P { head * lpeg.C((inner + lpeg.V(1))^0) * tail }
end

-- 引用符("..." や '...')にマッチングするパターン */
-- @option quotation: 引用符の記号    デフォルト: "
-- @return: 引用符内部の文字列がキャプチャされるため，不要な場合は /0 する
lpeg.Qs = function(quotation)
    local q = quotation or '"'
    return lpeg.Bp(q, q, lpeg.P'\\' * lpeg.P(q))
end

-- Luaのlong string [=*[...]=*] にマッチングするパターン
-- @return: long string内部の文字列がキャプチャされるため，不要な場合は /0 する
lpeg.Ls = function()
    local equals = lpeg.P"="^0
    local open = "[" * lpeg.Cg(equals, "LuaLongStringInit") * "[" * lpeg.P"\n"^-1
    local close = "]" * lpeg.C(equals) * "]"
    local closeeq = lpeg.Cmt(close * lpeg.Cb("LuaLongStringInit"), function(s, i, a, b) return a == b end)
    return open * lpeg.C((lpeg.P(1) - closeeq)^0) * close
end

-- 文頭以外でマッチングするパターン
-- @param pattern: LPegで作ったマッチパターン
lpeg.A = function(pattern)
    return lpeg.P{ pattern + 1 * lpeg.V(1) }
end

-- 文頭以外でマッチングする関数
-- @param  pattern: LPegで作ったマッチパターン
-- @param  subject: マッチング対象の文字列
-- @option init:    subjectのマッチング開始インデックス [=1]
lpeg.search = function(pattern, subject, init)
    return lpeg.A(pattern):match(subject, init)
end

-- 文字列分割関数
-- @param  sep: 区切り文字(文字列やLPegパターンなどを指定)
-- @param  subject: 分割する文字列
-- @option skip: 囲み文字の内部でスキップするパターンを指定
-- @return: 分割された文字列のテーブル
lpeg.split = function(sep, subject, skip)
    sep = lpeg.P(sep)
    local elem = skip and (skip + lpeg.C((1-sep)^0)) or lpeg.C((1-sep)^0)
    local p = lpeg.Ct(elem * (sep * elem)^0)
    return p:match(subject)
end

--[[
    1文字ずつ解析する関数
    -- ASTマクロの構文解析などに使う --
    @param  pattern: LPegで定義した文法
    @param  subject: 解析対象文字列
    @return: 解析完了後の文字列
    
    指定するpatternは，第1戻り値に次の解析位置を指定する必要がある
    第2戻り値を指定すれば，[一致位置]～[次の解析位置-1]の部分を指定文字列で置換できる
    （置換した場合次の解析位置は一致位置になる）
    （第3戻り値が指定されているならその位置を次の解析位置とする）
]]
lpeg.parse = function(pattern, subject)
    local cur, len = 1, subject:len()
    local p = lpeg.P(pattern) + lpeg.utf8
    
    while cur <= len do
        local fin, repl, next = p:match(subject, cur)
        
        if repl then -- 第2戻り値が指定された場合，ソース文字列を置換する
            subject = subject:replace(cur, fin-1, repl)
            len = subject:len()
            if next then -- 次の解析位置を一致位置以外にしたい場合
                cur = next
            end
        else
            cur = fin
        end
    end
    return subject
end

--[[
    -- オリジナルスクリプト作成サンプル --

-- command: "\msg(message)" -> Win32.showMessageBox(message)
-- macro: "@" -> "\msg", "#" -> "Hello"
local esc = false -- エスケープシーケンス フラグ

-- エスケープシーケンス処理
local function procESC(fin)
    if not (esc) then -- エスケープモードに入る場合，エスケープシーケンスは削除する
        esc = true
        return fin, ""
    else
        esc = false -- エスケープモード解除
        return fin
    end
end

-- MessageBox処理
local function procMSG(cur, message, fin)
    if esc then -- エスケープモードならMessageBox
        Win32.showMessageBox(message)
        return fin, "" -- コマンド文字列は削除
    else
        return cur+3 -- ()内の文字列に対しても処理を行いたいため，"msg"だけを飛ばす
    end
end

-- 一文字処理
local function procCHAR(c)
    esc = false -- エスケープモード解除
end

-- スクリプト文法
-- lpeg.Cp()はカレントポジションを返す
local grammar = (lpeg.P"\\" * lpeg.Cp() / procESC)
    + (lpeg.Cp() * "msg" * lpeg.space^0 * lpeg.Bp("(", ")") / 1 * lpeg.Cp() / procMSG)
    + (lpeg.utf8 / procCHAR)

-- マクロ定義
grammar = lpeg.P"@"*lpeg.Cp() / def(fin){ return fin, "\\msg" } -- "@" -> "\\msg"
    + lpeg.P"#"*lpeg.Cp() / def(fin){ return fin, "Hello" } -- "#" -> "Hello"
    + grammar

-- ソーススクリプト
local script = "#MessageBox:\\msg(Hello), NotMessageBox:\\msg(#), End:@(See, you)"

-- 解析実行
println(grammar:parse(script))
-- action --> Win32.showMessageBox"Hello", Win32.showMessageBox"See, you"
-- console --> "HelloMessageBox:, NotMessageBox:\msg(Hello), End:"
]]
