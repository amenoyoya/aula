#pragma once

#include "seekfrom.h"

namespace Aula {
    namespace IO {
        /// バイナリ管理クラス
        class Binary: public Object {
        public:
            /// バイナリ管理モード
            enum Mode {
                CONTROL = 1,
                ALLOCATE = 5,
            };

            Binary(): Object(), ptr(nullptr), pos(0) {}
            explicit Binary(void *p): Object(), ptr(nullptr), pos(0) {
                set(p);
            }
            explicit Binary(u32 size): Object(), ptr(nullptr), pos(0) {
                allocate(size);
            }
            explicit Binary(const void *data, u32 size): Object(), ptr(nullptr), pos(0) {
                push(data, size);
            }
            ~Binary(){
                release();
            }
            
            /// ポインタ直接制御モード(Mode.CONTROL)で対象バイナリを管理
            void set(void *p);
            
            /// メモリ割り当てモード(Mode.ALLOCATE)で空のバイナリオブジェクトを生成
            void allocate(u32 size);
            
            /// メモリサイズ変更
            // ポインタ位置は先頭に変更される
            void resize(u32 size); // only Mode.ALLOCATE or NONE
            
            /// メモリ解放
            void release();
            
            /// サイズは変えず、メモリの割当てのみ行う
            // 追加するバイナリの大きさがある程度分かっているなら
            // reserveしてからpush～していく方が高速
            void reserve(u32 size) { // only Mode.ALLOCATE
                if (_state == Mode::ALLOCATE) bin.reserve(size);
            }
            
            /// 指定indexの 8bit data を参照
            i8& operator [](u32 i){ return ptr[i]; }
            
            /// 指定位置からのポインタ取得
            const void *getPointer(u32 head = 0) const {
                return (const void *)(ptr + head);
            }
            
            /// バイナリサイズ取得
            u32 getSize() const { // only Mode.ALLOCATE
                return _state == Mode::ALLOCATE? bin.size(): 0;
            }

            /// 現在のポインタ位置取得
            const u32 &getPosition() const { return pos; }
            
            /// バイナリデータを後ろに追加
            void push(const void *data, u32 size); // only Mode.ALLOCATE
            
            /// 数値をバイナリとして追加
            void pushValue(i32 data, u8 size = 4) { // only Mode.ALLOCATE
                push(&data, size);
            }

            /// 倍精度数値をバイナリとして追加
            // precision: 精度(default: 6)
            void pushNumber(double data, u8 precision = 6) { // only Mode.ALLOCATE
                pushStringData(String::toString(data, precision));
            }
            
            /// 文字列をバイナリとして追加
            void pushString(const std::string &data, u32 size = u32(-1)) {
                push(data.c_str(), size == u32(-1)? data.size(): size);
            }

            /// 文字列を文字数と一緒に追加
            void pushStringData(const std::string &data) {
                pushValue(data.size());
                pushString(data);
            }
            
            /// バイナリの現在位置から数値を取り出す
            template<typename T>
            T getValue() {
                T buf = 0;
                
                memcpy(&buf, ptr + pos, sizeof(T));
                seek(sizeof(T), SEEK_CUR);
                return buf;
            }
            i32 getI32() {
                return getValue<i32>();
            }
            u32 getU32() {
                return getValue<u32>();
            }
            i16 getI16() {
                return getValue<i16>();
            }
            u16 getU16() {
                return getValue<u16>();
            }
            i8 getI8() {
                return getValue<i8>();
            }
            u8 getU8() {
                return getValue<u8>();
            }
            double getNumber() {
                return strtod(getStringData().c_str(), nullptr);
            }
            
            /// ポインタを文字列として取得
            std::string toString(u32 head = 0) {
                return (const char*)getPointer(head);
            }

            /// バイナリの現在位置からsize分の文字列を取り出す
            std::string getString(u32 size);
            
            /// バイナリの現在位置からpushStrDataで入れた文字列を取り出す
            std::string getStringData() {
                u32 size = getU32();
                return getString(size);
            }
            
            /// バイナリの現在位置からsize文のバッファを取り出す
            // ポインタ位置は size 分進む
            const void *get(u32 size);
            
            /// 読み込み位置を変更する
            void seek(i32 mov, u8 mode = SeekFrom::HEAD);
            
            /// バイナリをキー文字列で簡易暗号化・復号化
            // only BINARY_ALLOCATE
            void encode(const std::string &key, u32 keysize=16);
            bool decode(const std::string &key, u32 keysize=16); // 暗号化時のキーと異なるキーが指定されると失敗

            /// 現在の状態を分岐取得
            virtual u8 getState() {
                if (_state == Mode::ALLOCATE && pos >= bin.size()) return FINISHED;
                return _state;
            }
            
            /// @static バイナリデータから4バイトのハッシュ(CRC32)を生成
            // 文字列indexの検索を行う場合、文字列比較するよりCRC32ハッシュの比較を行うほうが速い
            // ただし偶然一致する可能性(16の8乗分の1)もある
            static u32 getCRC32(const void *buffer, u32 bufferlen, u32 crc32_start=0xffffff);
        private:
            char         *ptr;
            std::string   bin;
            u32           pos;
        };
    }
}
