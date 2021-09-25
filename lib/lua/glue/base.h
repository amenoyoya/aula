#pragma once

#include "../../core/base/object.h"

namespace Aula {
    inline void registerBaseLibrary(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        
        aula.new_usertype<Object>(
            "Object",
            sol::constructors<Object()>(),
            "getState", &Object::getState,
            "getMessage", &Object::getMessage
        );

        aula["Object"].get_or_create<sol::table>().new_enum("State",
            "NONE", Object::State::NONE,
            "ACTIVE", Object::State::ACTIVE,
            "FAILED", Object::State::FAILED,
            "FINISHED", Object::State::FINISHED,
            "BUSY", Object::State::BUSY
        );
    }
}