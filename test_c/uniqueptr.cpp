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

/*** unique_ptr test ***/
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

// unique_ptr::reset(): delete the resource explicitly
// => to call the reset function, borrow the mutable reference
inline void drop_person(std::unique_ptr<person_t> &self) {
    self.reset();
}


/*** unique_ptr custom deleter ***/
inline void custom_delete_person(person_t *person) {
    if (person) {
        printf("See you %s...\n", person->name.c_str());
        delete person;
        person = nullptr;
    }
}

inline std::unique_ptr<person_t, std::function<void(person_t*)>> custom_new_person(const std::string name, person_sex_enum sex, unsigned long age) {
    return std::unique_ptr<person_t, std::function<void(person_t*)>>(new person_t { name, sex, age}, custom_delete_person);
}

inline void custom_drop_person(std::unique_ptr<person_t, std::function<void(person_t*)>> &self) {
    self.reset();
}


/*** register class to lua test ***/
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

/*** main process ***/
int main() {
    auto john = new_person("John Doe", person_sex_enum::male, 25);
    // unique_ptr::get(): get raw pointer to borrow the ownership
    person_hello(john.get());
    // borrow the mutable reference and release the resource
    drop_person(john);

    auto jane = custom_new_person("Jane Doe", person_sex_enum::female, 18);
    person_hello(jane.get());
    custom_drop_person(jane); // => See you Jane Doe...

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
        "hello", person_hello,
        "drop", custom_drop_person
    );
    lua.set_function("new_person", new_person);
    lua.set_function("custom_new_person", custom_new_person);
    lua.script("local yoya = custom_new_person('Yoya Ameno', person_sex_enum.male, 33); yoya:hello(); yoya:drop()");

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