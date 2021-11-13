#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#define SOL_ALL_SAFETIES_ON 1
#define SOL_LUAJIT 1
#include <sol/sol.hpp>

#ifdef _MSC_VER
    #pragma comment(lib, "lua51.lib")
#endif

enum person_sex_enum {
    male, female
};

struct person_t {
    std::string name;
    person_sex_enum sex;
    unsigned long age;
};

inline std::unique_ptr<person_t> new_person(const std::string name, person_sex_enum sex, unsigned long age) {
    return std::unique_ptr<person_t>(new person_t {
        name, sex, age
    });
}

inline std::string person_sex(person_t *self) {
    switch (self->sex) {
    case person_sex_enum::male:
        return "male";
    case person_sex_enum::female:
        return "female";
    default:
        return "unknown";
    }
}

inline void person_hello(person_t *self) {
    printf("Hello, I'm %s.\n\tsex: %s\n\tage: %d\n", self->name.c_str(), person_sex(self).c_str(), self->age);
}

// // * if you delete unique_ptr explicitly, program will be crashed
// inline void delete_person(person_t *self) {
//     if (self) {
//         delete self;
//         self = nullptr;
//     }
// }

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
    auto john = new_person("John Doe", person_sex_enum::male, 25);
    
    // unique_ptr::get(): get raw pointer to borrow the ownership
    person_hello(john.get());
    
    // delete_person(john.get()); // --> will be crashed because delete_person() does not the ownership

    /*** Lua test ***/
    sol::state lua;

    lua.new_enum("person_sex_enum",
        "male", person_sex_enum::male,
        "female", person_sex_enum::female
    );
    lua.new_usertype<person_t>("person_t",
        "name", &person_t::name,
        "sex", &person_t::sex,
        "age", &person_t::age,
        "hello", person_hello
    );
    lua.set_function("new_person", new_person);
    lua.script("local jane = new_person('Jane Doe', person_sex_enum.female, 18); jane:hello()");

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