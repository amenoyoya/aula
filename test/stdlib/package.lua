local f, err = loadfile(package.__dir .. "/../loadsample/bufsample.sym")
if f == nil then
    error(err)
end

print "✅ OK: loadfile = load(Aula.IO.readFile:toString)"
f()
