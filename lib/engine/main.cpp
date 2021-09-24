#include "main.h"

namespace Aula{
    namespace Engine{
        /*** エラー処理 ***/
        // デフォルトエラーハンドラー
        static inline void defErrorHandler(const string &msg){
            #ifdef _WINDOWS
                MessageBox(nullptr, Encoding::utf8ToWideString(msg).c_str(), L"Script Error", MB_OK|MB_ICONWARNING);
            #else
                Console::writeLine(msg);
            #endif
        }
        
        void setErrorHandler(lua_State *L, int (*func)(lua_State *L)){
            lua_getglobal(L, "Aula");
            lua_getfield(L, -1, "Engine");
            lua_pushcfunction(L, func);
            lua_setfield(L, -2, "errorHandler");
            lua_pop(L, 2);
        }
        
        void processError(lua_State *L){
            string err = lua_tostring(L, -1);
            
            lua_getglobal(L, "Aula");
            lua_getfield(L, -1, "Engine");
            lua_getfield(L, -1, "errorHandler");
            if(lua_type(L, -1) == LUA_TFUNCTION){
                lua_pushstring(L, err.c_str());
                if(0 != lua_pcall(L, 1, 0, 0)) defErrorHandler(string("[Aula::Engine::errorHandler]") + lua_tostring(L, -1) + "\n" + err);
                lua_pop(L, 3);
            }else{
                defErrorHandler(err);
                lua_pop(L, 4);
            }
        }
        
        
        /* ScriptFileReader取得 */
        FileReader *getFileReader(lua_State *L){
            tolua_Error tolua_err;
            FileReader *pReader = nullptr;
            
            lua_getglobal(L, "Aula");
            lua_getfield(L, -1, "Engine");
            lua_getfield(L, -1, "reader");
            if(tolua_isusertype(L, -1, "Aula::FileReader", 0, &tolua_err)) pReader = (FileReader*)tolua_tousertype(L, -1, 0);
            lua_pop(L, 3);
            return pReader;
        }
        
        /* Luaファイルをロード */
        s8 loadScriptFile(lua_State *L, FileReader *pReader, u8 mode){
            if(!pReader || getState(pReader) != Object::ACTIVE) return -1;
            
            if(mode > 1){ // バイトコードはそのまま実行
                u32 size = pReader->getSize();
                string buf;
                buf.resize(size);
                pReader->read((void*)&buf[0], size);
                return (s8)loadScript(L, buf.c_str(), size, pReader->getCurrentFilePath());
            }
            // Luaファイル
            return (s8)loadScript(L, Encoding::toUTF8(pReader->readAll()).c_str(), u32(-1), pReader->getCurrentFilePath());
        }
        
        
        /* 復号化キー埋め込みアーカイブから復号化キー取得 */
        static string getPassword(const string &arc){
            ZipArchiver zip(arc, "r");
            u32 zipsize;
            
            if(getState(&zip) == Object::FAILED) return "";
            if(0 == (zipsize = zip.getSize())) return "";
            zip.close();
            
            File file(arc, "rb");
            string pass, bin;
            s32 size = 0, allsize = 0;
            
            if(getState(&file) == Object::FAILED) return "";
            file.seek(-1 * zipsize, SEEK_END); // zipデータの分だけ前に戻る
            file.seek(-4, SEEK_CUR); // パスワードサイズ値(4byte)分更に戻る
            // パスワードサイズ取得
            file.read(&size, 4);
            bin.resize(allsize = size * 4);
            if(size <= 0 || file.getSize() < (u32)allsize + 4) return "";
            // 暗号化パスワード取得
            file.seek(-allsize-4, SEEK_CUR);
            file.read((void*)&bin[0], allsize);
            // 復号化
            pass.reserve(size);
            for(s32 i = 0; i < allsize; i += 4){
                char buf = bin[i];
                
                if((i/4) % 2 == 0) buf = ~buf;
                else if((i/4) % 3 == 0) buf += (char)i;
                else buf -= (char)i;
                
                pass.push_back(buf);
            }
            return pass;
        }
        
        /* メインスクリプトをロード */
        s8 load(lua_State *L, const string &path, FileReader *_pReader){
            FileReader *pReader = _pReader? _pReader: getFileReader(L);
            
            string mainFiles[] = { "__main.lua", "__main.sym" };
            u8 modes[] = { 0, 1 };
            
            if(Path::isFile(path)){
                string ext = Path::getExtension(path);
                u8 mode = isSameString(ext, ".lua")? 0: (isSameString(ext, ".sym")? 1: 2);
                // スクリプトファイルロード
                if(mode < 2 && pReader->openFile(path)){
                    System::setCurrentDirectory(Path::getParentDirectory(path));
                    return _pReader? mode: loadScriptFile(L, pReader, mode);
                }
                // アーカイブファイルロード
                string key = getPassword(path); // 復号化キー取得
                for(u32 i = 0; i < 2; ++i){
                    if(pReader->openFileInZip(path, mainFiles[i], key)){
                        System::setCurrentDirectory(Path::getParentDirectory(path));
                        pReader->setDefaultArchive(path, key); // 復号化キーを保存
                        return _pReader? modes[i]: loadScriptFile(L, pReader, modes[i]);
                    }
                }
            }else if(Path::isDirectory(path)){
                // ディレクトリ内のメインスクリプト実行
                for(u32 i = 0; i < 2; ++i){
                    if(pReader->openFile(Path::appendSlash(path) + mainFiles[i])){
                        System::setCurrentDirectory(path);
                        return _pReader? modes[i]: loadScriptFile(L, pReader, modes[i]);
                    }
                }
            }
            return -1;
        }
        
        
        /*** アーカイブ暗号化関連 ***/
        // パスワードを暗号化してファイルに付与する
        static void encodePassword(File *file, const string &key){
            string bin;
            char *p;
            Randomizer rand;
            u32 size = key.size(), allsize = size * 4;
            
            bin.resize(allsize + 4);
            p = (char*)bin.c_str();
            for(u32 i = 0; i < allsize; ++i){
                char buf = (char)rand.get(256);
                
                if(i % 4 == 0) buf = key[i/4];
                
                if((i/4) % 2 == 0) buf = ~buf;
                else if((i/4) % 3 == 0) buf -= (char)i;
                else buf += (char)i;
                
                *(p++) = buf;
            }
            memcpy(p, &size, 4);
            file->seek(0, SEEK_END);
            file->write(bin.c_str(), allsize + 4);
        }
        
        /* ディレクトリを復号化キー埋め込みアーカイブ化 */
        bool encodeDirectory(const string &dirPath, const string &outputFile, const string &key, u8 level){
            File file(outputFile, "wb");
            // 復号化キーを埋め込む
            encodePassword(&file, key);
            file.close();
            // アーカイブ化
            return compressDirectory(dirPath, outputFile, key, level, "w+");
        }
    }
}
