/*
** Lua binding: libAula_core
** Generated automatically by tolua++-1.0.93 on Thu Sep 23 19:49:59 2021.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_libAula_core_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Aula__Randomizer (lua_State* tolua_S)
{
 Aula::Randomizer* self = (Aula::Randomizer*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__ZipFileReader (lua_State* tolua_S)
{
 Aula::ZipFileReader* self = (Aula::ZipFileReader*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__FileEnumerator (lua_State* tolua_S)
{
 Aula::FileEnumerator* self = (Aula::FileEnumerator*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__File (lua_State* tolua_S)
{
 Aula::File* self = (Aula::File*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__ZipArchiver (lua_State* tolua_S)
{
 Aula::ZipArchiver* self = (Aula::ZipArchiver*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__FileReader (lua_State* tolua_S)
{
 Aula::FileReader* self = (Aula::FileReader*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__LibraryLoader (lua_State* tolua_S)
{
 Aula::LibraryLoader* self = (Aula::LibraryLoader*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__ZipFileInformation (lua_State* tolua_S)
{
 Aula::ZipFileInformation* self = (Aula::ZipFileInformation*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Aula__ZipGlobalInformation (lua_State* tolua_S)
{
 Aula::ZipGlobalInformation* self = (Aula::ZipGlobalInformation*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Aula::Randomizer");
 tolua_usertype(tolua_S,"Aula::ZipFileReader");
 tolua_usertype(tolua_S,"Aula::FileEnumerator");
 tolua_usertype(tolua_S,"Aula::File");
 tolua_usertype(tolua_S,"Aula::FileReader");
 tolua_usertype(tolua_S,"Aula::ZipArchiver");
 tolua_usertype(tolua_S,"Aula::ZipFileInformation::_DateTime");
 tolua_usertype(tolua_S,"Aula::ZipGlobalInformation");
 tolua_usertype(tolua_S,"Aula::LibraryLoader");
 tolua_usertype(tolua_S,"Aula::ZipFileInformation");
 tolua_usertype(tolua_S,"Aula::Object");
}

/* function: Aula::isSameString */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_isSameString00
static int tolua_libAula_core_Aula_isSameString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* s1 = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* s2 = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Aula::isSameString(s1,s2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSameString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::isSameString */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_isSameString01
static int tolua_libAula_core_Aula_isSameString01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* s1 = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* s2 = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned long len = (( unsigned long)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Aula::isSameString(s1,s2,len);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_isSameString00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Encoding::getName */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Encoding_getName00
static int tolua_libAula_core_Aula_Encoding_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* target = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Encoding::getName(target);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Encoding::isUTF8 */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Encoding_isUTF800
static int tolua_libAula_core_Aula_Encoding_isUTF800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const string target = ((const string)  tolua_tocppstring(tolua_S,1,0));
  {
    char tolua_ret = (  char)  Aula::Encoding::isUTF8(target);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)target);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isUTF8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Encoding::encode */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Encoding_encode00
static int tolua_libAula_core_Aula_Encoding_encode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* target = ((const char*)  tolua_tostring(tolua_S,1,0));
  unsigned char toEncoding = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char fromEncoding = (( unsigned char)  tolua_tonumber(tolua_S,3,Aula::Encoding::UNKNOWN));
  {
   string tolua_ret = (string)  Aula::Encoding::encode(target,toEncoding,fromEncoding);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'encode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Encoding::toUTF8 */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Encoding_toUTF800
static int tolua_libAula_core_Aula_Encoding_toUTF800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* target = ((const char*)  tolua_tostring(tolua_S,1,0));
  unsigned char fromEncoding = (( unsigned char)  tolua_tonumber(tolua_S,2,Aula::Encoding::UNKNOWN));
  {
   string tolua_ret = (string)  Aula::Encoding::toUTF8(target,fromEncoding);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toUTF8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Console::writeLine */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Console_writeLine00
static int tolua_libAula_core_Aula_Console_writeLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   Aula::Console::writeLine(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Console::write */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Console_write00
static int tolua_libAula_core_Aula_Console_write00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   Aula::Console::write(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'write'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Console::setAttribute */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Console_setAttribute00
static int tolua_libAula_core_Aula_Console_setAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   char wFore = ((  char)  tolua_tonumber(tolua_S,1,Aula::Console::WHITE));
   char wBlack = ((  char)  tolua_tonumber(tolua_S,2,Aula::Console::BLACK));
  bool bHigh = ((bool)  tolua_toboolean(tolua_S,3,false));
  bool bUnderscore = ((bool)  tolua_toboolean(tolua_S,4,false));
  {
   bool tolua_ret = (bool)  Aula::Console::setAttribute(wFore,wBlack,bHigh,bUnderscore);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Console::setCursorPosition */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Console_setCursorPosition00
static int tolua_libAula_core_Aula_Console_setCursorPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   short shXPos = ((  short)  tolua_tonumber(tolua_S,1,0));
   short shYPos = ((  short)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Aula::Console::setCursorPosition(shXPos,shYPos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCursorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Console::clear */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Console_clear00
static int tolua_libAula_core_Aula_Console_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  Aula::Console::clear();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Console::isKeyPressed */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Console_isKeyPressed00
static int tolua_libAula_core_Aula_Console_isKeyPressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  Aula::Console::isKeyPressed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isKeyPressed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Console::getPressedKey */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Console_getPressedKey00
static int tolua_libAula_core_Aula_Console_getPressedKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    long tolua_ret = (  long)  Aula::Console::getPressedKey();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPressedKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::System::execute */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_System_execute00
static int tolua_libAula_core_Aula_System_execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* cmd = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
    long tolua_ret = (  long)  Aula::System::execute(cmd);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'execute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::System::sleep */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_System_sleep00
static int tolua_libAula_core_Aula_System_sleep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long msec = (( unsigned long)  tolua_tonumber(tolua_S,1,0));
  {
   Aula::System::sleep(msec);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sleep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::System::getTime */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_System_getTime00
static int tolua_libAula_core_Aula_System_getTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned long tolua_ret = ( unsigned long)  Aula::System::getTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::System::setEnvironmentVariable */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_System_setEnvironmentVariable00
static int tolua_libAula_core_Aula_System_setEnvironmentVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* val = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Aula::System::setEnvironmentVariable(name,val);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnvironmentVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::System::getEnvironmentVariable */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_System_getEnvironmentVariable00
static int tolua_libAula_core_Aula_System_getEnvironmentVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::System::getEnvironmentVariable(name);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnvironmentVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::System::setCurrentDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_System_setCurrentDirectory00
static int tolua_libAula_core_Aula_System_setCurrentDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* dir = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Aula::System::setCurrentDirectory(dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurrentDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::System::getCurrentDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_System_getCurrentDirectory00
static int tolua_libAula_core_Aula_System_getCurrentDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   string tolua_ret = (string)  Aula::System::getCurrentDirectory();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::getState */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_getState00
static int tolua_libAula_core_Aula_getState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::Object* obj = ((Aula::Object*)  tolua_tousertype(tolua_S,1,0));
  {
   unsigned char tolua_ret = ( unsigned char)  Aula::getState(obj);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::getMessage */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_getMessage00
static int tolua_libAula_core_Aula_getMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::Object* obj = ((Aula::Object*)  tolua_tousertype(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::getMessage(obj);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::LibraryLoader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_LibraryLoader_new00
static int tolua_libAula_core_Aula_LibraryLoader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::LibraryLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::LibraryLoader* tolua_ret = (Aula::LibraryLoader*)  Mtolua_new((Aula::LibraryLoader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::LibraryLoader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::LibraryLoader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_LibraryLoader_new00_local
static int tolua_libAula_core_Aula_LibraryLoader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::LibraryLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::LibraryLoader* tolua_ret = (Aula::LibraryLoader*)  Mtolua_new((Aula::LibraryLoader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::LibraryLoader");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::LibraryLoader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_LibraryLoader_new01
static int tolua_libAula_core_Aula_LibraryLoader_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::LibraryLoader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Aula::LibraryLoader* tolua_ret = (Aula::LibraryLoader*)  Mtolua_new((Aula::LibraryLoader)(path));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::LibraryLoader");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_LibraryLoader_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::LibraryLoader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_LibraryLoader_new01_local
static int tolua_libAula_core_Aula_LibraryLoader_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::LibraryLoader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Aula::LibraryLoader* tolua_ret = (Aula::LibraryLoader*)  Mtolua_new((Aula::LibraryLoader)(path));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::LibraryLoader");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_LibraryLoader_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Aula::LibraryLoader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_LibraryLoader_delete00
static int tolua_libAula_core_Aula_LibraryLoader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::LibraryLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::LibraryLoader* self = (Aula::LibraryLoader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  Aula::LibraryLoader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_LibraryLoader_open00
static int tolua_libAula_core_Aula_LibraryLoader_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::LibraryLoader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::LibraryLoader* self = (Aula::LibraryLoader*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->open(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  Aula::LibraryLoader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_LibraryLoader_close00
static int tolua_libAula_core_Aula_LibraryLoader_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::LibraryLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::LibraryLoader* self = (Aula::LibraryLoader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_new00
static int tolua_libAula_core_Aula_Randomizer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::Randomizer* tolua_ret = (Aula::Randomizer*)  Mtolua_new((Aula::Randomizer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::Randomizer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_new00_local
static int tolua_libAula_core_Aula_Randomizer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::Randomizer* tolua_ret = (Aula::Randomizer*)  Mtolua_new((Aula::Randomizer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::Randomizer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_new01
static int tolua_libAula_core_Aula_Randomizer_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   long _seed = ((  long)  tolua_tonumber(tolua_S,2,0));
  {
   Aula::Randomizer* tolua_ret = (Aula::Randomizer*)  Mtolua_new((Aula::Randomizer)(_seed));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::Randomizer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_Randomizer_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_new01_local
static int tolua_libAula_core_Aula_Randomizer_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   long _seed = ((  long)  tolua_tonumber(tolua_S,2,0));
  {
   Aula::Randomizer* tolua_ret = (Aula::Randomizer*)  Mtolua_new((Aula::Randomizer)(_seed));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::Randomizer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_Randomizer_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_new02
static int tolua_libAula_core_Aula_Randomizer_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_istable(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   long seedsNum = ((  long)  tolua_tonumber(tolua_S,2,0));
#ifdef __cplusplus
   long* seeds = Mtolua_new_dim(long, seedsNum);
#else
   long* seeds = (long*) malloc((seedsNum)*sizeof(long));
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isnumberarray(tolua_S,3,seedsNum,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    int i;
    for(i=0; i<seedsNum;i++)
    seeds[i] = ((long)  tolua_tofieldnumber(tolua_S,3,i+1,0));
   }
  }
  {
   Aula::Randomizer* tolua_ret = (Aula::Randomizer*)  Mtolua_new((Aula::Randomizer)(seedsNum,seeds));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::Randomizer");
  }
  {
   int i;
   for(i=0; i<seedsNum;i++)
    tolua_pushfieldnumber(tolua_S,3,i+1,(lua_Number) seeds[i]);
  }
#ifdef __cplusplus
  Mtolua_delete_dim(seeds);
#else
  free(seeds);
#endif
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_Randomizer_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_new02_local
static int tolua_libAula_core_Aula_Randomizer_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_istable(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   long seedsNum = ((  long)  tolua_tonumber(tolua_S,2,0));
#ifdef __cplusplus
   long* seeds = Mtolua_new_dim(long, seedsNum);
#else
   long* seeds = (long*) malloc((seedsNum)*sizeof(long));
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isnumberarray(tolua_S,3,seedsNum,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    int i;
    for(i=0; i<seedsNum;i++)
    seeds[i] = ((long)  tolua_tofieldnumber(tolua_S,3,i+1,0));
   }
  }
  {
   Aula::Randomizer* tolua_ret = (Aula::Randomizer*)  Mtolua_new((Aula::Randomizer)(seedsNum,seeds));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::Randomizer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
  {
   int i;
   for(i=0; i<seedsNum;i++)
    tolua_pushfieldnumber(tolua_S,3,i+1,(lua_Number) seeds[i]);
  }
#ifdef __cplusplus
  Mtolua_delete_dim(seeds);
#else
  free(seeds);
#endif
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_Randomizer_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: seed of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_seed00
static int tolua_libAula_core_Aula_Randomizer_seed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::Randomizer* self = (Aula::Randomizer*)  tolua_tousertype(tolua_S,1,0);
   long _seed = ((  long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seed'", NULL);
#endif
  {
   self->seed(_seed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seed of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_seed01
static int tolua_libAula_core_Aula_Randomizer_seed01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_istable(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Aula::Randomizer* self = (Aula::Randomizer*)  tolua_tousertype(tolua_S,1,0);
   long seedsNum = ((  long)  tolua_tonumber(tolua_S,2,0));
#ifdef __cplusplus
   long* seeds = Mtolua_new_dim(long, seedsNum);
#else
   long* seeds = (long*) malloc((seedsNum)*sizeof(long));
#endif
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seed'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isnumberarray(tolua_S,3,seedsNum,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    int i;
    for(i=0; i<seedsNum;i++)
    seeds[i] = ((long)  tolua_tofieldnumber(tolua_S,3,i+1,0));
   }
  }
  {
   self->seed(seedsNum,seeds);
  }
  {
   int i;
   for(i=0; i<seedsNum;i++)
    tolua_pushfieldnumber(tolua_S,3,i+1,(lua_Number) seeds[i]);
  }
#ifdef __cplusplus
  Mtolua_delete_dim(seeds);
#else
  free(seeds);
#endif
 }
 return 0;
tolua_lerror:
 return tolua_libAula_core_Aula_Randomizer_seed00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_get00
static int tolua_libAula_core_Aula_Randomizer_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::Randomizer* self = (Aula::Randomizer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->get();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_get01
static int tolua_libAula_core_Aula_Randomizer_get01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Aula::Randomizer* self = (Aula::Randomizer*)  tolua_tousertype(tolua_S,1,0);
  unsigned long r = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->get(r);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_Randomizer_get00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  Aula::Randomizer */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Randomizer_get02
static int tolua_libAula_core_Aula_Randomizer_get02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::Randomizer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Aula::Randomizer* self = (Aula::Randomizer*)  tolua_tousertype(tolua_S,1,0);
   long min = ((  long)  tolua_tonumber(tolua_S,2,0));
   long max = ((  long)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'", NULL);
#endif
  {
    long tolua_ret = (  long)  self->get(min,max);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_Randomizer_get01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Engine::encodeDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Engine_encodeDirectory00
static int tolua_libAula_core_Aula_Engine_encodeDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* dirPath = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* outputFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,""));
  unsigned char level = (( unsigned char)  tolua_tonumber(tolua_S,4,6));
  {
   bool tolua_ret = (bool)  Aula::Engine::encodeDirectory(dirPath,outputFile,key,level);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'encodeDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::getLeaf */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_getLeaf00
static int tolua_libAula_core_Aula_Path_getLeaf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Path::getLeaf(path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeaf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::getStem */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_getStem00
static int tolua_libAula_core_Aula_Path_getStem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Path::getStem(path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::getExtension */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_getExtension00
static int tolua_libAula_core_Aula_Path_getExtension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Path::getExtension(path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getExtension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::convert */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_convert00
static int tolua_libAula_core_Aula_Path_convert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Path::convert(path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::isSame */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_isSame00
static int tolua_libAula_core_Aula_Path_isSame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path1 = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* path2 = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Aula::Path::isSame(path1,path2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::isSame */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_isSame01
static int tolua_libAula_core_Aula_Path_isSame01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* path1 = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* path2 = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned long len = (( unsigned long)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Aula::Path::isSame(path1,path2,len);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_Path_isSame00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::getParent */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_getParent00
static int tolua_libAula_core_Aula_Path_getParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  bool real = ((bool)  tolua_toboolean(tolua_S,2,true));
  {
   string tolua_ret = (string)  Aula::Path::getParent(path,real);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::isFile */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_isFile00
static int tolua_libAula_core_Aula_Path_isFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Aula::Path::isFile(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::isDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_isDirectory00
static int tolua_libAula_core_Aula_Path_isDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Aula::Path::isDirectory(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::complete */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_complete00
static int tolua_libAula_core_Aula_Path_complete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Path::complete(path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'complete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::appendSlash */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_appendSlash00
static int tolua_libAula_core_Aula_Path_appendSlash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Path::appendSlash(path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'appendSlash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::Path::removeSlash */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_Path_removeSlash00
static int tolua_libAula_core_Aula_Path_removeSlash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string path = ((string)  tolua_tocppstring(tolua_S,1,0));
  {
   string tolua_ret = (string)  Aula::Path::removeSlash(path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSlash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_new00
static int tolua_libAula_core_Aula_File_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::File* tolua_ret = (Aula::File*)  Mtolua_new((Aula::File)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::File");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_new00_local
static int tolua_libAula_core_Aula_File_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::File* tolua_ret = (Aula::File*)  Mtolua_new((Aula::File)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::File");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_new01
static int tolua_libAula_core_Aula_File_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* mode = ((const char*)  tolua_tostring(tolua_S,3,"r"));
  {
   Aula::File* tolua_ret = (Aula::File*)  Mtolua_new((Aula::File)(path,mode));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::File");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_File_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_new01_local
static int tolua_libAula_core_Aula_File_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* mode = ((const char*)  tolua_tostring(tolua_S,3,"r"));
  {
   Aula::File* tolua_ret = (Aula::File*)  Mtolua_new((Aula::File)(path,mode));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::File");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_File_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_new02
static int tolua_libAula_core_Aula_File_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long pFile = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
  unsigned char closeMode = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  {
   Aula::File* tolua_ret = (Aula::File*)  Mtolua_new((Aula::File)(pFile,closeMode));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::File");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_File_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_new02_local
static int tolua_libAula_core_Aula_File_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long pFile = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
  unsigned char closeMode = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  {
   Aula::File* tolua_ret = (Aula::File*)  Mtolua_new((Aula::File)(pFile,closeMode));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::File");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_File_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_delete00
static int tolua_libAula_core_Aula_File_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_open00
static int tolua_libAula_core_Aula_File_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* mode = ((const char*)  tolua_tostring(tolua_S,3,"r"));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->open(path,mode);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_open01
static int tolua_libAula_core_Aula_File_open01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
  unsigned long pFile = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
  unsigned char closeMode = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->open(pFile,closeMode);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_File_open00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_close00
static int tolua_libAula_core_Aula_File_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_getSize00
static int tolua_libAula_core_Aula_File_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readLine of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_readLine00
static int tolua_libAula_core_Aula_File_readLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readLine'", NULL);
#endif
  {
   string tolua_ret = (string)  self->readLine();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readChar of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_readChar00
static int tolua_libAula_core_Aula_File_readChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readChar'", NULL);
#endif
  {
    char tolua_ret = (  char)  self->readChar();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeLine of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_writeLine00
static int tolua_libAula_core_Aula_File_writeLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'writeLine'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->writeLine(text);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeChar of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_writeChar00
static int tolua_libAula_core_Aula_File_writeChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
   char c = ((  char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'writeChar'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->writeChar(c);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readAll of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_readAll00
static int tolua_libAula_core_Aula_File_readAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readAll'", NULL);
#endif
  {
   string tolua_ret = (string)  self->readAll();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seek of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_seek00
static int tolua_libAula_core_Aula_File_seek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
   long move = ((  long)  tolua_tonumber(tolua_S,2,0L));
  unsigned char from = (( unsigned char)  tolua_tonumber(tolua_S,3,SEEK_SET));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seek'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->seek(move,from);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_getPosition00
static int tolua_libAula_core_Aula_File_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getPosition();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: flush of class  Aula::File */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_File_flush00
static int tolua_libAula_core_Aula_File_flush00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::File* self = (Aula::File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'flush'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->flush();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'flush'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_new00
static int tolua_libAula_core_Aula_FileEnumerator_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::FileEnumerator* tolua_ret = (Aula::FileEnumerator*)  Mtolua_new((Aula::FileEnumerator)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileEnumerator");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_new00_local
static int tolua_libAula_core_Aula_FileEnumerator_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::FileEnumerator* tolua_ret = (Aula::FileEnumerator*)  Mtolua_new((Aula::FileEnumerator)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileEnumerator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_new01
static int tolua_libAula_core_Aula_FileEnumerator_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* dir = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Aula::FileEnumerator* tolua_ret = (Aula::FileEnumerator*)  Mtolua_new((Aula::FileEnumerator)(dir));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileEnumerator");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_FileEnumerator_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_new01_local
static int tolua_libAula_core_Aula_FileEnumerator_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* dir = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Aula::FileEnumerator* tolua_ret = (Aula::FileEnumerator*)  Mtolua_new((Aula::FileEnumerator)(dir));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileEnumerator");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_FileEnumerator_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_delete00
static int tolua_libAula_core_Aula_FileEnumerator_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileEnumerator* self = (Aula::FileEnumerator*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_open00
static int tolua_libAula_core_Aula_FileEnumerator_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileEnumerator* self = (Aula::FileEnumerator*)  tolua_tousertype(tolua_S,1,0);
  const char* dir = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->open(dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_close00
static int tolua_libAula_core_Aula_FileEnumerator_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileEnumerator* self = (Aula::FileEnumerator*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toNext of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_toNext00
static int tolua_libAula_core_Aula_FileEnumerator_toNext00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileEnumerator* self = (Aula::FileEnumerator*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toNext'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->toNext();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toNext'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_getName00
static int tolua_libAula_core_Aula_FileEnumerator_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::FileEnumerator* self = (const Aula::FileEnumerator*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPath of class  Aula::FileEnumerator */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileEnumerator_getPath00
static int tolua_libAula_core_Aula_FileEnumerator_getPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::FileEnumerator",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::FileEnumerator* self = (const Aula::FileEnumerator*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getPath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::copyFile */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_copyFile00
static int tolua_libAula_core_Aula_copyFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* src = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* dest = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool overwrite = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   bool tolua_ret = (bool)  Aula::copyFile(src,dest,overwrite);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'copyFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::removeFile */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_removeFile00
static int tolua_libAula_core_Aula_removeFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Aula::removeFile(file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::moveFile */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_moveFile00
static int tolua_libAula_core_Aula_moveFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* src = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* dest = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool overwrite = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   bool tolua_ret = (bool)  Aula::moveFile(src,dest,overwrite);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::createDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_createDirectory00
static int tolua_libAula_core_Aula_createDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* dir = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Aula::createDirectory(dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::copyDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_copyDirectory00
static int tolua_libAula_core_Aula_copyDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* src = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* dest = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Aula::copyDirectory(src,dest);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'copyDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::removeDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_removeDirectory00
static int tolua_libAula_core_Aula_removeDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* dir = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Aula::removeDirectory(dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::moveDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_moveDirectory00
static int tolua_libAula_core_Aula_moveDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* src = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* dest = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Aula::moveDirectory(src,dest);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: entries of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipGlobalInformation_unsigned_entries
static int tolua_get_Aula__ZipGlobalInformation_unsigned_entries(lua_State* tolua_S)
{
  Aula::ZipGlobalInformation* self = (Aula::ZipGlobalInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'entries'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->entries);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: entries of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipGlobalInformation_unsigned_entries
static int tolua_set_Aula__ZipGlobalInformation_unsigned_entries(lua_State* tolua_S)
{
  Aula::ZipGlobalInformation* self = (Aula::ZipGlobalInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'entries'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->entries = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: commentSize of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipGlobalInformation_unsigned_commentSize
static int tolua_get_Aula__ZipGlobalInformation_unsigned_commentSize(lua_State* tolua_S)
{
  Aula::ZipGlobalInformation* self = (Aula::ZipGlobalInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'commentSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->commentSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: commentSize of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipGlobalInformation_unsigned_commentSize
static int tolua_set_Aula__ZipGlobalInformation_unsigned_commentSize(lua_State* tolua_S)
{
  Aula::ZipGlobalInformation* self = (Aula::ZipGlobalInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'commentSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->commentSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: comment of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipGlobalInformation_comment
static int tolua_get_Aula__ZipGlobalInformation_comment(lua_State* tolua_S)
{
  Aula::ZipGlobalInformation* self = (Aula::ZipGlobalInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'comment'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->comment);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: comment of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipGlobalInformation_comment
static int tolua_set_Aula__ZipGlobalInformation_comment(lua_State* tolua_S)
{
  Aula::ZipGlobalInformation* self = (Aula::ZipGlobalInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'comment'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->comment = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipGlobalInformation_new00
static int tolua_libAula_core_Aula_ZipGlobalInformation_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipGlobalInformation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipGlobalInformation* tolua_ret = (Aula::ZipGlobalInformation*)  Mtolua_new((Aula::ZipGlobalInformation)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipGlobalInformation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::ZipGlobalInformation */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipGlobalInformation_new00_local
static int tolua_libAula_core_Aula_ZipGlobalInformation_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipGlobalInformation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipGlobalInformation* tolua_ret = (Aula::ZipGlobalInformation*)  Mtolua_new((Aula::ZipGlobalInformation)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipGlobalInformation");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: version of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_version
static int tolua_get_Aula__ZipFileInformation_unsigned_version(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'version'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->version);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: version of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_version
static int tolua_set_Aula__ZipFileInformation_unsigned_version(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'version'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->version = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: neededVersion of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_neededVersion
static int tolua_get_Aula__ZipFileInformation_unsigned_neededVersion(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'neededVersion'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->neededVersion);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: neededVersion of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_neededVersion
static int tolua_set_Aula__ZipFileInformation_unsigned_neededVersion(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'neededVersion'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->neededVersion = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: flag of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_flag
static int tolua_get_Aula__ZipFileInformation_unsigned_flag(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flag'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->flag);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: flag of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_flag
static int tolua_set_Aula__ZipFileInformation_unsigned_flag(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flag'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->flag = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: compressionMethod of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_compressionMethod
static int tolua_get_Aula__ZipFileInformation_unsigned_compressionMethod(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressionMethod'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->compressionMethod);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: compressionMethod of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_compressionMethod
static int tolua_set_Aula__ZipFileInformation_unsigned_compressionMethod(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressionMethod'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->compressionMethod = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dosDate of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_dosDate
static int tolua_get_Aula__ZipFileInformation_unsigned_dosDate(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dosDate'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->dosDate);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dosDate of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_dosDate
static int tolua_set_Aula__ZipFileInformation_unsigned_dosDate(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dosDate'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dosDate = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: crc of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_crc
static int tolua_get_Aula__ZipFileInformation_unsigned_crc(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'crc'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->crc);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: crc of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_crc
static int tolua_set_Aula__ZipFileInformation_unsigned_crc(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'crc'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->crc = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: compressedSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_compressedSize
static int tolua_get_Aula__ZipFileInformation_unsigned_compressedSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressedSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->compressedSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: compressedSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_compressedSize
static int tolua_set_Aula__ZipFileInformation_unsigned_compressedSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressedSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->compressedSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: uncompressedSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_uncompressedSize
static int tolua_get_Aula__ZipFileInformation_unsigned_uncompressedSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uncompressedSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->uncompressedSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uncompressedSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_uncompressedSize
static int tolua_set_Aula__ZipFileInformation_unsigned_uncompressedSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uncompressedSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uncompressedSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fileNameSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_fileNameSize
static int tolua_get_Aula__ZipFileInformation_unsigned_fileNameSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileNameSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fileNameSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fileNameSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_fileNameSize
static int tolua_set_Aula__ZipFileInformation_unsigned_fileNameSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileNameSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fileNameSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fileExtraSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_fileExtraSize
static int tolua_get_Aula__ZipFileInformation_unsigned_fileExtraSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileExtraSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fileExtraSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fileExtraSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_fileExtraSize
static int tolua_set_Aula__ZipFileInformation_unsigned_fileExtraSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileExtraSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fileExtraSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fileCommentSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_fileCommentSize
static int tolua_get_Aula__ZipFileInformation_unsigned_fileCommentSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileCommentSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fileCommentSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fileCommentSize of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_fileCommentSize
static int tolua_set_Aula__ZipFileInformation_unsigned_fileCommentSize(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileCommentSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fileCommentSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: diskNumStart of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_diskNumStart
static int tolua_get_Aula__ZipFileInformation_unsigned_diskNumStart(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'diskNumStart'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->diskNumStart);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: diskNumStart of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_diskNumStart
static int tolua_set_Aula__ZipFileInformation_unsigned_diskNumStart(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'diskNumStart'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->diskNumStart = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: internalFA of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_internalFA
static int tolua_get_Aula__ZipFileInformation_unsigned_internalFA(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'internalFA'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->internalFA);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: internalFA of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_internalFA
static int tolua_set_Aula__ZipFileInformation_unsigned_internalFA(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'internalFA'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->internalFA = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: externalFA of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_unsigned_externalFA
static int tolua_get_Aula__ZipFileInformation_unsigned_externalFA(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'externalFA'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->externalFA);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: externalFA of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_unsigned_externalFA
static int tolua_set_Aula__ZipFileInformation_unsigned_externalFA(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'externalFA'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->externalFA = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sec of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation___DateTime_unsigned_sec
static int tolua_get_Aula__ZipFileInformation___DateTime_unsigned_sec(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sec'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sec);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sec of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation___DateTime_unsigned_sec
static int tolua_set_Aula__ZipFileInformation___DateTime_unsigned_sec(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sec'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sec = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: min of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation___DateTime_unsigned_min
static int tolua_get_Aula__ZipFileInformation___DateTime_unsigned_min(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'min'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->min);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: min of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation___DateTime_unsigned_min
static int tolua_set_Aula__ZipFileInformation___DateTime_unsigned_min(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'min'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->min = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hour of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation___DateTime_unsigned_hour
static int tolua_get_Aula__ZipFileInformation___DateTime_unsigned_hour(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hour'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hour);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hour of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation___DateTime_unsigned_hour
static int tolua_set_Aula__ZipFileInformation___DateTime_unsigned_hour(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hour'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hour = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: day of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation___DateTime_unsigned_day
static int tolua_get_Aula__ZipFileInformation___DateTime_unsigned_day(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'day'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->day);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: day of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation___DateTime_unsigned_day
static int tolua_set_Aula__ZipFileInformation___DateTime_unsigned_day(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'day'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->day = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: month of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation___DateTime_unsigned_month
static int tolua_get_Aula__ZipFileInformation___DateTime_unsigned_month(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'month'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->month);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: month of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation___DateTime_unsigned_month
static int tolua_set_Aula__ZipFileInformation___DateTime_unsigned_month(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'month'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->month = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: year of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation___DateTime_unsigned_year
static int tolua_get_Aula__ZipFileInformation___DateTime_unsigned_year(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'year'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->year);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: year of class  _DateTime */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation___DateTime_unsigned_year
static int tolua_set_Aula__ZipFileInformation___DateTime_unsigned_year(lua_State* tolua_S)
{
  Aula::ZipFileInformation::_DateTime* self = (Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'year'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->year = (( unsigned long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: date of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_date
static int tolua_get_Aula__ZipFileInformation_date(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'date'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->date,"Aula::ZipFileInformation::_DateTime");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: date of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_date
static int tolua_set_Aula__ZipFileInformation_date(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'date'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Aula::ZipFileInformation::_DateTime",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->date = *((Aula::ZipFileInformation::_DateTime*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fileName of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_fileName
static int tolua_get_Aula__ZipFileInformation_fileName(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileName'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->fileName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fileName of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_fileName
static int tolua_set_Aula__ZipFileInformation_fileName(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileName'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fileName = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: comment of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_get_Aula__ZipFileInformation_comment
static int tolua_get_Aula__ZipFileInformation_comment(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'comment'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->comment);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: comment of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_set_Aula__ZipFileInformation_comment
static int tolua_set_Aula__ZipFileInformation_comment(lua_State* tolua_S)
{
  Aula::ZipFileInformation* self = (Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'comment'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->comment = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileInformation_new00
static int tolua_libAula_core_Aula_ZipFileInformation_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipFileInformation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipFileInformation* tolua_ret = (Aula::ZipFileInformation*)  Mtolua_new((Aula::ZipFileInformation)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipFileInformation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::ZipFileInformation */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileInformation_new00_local
static int tolua_libAula_core_Aula_ZipFileInformation_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipFileInformation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipFileInformation* tolua_ret = (Aula::ZipFileInformation*)  Mtolua_new((Aula::ZipFileInformation)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipFileInformation");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_new00
static int tolua_libAula_core_Aula_ZipArchiver_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipArchiver* tolua_ret = (Aula::ZipArchiver*)  Mtolua_new((Aula::ZipArchiver)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipArchiver");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_new00_local
static int tolua_libAula_core_Aula_ZipArchiver_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipArchiver* tolua_ret = (Aula::ZipArchiver*)  Mtolua_new((Aula::ZipArchiver)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipArchiver");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_new01
static int tolua_libAula_core_Aula_ZipArchiver_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* type = ((const char*)  tolua_tostring(tolua_S,3,"w"));
  {
   Aula::ZipArchiver* tolua_ret = (Aula::ZipArchiver*)  Mtolua_new((Aula::ZipArchiver)(filename,type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipArchiver");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_ZipArchiver_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_new01_local
static int tolua_libAula_core_Aula_ZipArchiver_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* type = ((const char*)  tolua_tostring(tolua_S,3,"w"));
  {
   Aula::ZipArchiver* tolua_ret = (Aula::ZipArchiver*)  Mtolua_new((Aula::ZipArchiver)(filename,type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipArchiver");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_ZipArchiver_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_delete00
static int tolua_libAula_core_Aula_ZipArchiver_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_open00
static int tolua_libAula_core_Aula_ZipArchiver_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* type = ((const char*)  tolua_tostring(tolua_S,3,"w"));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->open(filename,type);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_close00
static int tolua_libAula_core_Aula_ZipArchiver_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
  const char* comment = ((const char*)  tolua_tostring(tolua_S,2,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->close(comment);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: appendFile of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_appendFile00
static int tolua_libAula_core_Aula_ZipArchiver_appendFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
  const char* destFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* srcFileName = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* password = ((const char*)  tolua_tostring(tolua_S,4,""));
  unsigned char level = (( unsigned char)  tolua_tonumber(tolua_S,5,6));
  const char* comment = ((const char*)  tolua_tostring(tolua_S,6,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'appendFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->appendFile(destFileName,srcFileName,password,level,comment);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'appendFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGlobalInformation of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_getGlobalInformation00
static int tolua_libAula_core_Aula_ZipArchiver_getGlobalInformation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Aula::ZipGlobalInformation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::ZipArchiver* self = (const Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
  Aula::ZipGlobalInformation* info = ((Aula::ZipGlobalInformation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGlobalInformation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getGlobalInformation(info);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGlobalInformation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_getSize00
static int tolua_libAula_core_Aula_ZipArchiver_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::ZipArchiver* self = (const Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   unsigned const long tolua_ret = ( unsigned const long)  self->getSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toFirstFile of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_toFirstFile00
static int tolua_libAula_core_Aula_ZipArchiver_toFirstFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toFirstFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->toFirstFile();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toFirstFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toNextFile of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_toNextFile00
static int tolua_libAula_core_Aula_ZipArchiver_toNextFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toNextFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->toNextFile();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toNextFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: locateFile of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_locateFile00
static int tolua_libAula_core_Aula_ZipArchiver_locateFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'locateFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->locateFile(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'locateFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentFileInformation of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_getCurrentFileInformation00
static int tolua_libAula_core_Aula_ZipArchiver_getCurrentFileInformation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Aula::ZipFileInformation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::ZipArchiver* self = (const Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
  Aula::ZipFileInformation* info = ((Aula::ZipFileInformation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentFileInformation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getCurrentFileInformation(info);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentFileInformation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentOffset of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_getCurrentOffset00
static int tolua_libAula_core_Aula_ZipArchiver_getCurrentOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::ZipArchiver* self = (const Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentOffset'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getCurrentOffset();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openCurrentFile of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_openCurrentFile00
static int tolua_libAula_core_Aula_ZipArchiver_openCurrentFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
  const char* password = ((const char*)  tolua_tostring(tolua_S,2,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openCurrentFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->openCurrentFile(password);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openCurrentFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeCurrentFile of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_closeCurrentFile00
static int tolua_libAula_core_Aula_ZipArchiver_closeCurrentFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipArchiver* self = (Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeCurrentFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->closeCurrentFile();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeCurrentFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentFilePosition of class  Aula::ZipArchiver */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipArchiver_getCurrentFilePosition00
static int tolua_libAula_core_Aula_ZipArchiver_getCurrentFilePosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::ZipArchiver",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::ZipArchiver* self = (const Aula::ZipArchiver*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentFilePosition'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getCurrentFilePosition();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentFilePosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::removeZipData */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_removeZipData00
static int tolua_libAula_core_Aula_removeZipData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  Aula::removeZipData(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeZipData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::compressDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_compressDirectory00
static int tolua_libAula_core_Aula_compressDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* dirPath = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* outputFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,""));
  unsigned char level = (( unsigned char)  tolua_tonumber(tolua_S,4,6));
  const char* mode = ((const char*)  tolua_tostring(tolua_S,5,"w"));
  const char* rootDir = ((const char*)  tolua_tostring(tolua_S,6,""));
  {
   bool tolua_ret = (bool)  Aula::compressDirectory(dirPath,outputFile,key,level,mode,rootDir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'compressDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Aula::uncompressDirectory */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_uncompressDirectory00
static int tolua_libAula_core_Aula_uncompressDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* zipFile = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* dirPath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,""));
  {
   bool tolua_ret = (bool)  Aula::uncompressDirectory(zipFile,dirPath,key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'uncompressDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_new00
static int tolua_libAula_core_Aula_ZipFileReader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipFileReader* tolua_ret = (Aula::ZipFileReader*)  Mtolua_new((Aula::ZipFileReader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipFileReader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_new00_local
static int tolua_libAula_core_Aula_ZipFileReader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::ZipFileReader* tolua_ret = (Aula::ZipFileReader*)  Mtolua_new((Aula::ZipFileReader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipFileReader");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_new01
static int tolua_libAula_core_Aula_ZipFileReader_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* arcname = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filename = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* password = ((const char*)  tolua_tostring(tolua_S,4,""));
  {
   Aula::ZipFileReader* tolua_ret = (Aula::ZipFileReader*)  Mtolua_new((Aula::ZipFileReader)(arcname,filename,password));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipFileReader");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_ZipFileReader_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_new01_local
static int tolua_libAula_core_Aula_ZipFileReader_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* arcname = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filename = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* password = ((const char*)  tolua_tostring(tolua_S,4,""));
  {
   Aula::ZipFileReader* tolua_ret = (Aula::ZipFileReader*)  Mtolua_new((Aula::ZipFileReader)(arcname,filename,password));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::ZipFileReader");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_ZipFileReader_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_delete00
static int tolua_libAula_core_Aula_ZipFileReader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPassword of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_setPassword00
static int tolua_libAula_core_Aula_ZipFileReader_setPassword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
  const char* pass = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPassword'", NULL);
#endif
  {
   self->setPassword(pass);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPassword'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_open00
static int tolua_libAula_core_Aula_ZipFileReader_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
  const char* arcname = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filename = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->open(arcname,filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_close00
static int tolua_libAula_core_Aula_ZipFileReader_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_getSize00
static int tolua_libAula_core_Aula_ZipFileReader_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readLine of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_readLine00
static int tolua_libAula_core_Aula_ZipFileReader_readLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readLine'", NULL);
#endif
  {
   string tolua_ret = (string)  self->readLine();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readChar of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_readChar00
static int tolua_libAula_core_Aula_ZipFileReader_readChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readChar'", NULL);
#endif
  {
    char tolua_ret = (  char)  self->readChar();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readAll of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_readAll00
static int tolua_libAula_core_Aula_ZipFileReader_readAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readAll'", NULL);
#endif
  {
   string tolua_ret = (string)  self->readAll();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seek of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_seek00
static int tolua_libAula_core_Aula_ZipFileReader_seek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
   long move = ((  long)  tolua_tonumber(tolua_S,2,0));
  unsigned char from = (( unsigned char)  tolua_tonumber(tolua_S,3,SEEK_SET));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seek'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->seek(move,from);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  Aula::ZipFileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_ZipFileReader_getPosition00
static int tolua_libAula_core_Aula_ZipFileReader_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::ZipFileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::ZipFileReader* self = (Aula::ZipFileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getPosition();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_new00
static int tolua_libAula_core_Aula_FileReader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::FileReader* tolua_ret = (Aula::FileReader*)  Mtolua_new((Aula::FileReader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileReader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_new00_local
static int tolua_libAula_core_Aula_FileReader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Aula::FileReader* tolua_ret = (Aula::FileReader*)  Mtolua_new((Aula::FileReader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileReader");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_new01
static int tolua_libAula_core_Aula_FileReader_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* ext = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* password = ((const char*)  tolua_tostring(tolua_S,4,""));
  {
   Aula::FileReader* tolua_ret = (Aula::FileReader*)  Mtolua_new((Aula::FileReader)(filename,ext,password));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileReader");
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_FileReader_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_new01_local
static int tolua_libAula_core_Aula_FileReader_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* ext = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* password = ((const char*)  tolua_tostring(tolua_S,4,""));
  {
   Aula::FileReader* tolua_ret = (Aula::FileReader*)  Mtolua_new((Aula::FileReader)(filename,ext,password));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Aula::FileReader");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_libAula_core_Aula_FileReader_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_delete00
static int tolua_libAula_core_Aula_FileReader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultArchive of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_setDefaultArchive00
static int tolua_libAula_core_Aula_FileReader_setDefaultArchive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDefaultArchive'", NULL);
#endif
  {
   self->setDefaultArchive(path,key);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefaultArchive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultArchive of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_setDefaultArchive01
static int tolua_libAula_core_Aula_FileReader_setDefaultArchive01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
  const Aula::FileReader* file = ((const Aula::FileReader*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDefaultArchive'", NULL);
#endif
  {
   self->setDefaultArchive(file);
  }
 }
 return 0;
tolua_lerror:
 return tolua_libAula_core_Aula_FileReader_setDefaultArchive00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: open of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_open00
static int tolua_libAula_core_Aula_FileReader_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* ext = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* password = ((const char*)  tolua_tostring(tolua_S,4,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->open(filename,ext,password);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openFile of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_openFile00
static int tolua_libAula_core_Aula_FileReader_openFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->openFile(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openFileInZip of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_openFileInZip00
static int tolua_libAula_core_Aula_FileReader_openFileInZip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
  const char* arcname = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filename = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* password = ((const char*)  tolua_tostring(tolua_S,4,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openFileInZip'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->openFileInZip(arcname,filename,password);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openFileInZip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_close00
static int tolua_libAula_core_Aula_FileReader_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentFilePath of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_getCurrentFilePath00
static int tolua_libAula_core_Aula_FileReader_getCurrentFilePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Aula::FileReader* self = (const Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentFilePath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getCurrentFilePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentFilePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_getSize00
static int tolua_libAula_core_Aula_FileReader_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readLine of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_readLine00
static int tolua_libAula_core_Aula_FileReader_readLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readLine'", NULL);
#endif
  {
   string tolua_ret = (string)  self->readLine();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readChar of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_readChar00
static int tolua_libAula_core_Aula_FileReader_readChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readChar'", NULL);
#endif
  {
    char tolua_ret = (  char)  self->readChar();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readAll of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_readAll00
static int tolua_libAula_core_Aula_FileReader_readAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readAll'", NULL);
#endif
  {
   string tolua_ret = (string)  self->readAll();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seek of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_seek00
static int tolua_libAula_core_Aula_FileReader_seek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
   long move = ((  long)  tolua_tonumber(tolua_S,2,0));
  unsigned char from = (( unsigned char)  tolua_tonumber(tolua_S,3,SEEK_SET));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seek'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->seek(move,from);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  Aula::FileReader */
#ifndef TOLUA_DISABLE_tolua_libAula_core_Aula_FileReader_getPosition00
static int tolua_libAula_core_Aula_FileReader_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Aula::FileReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Aula::FileReader* self = (Aula::FileReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->getPosition();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_libAula_core_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"SEEK_SET",SEEK_SET);
  tolua_constant(tolua_S,"SEEK_CUR",SEEK_CUR);
  tolua_constant(tolua_S,"SEEK_END",SEEK_END);
  tolua_module(tolua_S,"Aula",0);
  tolua_beginmodule(tolua_S,"Aula");
   tolua_function(tolua_S,"isSameString",tolua_libAula_core_Aula_isSameString00);
   tolua_function(tolua_S,"isSameString",tolua_libAula_core_Aula_isSameString01);
   tolua_module(tolua_S,"Encoding",0);
   tolua_beginmodule(tolua_S,"Encoding");
    tolua_constant(tolua_S,"UNKNOWN",Aula::Encoding::UNKNOWN);
    tolua_constant(tolua_S,"BINARY",Aula::Encoding::BINARY);
    tolua_constant(tolua_S,"ANSI",Aula::Encoding::ANSI);
    tolua_constant(tolua_S,"SJIS",Aula::Encoding::SJIS);
    tolua_constant(tolua_S,"JIS",Aula::Encoding::JIS);
    tolua_constant(tolua_S,"EUC",Aula::Encoding::EUC);
    tolua_constant(tolua_S,"ISO2022JP",Aula::Encoding::ISO2022JP);
    tolua_constant(tolua_S,"UTF8",Aula::Encoding::UTF8);
    tolua_constant(tolua_S,"UTF16BE",Aula::Encoding::UTF16BE);
    tolua_constant(tolua_S,"UTF16LE",Aula::Encoding::UTF16LE);
    tolua_constant(tolua_S,"UTF32BE",Aula::Encoding::UTF32BE);
    tolua_constant(tolua_S,"UTF32LE",Aula::Encoding::UTF32LE);
    tolua_function(tolua_S,"getName",tolua_libAula_core_Aula_Encoding_getName00);
    tolua_function(tolua_S,"isUTF8",tolua_libAula_core_Aula_Encoding_isUTF800);
    tolua_function(tolua_S,"encode",tolua_libAula_core_Aula_Encoding_encode00);
    tolua_function(tolua_S,"toUTF8",tolua_libAula_core_Aula_Encoding_toUTF800);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"Console",0);
   tolua_beginmodule(tolua_S,"Console");
    tolua_function(tolua_S,"writeLine",tolua_libAula_core_Aula_Console_writeLine00);
    tolua_function(tolua_S,"write",tolua_libAula_core_Aula_Console_write00);
    tolua_constant(tolua_S,"BLACK",Aula::Console::BLACK);
    tolua_constant(tolua_S,"BLUE",Aula::Console::BLUE);
    tolua_constant(tolua_S,"GREEN",Aula::Console::GREEN);
    tolua_constant(tolua_S,"CYAN",Aula::Console::CYAN);
    tolua_constant(tolua_S,"RED",Aula::Console::RED);
    tolua_constant(tolua_S,"PURPLE",Aula::Console::PURPLE);
    tolua_constant(tolua_S,"YELLOW",Aula::Console::YELLOW);
    tolua_constant(tolua_S,"WHITE",Aula::Console::WHITE);
    tolua_function(tolua_S,"setAttribute",tolua_libAula_core_Aula_Console_setAttribute00);
    tolua_function(tolua_S,"setCursorPosition",tolua_libAula_core_Aula_Console_setCursorPosition00);
    tolua_function(tolua_S,"clear",tolua_libAula_core_Aula_Console_clear00);
    tolua_function(tolua_S,"isKeyPressed",tolua_libAula_core_Aula_Console_isKeyPressed00);
    tolua_function(tolua_S,"getPressedKey",tolua_libAula_core_Aula_Console_getPressedKey00);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"System",0);
   tolua_beginmodule(tolua_S,"System");
    tolua_function(tolua_S,"execute",tolua_libAula_core_Aula_System_execute00);
    tolua_function(tolua_S,"sleep",tolua_libAula_core_Aula_System_sleep00);
    tolua_function(tolua_S,"getTime",tolua_libAula_core_Aula_System_getTime00);
    tolua_function(tolua_S,"setEnvironmentVariable",tolua_libAula_core_Aula_System_setEnvironmentVariable00);
    tolua_function(tolua_S,"getEnvironmentVariable",tolua_libAula_core_Aula_System_getEnvironmentVariable00);
    tolua_function(tolua_S,"setCurrentDirectory",tolua_libAula_core_Aula_System_setCurrentDirectory00);
    tolua_function(tolua_S,"getCurrentDirectory",tolua_libAula_core_Aula_System_getCurrentDirectory00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Object","Aula::Object","",NULL);
   tolua_beginmodule(tolua_S,"Object");
    tolua_constant(tolua_S,"NONE",Aula::Object::NONE);
    tolua_constant(tolua_S,"ACTIVE",Aula::Object::ACTIVE);
    tolua_constant(tolua_S,"FAILED",Aula::Object::FAILED);
    tolua_constant(tolua_S,"FINISHED",Aula::Object::FINISHED);
    tolua_constant(tolua_S,"BUSY",Aula::Object::BUSY);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"getState",tolua_libAula_core_Aula_getState00);
   tolua_function(tolua_S,"getMessage",tolua_libAula_core_Aula_getMessage00);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"LibraryLoader","Aula::LibraryLoader","Aula::Object",tolua_collect_Aula__LibraryLoader);
   #else
   tolua_cclass(tolua_S,"LibraryLoader","Aula::LibraryLoader","Aula::Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"LibraryLoader");
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_LibraryLoader_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_LibraryLoader_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_LibraryLoader_new00_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_LibraryLoader_new01);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_LibraryLoader_new01_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_LibraryLoader_new01_local);
    tolua_function(tolua_S,"delete",tolua_libAula_core_Aula_LibraryLoader_delete00);
    tolua_function(tolua_S,"open",tolua_libAula_core_Aula_LibraryLoader_open00);
    tolua_function(tolua_S,"close",tolua_libAula_core_Aula_LibraryLoader_close00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Randomizer","Aula::Randomizer","Aula::Object",tolua_collect_Aula__Randomizer);
   #else
   tolua_cclass(tolua_S,"Randomizer","Aula::Randomizer","Aula::Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Randomizer");
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_Randomizer_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_Randomizer_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_Randomizer_new00_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_Randomizer_new01);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_Randomizer_new01_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_Randomizer_new01_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_Randomizer_new02);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_Randomizer_new02_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_Randomizer_new02_local);
    tolua_function(tolua_S,"seed",tolua_libAula_core_Aula_Randomizer_seed00);
    tolua_function(tolua_S,"seed",tolua_libAula_core_Aula_Randomizer_seed01);
    tolua_function(tolua_S,"get",tolua_libAula_core_Aula_Randomizer_get00);
    tolua_function(tolua_S,"get",tolua_libAula_core_Aula_Randomizer_get01);
    tolua_function(tolua_S,"get",tolua_libAula_core_Aula_Randomizer_get02);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"Engine",0);
   tolua_beginmodule(tolua_S,"Engine");
    tolua_function(tolua_S,"encodeDirectory",tolua_libAula_core_Aula_Engine_encodeDirectory00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Aula",0);
  tolua_beginmodule(tolua_S,"Aula");
   tolua_module(tolua_S,"Path",0);
   tolua_beginmodule(tolua_S,"Path");
    tolua_function(tolua_S,"getLeaf",tolua_libAula_core_Aula_Path_getLeaf00);
    tolua_function(tolua_S,"getStem",tolua_libAula_core_Aula_Path_getStem00);
    tolua_function(tolua_S,"getExtension",tolua_libAula_core_Aula_Path_getExtension00);
    tolua_function(tolua_S,"convert",tolua_libAula_core_Aula_Path_convert00);
    tolua_function(tolua_S,"isSame",tolua_libAula_core_Aula_Path_isSame00);
    tolua_function(tolua_S,"isSame",tolua_libAula_core_Aula_Path_isSame01);
    tolua_function(tolua_S,"getParent",tolua_libAula_core_Aula_Path_getParent00);
    tolua_function(tolua_S,"isFile",tolua_libAula_core_Aula_Path_isFile00);
    tolua_function(tolua_S,"isDirectory",tolua_libAula_core_Aula_Path_isDirectory00);
    tolua_function(tolua_S,"complete",tolua_libAula_core_Aula_Path_complete00);
    tolua_function(tolua_S,"appendSlash",tolua_libAula_core_Aula_Path_appendSlash00);
    tolua_function(tolua_S,"removeSlash",tolua_libAula_core_Aula_Path_removeSlash00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"File","Aula::File","Aula::Object",tolua_collect_Aula__File);
   #else
   tolua_cclass(tolua_S,"File","Aula::File","Aula::Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"File");
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_File_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_File_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_File_new00_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_File_new01);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_File_new01_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_File_new01_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_File_new02);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_File_new02_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_File_new02_local);
    tolua_function(tolua_S,"delete",tolua_libAula_core_Aula_File_delete00);
    tolua_function(tolua_S,"open",tolua_libAula_core_Aula_File_open00);
    tolua_function(tolua_S,"open",tolua_libAula_core_Aula_File_open01);
    tolua_function(tolua_S,"close",tolua_libAula_core_Aula_File_close00);
    tolua_function(tolua_S,"getSize",tolua_libAula_core_Aula_File_getSize00);
    tolua_function(tolua_S,"readLine",tolua_libAula_core_Aula_File_readLine00);
    tolua_function(tolua_S,"readChar",tolua_libAula_core_Aula_File_readChar00);
    tolua_function(tolua_S,"writeLine",tolua_libAula_core_Aula_File_writeLine00);
    tolua_function(tolua_S,"writeChar",tolua_libAula_core_Aula_File_writeChar00);
    tolua_function(tolua_S,"readAll",tolua_libAula_core_Aula_File_readAll00);
    tolua_function(tolua_S,"seek",tolua_libAula_core_Aula_File_seek00);
    tolua_function(tolua_S,"getPosition",tolua_libAula_core_Aula_File_getPosition00);
    tolua_function(tolua_S,"flush",tolua_libAula_core_Aula_File_flush00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"FileEnumerator","Aula::FileEnumerator","Aula::Object",tolua_collect_Aula__FileEnumerator);
   #else
   tolua_cclass(tolua_S,"FileEnumerator","Aula::FileEnumerator","Aula::Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"FileEnumerator");
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_FileEnumerator_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_FileEnumerator_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_FileEnumerator_new00_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_FileEnumerator_new01);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_FileEnumerator_new01_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_FileEnumerator_new01_local);
    tolua_function(tolua_S,"delete",tolua_libAula_core_Aula_FileEnumerator_delete00);
    tolua_function(tolua_S,"open",tolua_libAula_core_Aula_FileEnumerator_open00);
    tolua_function(tolua_S,"close",tolua_libAula_core_Aula_FileEnumerator_close00);
    tolua_function(tolua_S,"toNext",tolua_libAula_core_Aula_FileEnumerator_toNext00);
    tolua_function(tolua_S,"getName",tolua_libAula_core_Aula_FileEnumerator_getName00);
    tolua_function(tolua_S,"getPath",tolua_libAula_core_Aula_FileEnumerator_getPath00);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"copyFile",tolua_libAula_core_Aula_copyFile00);
   tolua_function(tolua_S,"removeFile",tolua_libAula_core_Aula_removeFile00);
   tolua_function(tolua_S,"moveFile",tolua_libAula_core_Aula_moveFile00);
   tolua_function(tolua_S,"createDirectory",tolua_libAula_core_Aula_createDirectory00);
   tolua_function(tolua_S,"copyDirectory",tolua_libAula_core_Aula_copyDirectory00);
   tolua_function(tolua_S,"removeDirectory",tolua_libAula_core_Aula_removeDirectory00);
   tolua_function(tolua_S,"moveDirectory",tolua_libAula_core_Aula_moveDirectory00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Aula",0);
  tolua_beginmodule(tolua_S,"Aula");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ZipGlobalInformation","Aula::ZipGlobalInformation","",tolua_collect_Aula__ZipGlobalInformation);
   #else
   tolua_cclass(tolua_S,"ZipGlobalInformation","Aula::ZipGlobalInformation","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ZipGlobalInformation");
    tolua_variable(tolua_S,"entries",tolua_get_Aula__ZipGlobalInformation_unsigned_entries,tolua_set_Aula__ZipGlobalInformation_unsigned_entries);
    tolua_variable(tolua_S,"commentSize",tolua_get_Aula__ZipGlobalInformation_unsigned_commentSize,tolua_set_Aula__ZipGlobalInformation_unsigned_commentSize);
    tolua_variable(tolua_S,"comment",tolua_get_Aula__ZipGlobalInformation_comment,tolua_set_Aula__ZipGlobalInformation_comment);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_ZipGlobalInformation_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_ZipGlobalInformation_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_ZipGlobalInformation_new00_local);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ZipFileInformation","Aula::ZipFileInformation","",tolua_collect_Aula__ZipFileInformation);
   #else
   tolua_cclass(tolua_S,"ZipFileInformation","Aula::ZipFileInformation","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ZipFileInformation");
    tolua_variable(tolua_S,"version",tolua_get_Aula__ZipFileInformation_unsigned_version,tolua_set_Aula__ZipFileInformation_unsigned_version);
    tolua_variable(tolua_S,"neededVersion",tolua_get_Aula__ZipFileInformation_unsigned_neededVersion,tolua_set_Aula__ZipFileInformation_unsigned_neededVersion);
    tolua_variable(tolua_S,"flag",tolua_get_Aula__ZipFileInformation_unsigned_flag,tolua_set_Aula__ZipFileInformation_unsigned_flag);
    tolua_variable(tolua_S,"compressionMethod",tolua_get_Aula__ZipFileInformation_unsigned_compressionMethod,tolua_set_Aula__ZipFileInformation_unsigned_compressionMethod);
    tolua_variable(tolua_S,"dosDate",tolua_get_Aula__ZipFileInformation_unsigned_dosDate,tolua_set_Aula__ZipFileInformation_unsigned_dosDate);
    tolua_variable(tolua_S,"crc",tolua_get_Aula__ZipFileInformation_unsigned_crc,tolua_set_Aula__ZipFileInformation_unsigned_crc);
    tolua_variable(tolua_S,"compressedSize",tolua_get_Aula__ZipFileInformation_unsigned_compressedSize,tolua_set_Aula__ZipFileInformation_unsigned_compressedSize);
    tolua_variable(tolua_S,"uncompressedSize",tolua_get_Aula__ZipFileInformation_unsigned_uncompressedSize,tolua_set_Aula__ZipFileInformation_unsigned_uncompressedSize);
    tolua_variable(tolua_S,"fileNameSize",tolua_get_Aula__ZipFileInformation_unsigned_fileNameSize,tolua_set_Aula__ZipFileInformation_unsigned_fileNameSize);
    tolua_variable(tolua_S,"fileExtraSize",tolua_get_Aula__ZipFileInformation_unsigned_fileExtraSize,tolua_set_Aula__ZipFileInformation_unsigned_fileExtraSize);
    tolua_variable(tolua_S,"fileCommentSize",tolua_get_Aula__ZipFileInformation_unsigned_fileCommentSize,tolua_set_Aula__ZipFileInformation_unsigned_fileCommentSize);
    tolua_variable(tolua_S,"diskNumStart",tolua_get_Aula__ZipFileInformation_unsigned_diskNumStart,tolua_set_Aula__ZipFileInformation_unsigned_diskNumStart);
    tolua_variable(tolua_S,"internalFA",tolua_get_Aula__ZipFileInformation_unsigned_internalFA,tolua_set_Aula__ZipFileInformation_unsigned_internalFA);
    tolua_variable(tolua_S,"externalFA",tolua_get_Aula__ZipFileInformation_unsigned_externalFA,tolua_set_Aula__ZipFileInformation_unsigned_externalFA);
    tolua_cclass(tolua_S,"_DateTime","Aula::ZipFileInformation::_DateTime","",NULL);
    tolua_beginmodule(tolua_S,"_DateTime");
     tolua_variable(tolua_S,"sec",tolua_get_Aula__ZipFileInformation___DateTime_unsigned_sec,tolua_set_Aula__ZipFileInformation___DateTime_unsigned_sec);
     tolua_variable(tolua_S,"min",tolua_get_Aula__ZipFileInformation___DateTime_unsigned_min,tolua_set_Aula__ZipFileInformation___DateTime_unsigned_min);
     tolua_variable(tolua_S,"hour",tolua_get_Aula__ZipFileInformation___DateTime_unsigned_hour,tolua_set_Aula__ZipFileInformation___DateTime_unsigned_hour);
     tolua_variable(tolua_S,"day",tolua_get_Aula__ZipFileInformation___DateTime_unsigned_day,tolua_set_Aula__ZipFileInformation___DateTime_unsigned_day);
     tolua_variable(tolua_S,"month",tolua_get_Aula__ZipFileInformation___DateTime_unsigned_month,tolua_set_Aula__ZipFileInformation___DateTime_unsigned_month);
     tolua_variable(tolua_S,"year",tolua_get_Aula__ZipFileInformation___DateTime_unsigned_year,tolua_set_Aula__ZipFileInformation___DateTime_unsigned_year);
    tolua_endmodule(tolua_S);
    tolua_variable(tolua_S,"date",tolua_get_Aula__ZipFileInformation_date,tolua_set_Aula__ZipFileInformation_date);
    tolua_variable(tolua_S,"fileName",tolua_get_Aula__ZipFileInformation_fileName,tolua_set_Aula__ZipFileInformation_fileName);
    tolua_variable(tolua_S,"comment",tolua_get_Aula__ZipFileInformation_comment,tolua_set_Aula__ZipFileInformation_comment);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_ZipFileInformation_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_ZipFileInformation_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_ZipFileInformation_new00_local);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ZipArchiver","Aula::ZipArchiver","Aula::Object",tolua_collect_Aula__ZipArchiver);
   #else
   tolua_cclass(tolua_S,"ZipArchiver","Aula::ZipArchiver","Aula::Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ZipArchiver");
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_ZipArchiver_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_ZipArchiver_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_ZipArchiver_new00_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_ZipArchiver_new01);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_ZipArchiver_new01_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_ZipArchiver_new01_local);
    tolua_function(tolua_S,"delete",tolua_libAula_core_Aula_ZipArchiver_delete00);
    tolua_function(tolua_S,"open",tolua_libAula_core_Aula_ZipArchiver_open00);
    tolua_function(tolua_S,"close",tolua_libAula_core_Aula_ZipArchiver_close00);
    tolua_function(tolua_S,"appendFile",tolua_libAula_core_Aula_ZipArchiver_appendFile00);
    tolua_function(tolua_S,"getGlobalInformation",tolua_libAula_core_Aula_ZipArchiver_getGlobalInformation00);
    tolua_function(tolua_S,"getSize",tolua_libAula_core_Aula_ZipArchiver_getSize00);
    tolua_function(tolua_S,"toFirstFile",tolua_libAula_core_Aula_ZipArchiver_toFirstFile00);
    tolua_function(tolua_S,"toNextFile",tolua_libAula_core_Aula_ZipArchiver_toNextFile00);
    tolua_function(tolua_S,"locateFile",tolua_libAula_core_Aula_ZipArchiver_locateFile00);
    tolua_function(tolua_S,"getCurrentFileInformation",tolua_libAula_core_Aula_ZipArchiver_getCurrentFileInformation00);
    tolua_function(tolua_S,"getCurrentOffset",tolua_libAula_core_Aula_ZipArchiver_getCurrentOffset00);
    tolua_function(tolua_S,"openCurrentFile",tolua_libAula_core_Aula_ZipArchiver_openCurrentFile00);
    tolua_function(tolua_S,"closeCurrentFile",tolua_libAula_core_Aula_ZipArchiver_closeCurrentFile00);
    tolua_function(tolua_S,"getCurrentFilePosition",tolua_libAula_core_Aula_ZipArchiver_getCurrentFilePosition00);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"removeZipData",tolua_libAula_core_Aula_removeZipData00);
   tolua_function(tolua_S,"compressDirectory",tolua_libAula_core_Aula_compressDirectory00);
   tolua_function(tolua_S,"uncompressDirectory",tolua_libAula_core_Aula_uncompressDirectory00);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ZipFileReader","Aula::ZipFileReader","Aula::Object",tolua_collect_Aula__ZipFileReader);
   #else
   tolua_cclass(tolua_S,"ZipFileReader","Aula::ZipFileReader","Aula::Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ZipFileReader");
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_ZipFileReader_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_ZipFileReader_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_ZipFileReader_new00_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_ZipFileReader_new01);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_ZipFileReader_new01_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_ZipFileReader_new01_local);
    tolua_function(tolua_S,"delete",tolua_libAula_core_Aula_ZipFileReader_delete00);
    tolua_function(tolua_S,"setPassword",tolua_libAula_core_Aula_ZipFileReader_setPassword00);
    tolua_function(tolua_S,"open",tolua_libAula_core_Aula_ZipFileReader_open00);
    tolua_function(tolua_S,"close",tolua_libAula_core_Aula_ZipFileReader_close00);
    tolua_function(tolua_S,"getSize",tolua_libAula_core_Aula_ZipFileReader_getSize00);
    tolua_function(tolua_S,"readLine",tolua_libAula_core_Aula_ZipFileReader_readLine00);
    tolua_function(tolua_S,"readChar",tolua_libAula_core_Aula_ZipFileReader_readChar00);
    tolua_function(tolua_S,"readAll",tolua_libAula_core_Aula_ZipFileReader_readAll00);
    tolua_function(tolua_S,"seek",tolua_libAula_core_Aula_ZipFileReader_seek00);
    tolua_function(tolua_S,"getPosition",tolua_libAula_core_Aula_ZipFileReader_getPosition00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"FileReader","Aula::FileReader","Aula::Object",tolua_collect_Aula__FileReader);
   #else
   tolua_cclass(tolua_S,"FileReader","Aula::FileReader","Aula::Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"FileReader");
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_FileReader_new00);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_FileReader_new00_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_FileReader_new00_local);
    tolua_function(tolua_S,"new",tolua_libAula_core_Aula_FileReader_new01);
    tolua_function(tolua_S,"new_local",tolua_libAula_core_Aula_FileReader_new01_local);
    tolua_function(tolua_S,".call",tolua_libAula_core_Aula_FileReader_new01_local);
    tolua_function(tolua_S,"delete",tolua_libAula_core_Aula_FileReader_delete00);
    tolua_function(tolua_S,"setDefaultArchive",tolua_libAula_core_Aula_FileReader_setDefaultArchive00);
    tolua_function(tolua_S,"setDefaultArchive",tolua_libAula_core_Aula_FileReader_setDefaultArchive01);
    tolua_function(tolua_S,"open",tolua_libAula_core_Aula_FileReader_open00);
    tolua_function(tolua_S,"openFile",tolua_libAula_core_Aula_FileReader_openFile00);
    tolua_function(tolua_S,"openFileInZip",tolua_libAula_core_Aula_FileReader_openFileInZip00);
    tolua_function(tolua_S,"close",tolua_libAula_core_Aula_FileReader_close00);
    tolua_function(tolua_S,"getCurrentFilePath",tolua_libAula_core_Aula_FileReader_getCurrentFilePath00);
    tolua_function(tolua_S,"getSize",tolua_libAula_core_Aula_FileReader_getSize00);
    tolua_function(tolua_S,"readLine",tolua_libAula_core_Aula_FileReader_readLine00);
    tolua_function(tolua_S,"readChar",tolua_libAula_core_Aula_FileReader_readChar00);
    tolua_function(tolua_S,"readAll",tolua_libAula_core_Aula_FileReader_readAll00);
    tolua_function(tolua_S,"seek",tolua_libAula_core_Aula_FileReader_seek00);
    tolua_function(tolua_S,"getPosition",tolua_libAula_core_Aula_FileReader_getPosition00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_libAula_core (lua_State* tolua_S) {
 return tolua_libAula_core_open(tolua_S);
};
#endif

