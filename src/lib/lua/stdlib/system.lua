-- table print 時に serialize するかどうか
table.print_flag = true -- true: print(tbl) => table.serialize(tbl, 2, true)

-- UTF-8文字列出力関数
-- デフォルト print 関数を overload
function print(...)
    local list = {...}
    local n = #list
    if n == 0 then
        Aula.IO.Stdout:write "nil"
    else
        for i = 1, n do
            Aula.IO.Stdout:write(
                (i == 1 and "" or "\t") .. ((type(list[i]) == 'table' and table.print_flag) and table.serialize(list[i], 2, true) or tostring(list[i])),
                false
            )
        end
        Aula.IO.Stdout:write "" -- \n
    end
end

-- フォーマット付きUTF-8文字列出力
function printf(format, ...)
    Aula.IO.Stdout:write(format:format(...), false)
end

-- フォーマット付きerror出力
function errorf(format, ...)
    return error(format:format(...))
end

-- コマンドラインから文字列を読み込む(UTF-8)
function readln(message, size)
    if type(message) == 'string' then
        Aula.IO.Stdout:write(message, false)
    end
    return Aula.IO.Stdin:readString(size or 1024)
end
