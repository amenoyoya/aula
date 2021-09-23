#pragma once

#include "base.h"

#ifndef _WINDOWS
    #include <dlfcn.h>
#endif

#define MEXP 19937
#define SFMT_MEXP 19937
#include "SFMT-1.4.1/SFMT.h"

namespace Aula{
    /*** Aulaライブラリ基底クラス ***/
    class Object;
    u8 getState(Object *obj);
    string getMessage(Object *obj);
    
    class Object{
    public:
        enum State{ // Objectの状態
            NONE, ACTIVE, FAILED, FINISHED, BUSY
        };
        
        Object(): _state(NONE) {}
        
        friend u8 getState(Object *obj);
        friend string getMessage(Object *obj);
    protected:
        u8        _state;    // 状態
        string    _message;    // メッセージ
        
        virtual u8 _getState(){return _state;}
        virtual string _getMessage(){return _message;}
    };
    
    // オブジェクトの状態・メッセージを取得
    inline u8 getState(Object *obj){
        return obj->_getState();
    }
    inline string getMessage(Object *obj){
        return obj->_getMessage();
    }
    
    
    /*** 動的ライブラリ読み込みクラス ***/
    class LibraryLoader: public Object {
        u32        handle;
    public:
        LibraryLoader(): Object(), handle(0) {}
        explicit LibraryLoader(const string &path): Object(), handle(0) {
            open(path);
        }
        ~LibraryLoader(){
            close();
        }
        
        // dllファイルオープン
        bool open(const string &path);
        void close();
        
        // 指定関数名の関数をロード
        void *getFunction(const string &name){
            #ifdef _WINDOWS
                return handle? (void*)GetProcAddress((HMODULE)handle, name.c_str()): nullptr;
            #else
                return handle? dlsym((void*)handle, name.c_str()): nullptr;
            #endif
        }
    };
    
    
    /*** 乱数発生器 ***/
    class Randomizer: public Object {
    public:
        explicit Randomizer(s32 _seed=(s32)time(nullptr)): Object() {
            _state = ACTIVE; seed(_seed);
        }
        explicit Randomizer(s32 seedsNum, s32 seeds[]): Object() {
            _state = ACTIVE; seed(seedsNum, seeds);
        }
        
        // 乱数の種を植える
        void seed(s32 _seed){
            sfmt_init_gen_rand(&sfmt, _seed);
        }
        void seed(s32 seedsNum, s32 seeds[]){
            sfmt_init_by_array(&sfmt, (uint32_t*)seeds, seedsNum);
        }
        
        // 32bitの乱数生成
        u32 get(){
            return sfmt_genrand_uint32(&sfmt);
        }
        // 0～r-1までの32bit乱数生成
        u32 get(u32 r){
            return get() % r;
        }
        // min～maxまでの32bit乱数生成
        s32 get(s32 min, s32 max){
            return get(max-min+1) + min;
        }
    private:
        sfmt_t sfmt;
    };
    
    
    // バイナリデータから4バイトのハッシュ(CRC32)を生成
    // 文字列indexの検索を行う場合、文字列比較するよりCRC32ハッシュの比較を行うほうが速い
    // ただし偶然一致する可能性(16の8乗分の1)もある
    u32 getCRC32(const char *buffer, u32 bufferlen=u32(-1), u32 crc32_start=0xffffff);
    
    
    // Base64エンコード・デコード
    string base64encode(const char *data, u32 size);
    u32 base64decode(char *dest, const string &data); // デコードされたデータバイト数が返る
}
