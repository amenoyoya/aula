#pragma once

#include "types.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <ctime>

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
        virtual u8 getState() {
            return this->_state;
        }

        /// オブジェクトのメッセージ取得
        virtual std::string getMessage() {
            return this->_message;
        }
    protected:
        u8           _state;    // 状態
        std::string  _message;  // メッセージ
    };
}
