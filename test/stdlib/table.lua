--- table serializer
local tbl = {
    test = [==[
Hello,
"World"]==],
    {
        1, 2, "\t\a\b"
    }
}

local serialized = table.serialize(tbl, 0, true)
assert(serialized == '{{1,2,"\\t\\u0007\\b"},["test"]="Hello,\\n\\"World\\""}')

serialized = table.serialize(tbl, 2, true)
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


--- new class 'App' definition
local App = class {
    constructor = function(self, id)
        self.id = 0
        self.map = {}
        self:setID(id)
    end,
    destructor = function(self)
        self.map = {}
        print "✅ OK: class App.destructor called"
    end,
    operator = {
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


--- App extended class 'MyApp' definition
local MyApp = class(App) {
    constructor = function(self, ...)
        -- call parent constructor
        App.constructor(self, ...)
    end,
    
    setID = function(self, id)
        -- overrided parent method must be called directly
        App.setID(self, (id or 0) * 5)
    end
}

local myapp = MyApp.new(100)
assert(myapp:getID() == 500)
printf("✅ OK: class MyApp extend App\n\tgetID: %d\n", myapp:getID())
