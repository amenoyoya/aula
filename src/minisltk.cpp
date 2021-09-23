#include "../sltk3/engine.h"

using namespace Sltk;

__main(){
	lua_State *L = Engine::create();
	if(argc > 1){
		if(1 != Engine::load(L, Encoding::toUTF8(argv[1])) || !Engine::call(L, 0, 0)){
			if(lua_type(L, -1) != LUA_TSTRING) lua_pushstring(L, "Argument[1] is not Script File.");
			Engine::processError(L);
		}
	}
	Engine::release(L);
	return 0;
}
