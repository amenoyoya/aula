#pragma once

#include "types.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

namespace Aula {
    /// 基底クラス
    class Object {
    public:
        /// Objectの状態
        enum State{
            NONE, ACTIVE, FAILED, FINISHED, BUSY
        };
        
        Object(): _state(NONE) {}
        
        /// オブジェクトの状態取得
        static u8 getState(Object *obj) {
            return obj->_getState();
        }

        /// オブジェクトのメッセージ取得
        static string getMessage(Object *obj) {
            return obj->_getMessage();
        }
    protected:
        u8      _state;    // 状態
        string  _message;  // メッセージ
        
        virtual u8 _getState() { return _state; }
        virtual string _getMessage() { return _message; }
    };
}
