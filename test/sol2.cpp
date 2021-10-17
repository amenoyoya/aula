#define SOL_ALL_SAFETIES_ON 1
#define SOL_LUAJIT 1
#include <sol/sol.hpp>

typedef long i32;

class Test {
public:
    Test(): val(0) {}
    explicit Test(i32 value): val(value) {}
    ~Test() {
        printf("closed the test object\n");
    }

    void print() {
        printf("value: %ld\n", val);
    }
    const i32 &value() const { return val; }
    Test *value(i32 _val) { val = _val; return this; }
private:
    i32 val;
};

int main() {
    sol::state lua;

    lua.new_usertype<Test>("Test",
        sol::constructors<
            Test(),
            Test(i32)
        >(),
        "print", &Test::print,
        "value", sol::overload(
            [](Test *self) { return self->value(); },
            [](Test *self, i32 val) { return self->value(val); }
        )
    );
    lua.script("local test = Test.new(100); test:value(test:value() + 1); test:print()");
    return 0;
}