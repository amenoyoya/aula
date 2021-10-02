local f, err = loadfile(__dir() .. "/../loadsample/bufsample.sym")
if f == nil then
    error(err)
end

print "✅ OK: loadfile = load(Aula.IO.readFile:toString)"
f()

print "✅ OK: debug.debug = Aula.Lua.dotty"
debug.debug("test program debug.debug")
