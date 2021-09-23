#ifdef _WINDOWS
	#define _UseWin32Engine
	#define SHOW_VERSION() Win32::showMessageBox(info, "SeleneTalk ver. " VERSION_STR)
#else
	#define SHOW_VERSION() Console::writeLine(info);
#endif

#include "../sltk3/engine.h"
#include "version.h"

/*#ifdef _WindowsSystem
	#pragma comment(linker, "/subsystem:\"windows\" /entry:\"wmainCRTStartup\"")
#endif*/

using namespace Sltk;

static char startup_lib[] = {
	#include "startuplib/Startup.cpp"
};

// Usage: SeleneTalk [-s "SelneTalkScript"] [-l "LuaScript"] "MainScript" ...
__main(){
	lua_State  *L = Engine::create();
	FileReader *pReader = Engine::getFileReader(L);
	string      sltk_script, lua_script;
	u8          eval = 0;
	s8          mode = -1;
	u32         nargs = 0;
	const char *info = "SeleneTalk ver. " VERSION_STR
		"\nA script engine based on the customized LuaJIT.\n\tCopyright (C) 2017 yoya.";
	
	#ifdef _UseWin32Engine
		// Win32���C�u�����iIE�R���|�[�l���g�j��o�^
		if(!Engine::registerWin32Library(L)) Engine::processError(L);
	#endif
	
	// os.argv[]�ň����擾�\��
	lua_getglobal(L, "os");
	lua_createtable(L, 0, 0);
	lua_pushstring(L, Path::complete(Encoding::toUTF8(argv[0])).c_str());
	lua_rawseti(L, -2, nargs++); // os.argv[0] �Ɏ��s�t�@�C���̃t���p�X�i�[
	
	// �R�}���h���C����������
	for(int i = 1; i < argc; ++i){
		if(eval == 1){ // -s �X�C�b�`��̈�����SeleneTalk�X�N���v�g�Ƃ��ēǂݍ���
			eval = 0;
			sltk_script.append(Encoding::toUTF8(argv[i]) + "\n");
		}else if(eval == 2){ // -l �X�C�b�`��̈�����Lua�X�N���v�g�Ƃ��ēǂݍ���
			eval = 0;
			lua_script.append(Encoding::toUTF8(argv[i]) + "\n");
		}else{
			if(wcscmp(argv[i], L"-s") == 0) eval = 1;
			else if(wcscmp(argv[i], L"-l") == 0) eval = 2;
			else{
				string arg = Encoding::toUTF8(argv[i]);
				if(mode >= 0){
					lua_pushstring(L, arg.c_str());
					lua_rawseti(L, -2, nargs++); // os.argv[] �Ɉ����ǉ�
				}else{
					if(-1 == (mode = Engine::load(L, arg, pReader))){
						lua_pushstring(L, arg.c_str());
						lua_rawseti(L, -2, nargs++); // os.argv[] �Ɉ����ǉ�
					}
				}
			}
		}
	}
	lua_setfield(L, -2, "argv"); // os.argv[] ����
	
	// ���C���X�N���v�g�������Ŏw�肳��Ȃ������ꍇ
	// Main.sltk(.lua, .sym)�t�@�C����Startup�f�B���N�g��(�A�[�J�C�u)�����[�h
	if(-1 == mode && -1 == (mode = Engine::load(L, System::getCurrentDirectory(), pReader))) mode = Engine::load(L, "Startup", pReader);
	
	/* �X�N���v�g���s */
	if(!Engine::loadScript(L, startup_lib, sizeof(startup_lib), "<SeleneTalk/Startup>")
		|| !Engine::call(L, 0, 0)) Engine::processError(L); // Startup�X�N���v�g���s
	if(sltk_script != ""){ // ����SelneTalk�X�N���v�g���s
		lua_sltkmode(1);
		if(!Engine::loadScript(L, sltk_script.c_str(), sltk_script.size(), "<SeleneTalk/Arguments/SeleneTalk>")
			|| !Engine::call(L, 0, 0)) Engine::processError(L);
	}
	if(lua_script != ""){ // ����Lua�X�N���v�g���s
		lua_sltkmode(0);
		if(!Engine::loadScript(L, lua_script.c_str(), lua_script.size(), "<SeleneTalk/Arguments/Lua>")
			|| !Engine::call(L, 0, 0)) Engine::processError(L);
	}
	if(mode >= 0 && (!Engine::loadScriptFile(L, pReader, mode)
		|| !Engine::call(L, 0, 0))) Engine::processError(L); // ���C���X�N���v�g���s
	if(mode < 0 && sltk_script == "" && lua_script == "") SHOW_VERSION(); // �X�N���v�g�������Ȃ���΃o�[�W�������\��
	Engine::release(L);
	return 0;
}
