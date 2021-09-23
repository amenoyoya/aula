#pragma once

#include "core.h"

namespace Aula{
    /* tolua++クラスにメソッドを追加する関数 */
    // スタックの一番上にあるtolua++クラスをアンロックする
    inline void tolua_unlockclass(lua_State *L){
        lua_getmetatable(L, -1);  // -> -2:class<tolua> | -1:meta
        lua_createtable(L, 0, 0); // -> -3:class<tolua> | -2:meta | -1:{}
        lua_setmetatable(L, -3);  // -> -2:class<plain> | -1:meta
    }
    
    // STACK -2:class<plain> | -1:meta の状態で
    // アンロックしたtolua++クラスを元に戻す
    inline void tolua_lockclass(lua_State *L){
        lua_setmetatable(L, -2);  // -> -1:class<tolua>
        lua_pop(L, 1);
    }
    
    
    /*** Aula Engine ***/
    namespace Engine{
        /* エラー処理 */
        // エラーハンドラー設定
        void setErrorHandler(int (*func)(lua_State *L));
        // Aula.Engine.errorHandler(errorMessage) を実行する
        // エラーメッセージはLuaスタックの一番上に乗っている必要がある
        void processError(lua_State *L);
        
        
        /* エンジン作成・修了 */
        inline lua_State *create(){
            lua_State *L = luaL_newstate();
            if(!registerCoreLibrary(L)) processError(L);
            return L;
        }
        
        inline void release(lua_State *L){
            lua_close(L);
        }
        
        /* ScriptFileReader取得 */
        // Aula.Engine.readerを呼び出す
        FileReader *getFileReader(lua_State *L);
        
        /* Luaスクリプトバッファーをロード */
        // 失敗した場合，Luaスタックの一番上にエラーメッセージがある
        inline bool loadScript(lua_State *L, const char *buffer, u32 size=u32(-1), const string &chunk="string"){
            size = size == u32(-1)? strlen(buffer): size;
            return size? 0 == luaL_loadbuffer(L, buffer, size, chunk.c_str()): true;
        }
        
        /* Luaファイルをロード */
        // 現在FileReaderがopenしているファイルをロード
        // @param mode: 実行モード 0=Lua, 1=バイトコード
        // @return: -1=ファイルが存在しない, 1=成功,
        //           0=スクリプトロード失敗(Luaスタックの一番上にエラーメッセージ)
        s8 loadScriptFile(lua_State *L, FileReader *pReader, u8 mode=0);
        
        /* メインスクリプトをロード */
        // path: file or directory (暗号化アーカイブなら復号化して実行)
        //       ディレクトリかアーカイブなら内部の __main.lua(.sym) をロード
        // pReader: ScriptFileReader。指定されない場合は内部でgetFileReaderされる
        //          pReaderを指定した場合，ロードは行われない（後でloadScriptFileを実行する必要がある）
        // 戻り値（pReader未指定時）: -1=指定パスが無効, 0=ロード失敗, 1=成功
        // 戻り値（pReader指定時は実行モード）: -1=指定パスが無効, 0=Lua, 1=SeleneTalk, 2=バイトコード
        s8 load(lua_State *L, const string &path, FileReader *pReader=nullptr);
        
        /* スタックの値（関数）を呼び出す */
        // 失敗した場合，Luaスタックの一番上にエラーメッセージがある
        inline bool call(lua_State *L, u32 nArgs, u32 nReturns){
            return 0 == lua_pcall(L, nArgs, nReturns, 0);
        }
        
        
        /* ディレクトリを復号化キー埋め込みアーカイブ化 */
        // スクリプト格納ディレクトリ用
        bool encodeDirectory(const string &dirPath, const string &outputFile, const string &key="", u8 level=6);
    }
}
