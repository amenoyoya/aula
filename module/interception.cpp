#include "../lib/lua.hpp"
#include "interception.hpp"

extern "C" {
    #include "interception/library/interception.c"

    __declspec(dllexport) int luaopen_interception(lua_State *L) {
        sol::state_view lua(L);

        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto interception = aula["Interception"].get_or_create<sol::table>();

        interception.new_enum("ProcessPriority",
            "IDLE", Aula::Interception::ProcessPriority::IDLE,
            "BELOW_NORMAL", Aula::Interception::ProcessPriority::BELOW_NORMAL,
            "NORMAL", Aula::Interception::ProcessPriority::NORMAL,
            "ABOVE_NORMAL", Aula::Interception::ProcessPriority::ABOVE_NORMAL,
            "HIGH", Aula::Interception::ProcessPriority::HIGH,
            "REALTIME", Aula::Interception::ProcessPriority::REALTIME
        );
        
        interception.set_function("setCurrentProcessPriority", Aula::Interception::setCurrentProcessPriority);

        interception["KEY_DOWN"] = INTERCEPTION_KEY_DOWN;
        interception["KEY_UP"] = INTERCEPTION_KEY_UP;
        interception["KEY_E0"] = INTERCEPTION_KEY_E0;
        interception["KEY_E1"] = INTERCEPTION_KEY_E1;
        interception["KEY_TERMSRV_SET_LED"] = INTERCEPTION_KEY_TERMSRV_SET_LED;
        interception["KEY_TERMSRV_SHADOW"] = INTERCEPTION_KEY_TERMSRV_SHADOW;
        interception["KEY_TERMSRV_VKPACKET"] = INTERCEPTION_KEY_TERMSRV_VKPACKET;
        interception["FILTER_KEY_NONE"] = INTERCEPTION_FILTER_KEY_NONE;
        interception["FILTER_KEY_ALL"] = INTERCEPTION_FILTER_KEY_ALL;
        interception["FILTER_KEY_DOWN"] = INTERCEPTION_FILTER_KEY_DOWN;
        interception["FILTER_KEY_UP"] = INTERCEPTION_FILTER_KEY_UP;
        interception["FILTER_KEY_E0"] = INTERCEPTION_FILTER_KEY_E0;
        interception["FILTER_KEY_E1"] = INTERCEPTION_FILTER_KEY_E1;
        interception["FILTER_KEY_TERMSRV_SET_LED"] = INTERCEPTION_FILTER_KEY_TERMSRV_SET_LED;
        interception["FILTER_KEY_TERMSRV_SHADOW"] = INTERCEPTION_FILTER_KEY_TERMSRV_SHADOW;
        interception["FILTER_KEY_TERMSRV_VKPACKET"] = INTERCEPTION_FILTER_KEY_TERMSRV_VKPACKET;
        interception["MOUSE_LEFT_BUTTON_DOWN"] = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN;
        interception["MOUSE_LEFT_BUTTON_UP"] = INTERCEPTION_MOUSE_LEFT_BUTTON_UP;
        interception["MOUSE_RIGHT_BUTTON_DOWN"] = INTERCEPTION_MOUSE_RIGHT_BUTTON_DOWN;
        interception["MOUSE_RIGHT_BUTTON_UP"] = INTERCEPTION_MOUSE_RIGHT_BUTTON_UP;
        interception["MOUSE_MIDDLE_BUTTON_DOWN"] = INTERCEPTION_MOUSE_MIDDLE_BUTTON_DOWN;
        interception["MOUSE_MIDDLE_BUTTON_UP"] = INTERCEPTION_MOUSE_MIDDLE_BUTTON_UP;
        interception["MOUSE_BUTTON_1_DOWN"] = INTERCEPTION_MOUSE_BUTTON_1_DOWN;
        interception["MOUSE_BUTTON_1_UP"] = INTERCEPTION_MOUSE_BUTTON_1_UP;
        interception["MOUSE_BUTTON_2_DOWN"] = INTERCEPTION_MOUSE_BUTTON_2_DOWN;
        interception["MOUSE_BUTTON_2_UP"] = INTERCEPTION_MOUSE_BUTTON_2_UP;
        interception["MOUSE_BUTTON_3_DOWN"] = INTERCEPTION_MOUSE_BUTTON_3_DOWN;
        interception["MOUSE_BUTTON_3_UP"] = INTERCEPTION_MOUSE_BUTTON_3_UP;
        interception["MOUSE_BUTTON_4_DOWN"] = INTERCEPTION_MOUSE_BUTTON_4_DOWN;
        interception["MOUSE_BUTTON_4_UP"] = INTERCEPTION_MOUSE_BUTTON_4_UP;
        interception["MOUSE_BUTTON_5_DOWN"] = INTERCEPTION_MOUSE_BUTTON_5_DOWN;
        interception["MOUSE_BUTTON_5_UP"] = INTERCEPTION_MOUSE_BUTTON_5_UP;
        interception["MOUSE_WHEEL"] = INTERCEPTION_MOUSE_WHEEL;
        interception["MOUSE_HWHEEL"] = INTERCEPTION_MOUSE_HWHEEL;
        interception["FILTER_MOUSE_NONE"] = INTERCEPTION_FILTER_MOUSE_NONE;
        interception["FILTER_MOUSE_ALL"] = INTERCEPTION_FILTER_MOUSE_ALL;
        interception["FILTER_MOUSE_LEFT_BUTTON_DOWN"] = INTERCEPTION_FILTER_MOUSE_LEFT_BUTTON_DOWN;
        interception["FILTER_MOUSE_LEFT_BUTTON_UP"] = INTERCEPTION_FILTER_MOUSE_LEFT_BUTTON_UP;
        interception["FILTER_MOUSE_RIGHT_BUTTON_DOWN"] = INTERCEPTION_FILTER_MOUSE_RIGHT_BUTTON_DOWN;
        interception["FILTER_MOUSE_RIGHT_BUTTON_UP"] = INTERCEPTION_FILTER_MOUSE_RIGHT_BUTTON_UP;
        interception["FILTER_MOUSE_MIDDLE_BUTTON_DOWN"] = INTERCEPTION_FILTER_MOUSE_MIDDLE_BUTTON_DOWN;
        interception["FILTER_MOUSE_MIDDLE_BUTTON_UP"] = INTERCEPTION_FILTER_MOUSE_MIDDLE_BUTTON_UP;
        interception["FILTER_MOUSE_BUTTON_1_DOWN"] = INTERCEPTION_FILTER_MOUSE_BUTTON_1_DOWN;
        interception["FILTER_MOUSE_BUTTON_1_UP"] = INTERCEPTION_FILTER_MOUSE_BUTTON_1_UP;
        interception["FILTER_MOUSE_BUTTON_2_DOWN"] = INTERCEPTION_FILTER_MOUSE_BUTTON_2_DOWN;
        interception["FILTER_MOUSE_BUTTON_2_UP"] = INTERCEPTION_FILTER_MOUSE_BUTTON_2_UP;
        interception["FILTER_MOUSE_BUTTON_3_DOWN"] = INTERCEPTION_FILTER_MOUSE_BUTTON_3_DOWN;
        interception["FILTER_MOUSE_BUTTON_3_UP"] = INTERCEPTION_FILTER_MOUSE_BUTTON_3_UP;
        interception["FILTER_MOUSE_BUTTON_4_DOWN"] = INTERCEPTION_FILTER_MOUSE_BUTTON_4_DOWN;
        interception["FILTER_MOUSE_BUTTON_4_UP"] = INTERCEPTION_FILTER_MOUSE_BUTTON_4_UP;
        interception["FILTER_MOUSE_BUTTON_5_DOWN"] = INTERCEPTION_FILTER_MOUSE_BUTTON_5_DOWN;
        interception["FILTER_MOUSE_BUTTON_5_UP"] = INTERCEPTION_FILTER_MOUSE_BUTTON_5_UP;
        interception["FILTER_MOUSE_WHEEL"] = INTERCEPTION_FILTER_MOUSE_WHEEL;
        interception["FILTER_MOUSE_HWHEEL"] = INTERCEPTION_FILTER_MOUSE_HWHEEL;
        interception["FILTER_MOUSE_MOVE"] = INTERCEPTION_FILTER_MOUSE_MOVE;
        interception["MOUSE_MOVE_RELATIVE"] = INTERCEPTION_MOUSE_MOVE_RELATIVE;
        interception["MOUSE_MOVE_ABSOLUTE"] = INTERCEPTION_MOUSE_MOVE_ABSOLUTE;
        interception["MOUSE_VIRTUAL_DESKTOP"] = INTERCEPTION_MOUSE_VIRTUAL_DESKTOP;
        interception["MOUSE_ATTRIBUTES_CHANGED"] = INTERCEPTION_MOUSE_ATTRIBUTES_CHANGED;
        interception["MOUSE_MOVE_NOCOALESCE"] = INTERCEPTION_MOUSE_MOVE_NOCOALESCE;
        interception["MOUSE_TERMSRV_SRC_SHADOW"] = INTERCEPTION_MOUSE_TERMSRV_SRC_SHADOW;

        interception.new_usertype<InterceptionMouseStroke>("MouseStroke",
            "state", &InterceptionMouseStroke::state,
            "flags", &InterceptionMouseStroke::flags,
            "rolling", &InterceptionMouseStroke::rolling,
            "x", &InterceptionMouseStroke::x,
            "y", &InterceptionMouseStroke::y,
            "information", &InterceptionMouseStroke::information
        );
        interception.new_usertype<InterceptionKeyStroke>("KeyStroke",
            "code", &InterceptionKeyStroke::code,
            "state", &InterceptionKeyStroke::state,
            "information", &InterceptionKeyStroke::information
        );

        interception.new_usertype<Aula::Interception::Device>("Device",
            "index", &Aula::Interception::Device::index,
            "hardwareId", &Aula::Interception::Device::hardwareId,
            "isKeyboard", &Aula::Interception::Device::isKeyboard,
            "isMouse", &Aula::Interception::Device::isMouse
        );

        interception.new_usertype<Aula::Interception::Context>("Context",
            sol::constructors<
                Aula::Interception::Context()
            >(),
            "getState", &Aula::Interception::Context::getState,
            "getMessage", &Aula::Interception::Context::getMessage,
            "open", &Aula::Interception::Context::open,
            "close", &Aula::Interception::Context::close,
            "enumerateDevices", &Aula::Interception::Context::enumerateDevices,
            "setKeyboardFilter", &Aula::Interception::Context::setKeyboardFilter,
            "setMouseFilter", &Aula::Interception::Context::setMouseFilter,
            "recieve", &Aula::Interception::Context::recieve,
            "pass", &Aula::Interception::Context::pass,
            "getCurrentKeyStroke", &Aula::Interception::Context::getCurrentKeyStroke,
            "getCurrentMouseStroke", &Aula::Interception::Context::getCurrentMouseStroke,
            "getCurrentDeviceIndex", &Aula::Interception::Context::getCurrentDeviceIndex,
            "getHardwareId", sol::overload(
                [](Aula::Interception::Context *self, unsigned long deviceIndex) { return self->getHardwareId(deviceIndex); },
                [](Aula::Interception::Context *self) { return self->getHardwareId(); }
            )
        );

        return 0;
    }
}