#pragma once

#include "texture.hpp"
#include <functional>

namespace Aula {
    namespace SDL {
        /// ウィンドウ設定構造体
        struct WindowConfig {
            std::string title;        // ウィンドウタイトル
            Point       position;     // Point(-1, -1) で中央表示
            Size        size;         // ウィンドウサイズ (default: 800x600)
            bool        isFullscreen; // フルスクリーンモード (default: false)
            bool        isResizable;  // ウィンドウサイズ可変モード (default: false)
            std::string renderer;     // 使用する描画エンジン: "direct3d", "opengl" (default), "opengles2", "software" ...

            WindowConfig() {
                title = "SDL_Window";
                position.x = -1, position.y = -1;
                size.width = 800, size.height = 600;
                isFullscreen = false;
                isResizable = false;
                renderer = "opengl";
            }
        };

        /// SDL開始
        inline bool initialize() {
            SDL_SetMainReady();
            return SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) == 0
                && TTF_Init() == 0;
            // // SDL_mixer も一緒に初期化
            // return Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == 0;
        }
        
        /// SDL終了
        inline void quit() {
            SDL_Quit();
        }
        
        /// SDLエラーメッセージ取得
        inline std::string getLastError() {
            return SDL_GetError();
        }

        /// ウィンドウ作成
        bool createWindow(const WindowConfig &config);

        /// ウィンドウ削除
        void destroyWindow();

        /// ウィンドウ取得
        SDL_Window *getWindowHandle();

        /// レンダラー取得
        SDL_Renderer *getRendererHandle();

        /// レンダラー名取得
        const std::string &getRendererName();

        /// ウィンドウモード切り替え. (true: Window, false: Fullscreen)
        bool setWindowMode(bool flag);
        
        /// アイコン設定
        bool setIcon(const IO::Binary &imgdata);

        /// 現在の描画対象スクリーンをクリア
        bool clearScreen(const Color &color = Color(0, 0, 0, 255));
        
        /// ブレンドモード変更
        bool setBlendMode(u8 mode = BLEND_ALPHA);

        /// "TEXTURE_TARGET"タイプで生成したテクスチャを描画対象にする
        // nullptrを指定すると裏画面が描画対象
        bool setRenderTarget(Texture *texture = nullptr);
        
        
        /*** イベント処理 ***/
        
        /// デフォルトイベントプロシージャ
        // ×ボタンでの終了処理、マウスホイール処理
        bool defaultEventProcedure(Event *ev);

        /// whileループで使用。ウィンドウイベント処理
        bool pollEvent(const std::function<bool(Event *ev)> &eventProc = defaultEventProcedure);
        
        /// イベントを発生させる
        inline bool pushEvent(Event *ev) {
            return 0 == SDL_PushEvent((SDL_Event*)ev);
        }
        
        
        /*** 入力関係 ***/

        /// キー・マウス繰り返し入力モード移行タイムアウト設定 [ms] (default: 500 ms)
        void setKeyRepeatTime(u32 time);

        /// キー・マウス繰り返し入力モード移行タイムアウト取得 [ms]
        u32 getKeyRepeatTime();

        /// キー入力状態取得
        // @return 0: Not input, 1: Pressed, 2: Is down, 3: Repeat mode
        u8 getKeyState(u32 keycode);

        /// キー入力送信
        // @param state: 0: Not input, 1: Pressed, 2: Is down, 3: Repeat mode
        void sendKeyState(u32 keycode, u8 state);
        
        /// マウス入力状態取得
        // @return 0: Not input, 1: Pressed, 2: Is down, 3: Repeat mode
        u8 getMouseState(u32 mousecode);
        
        /// マウス入力送信
        // @param state: 0: Not input, 1: Pressed, 2: Is down, 3: Repeat mode
        void sendMouseState(u32 mousecode, u8 state);
        
        /// マウス移動量取得
        Point getMouseMove();
        
        /// マウス位置取得
        Point getMousePosition();
        
        /// マウスが移動したか
        bool isMouseMoved();
        
        /// マウスがワープしたか = warpMouse() で移動したか
        bool isMouseWarped();
        
        /// マウスホイール移動量取得
        Point getMouseWheel();
        
        /// マウスカーソル可視設定
        inline void showMouse(bool visible = true) {
            SDL_ShowCursor(visible);
        }
        
        /// マウスカーソルをcurrentウィンドウの指定位置に移動
        void warpMouse(i32 x, i32 y);
        
        
        /** TextInput関連 **/
        inline void startTextInput() {
            SDL_StartTextInput();
        }
        
        inline bool isTextInputActive() {
            return SDL_TRUE == SDL_IsTextInputActive();
        }
        
        inline void stopTextInput() {
            SDL_StopTextInput();
        }
        
        
        /*** クリップボード関連 ***/
        inline bool setClipboardText(const std::string &text) {
            return 0 == SDL_SetClipboardText(text.c_str());
        }
        
        inline std::string getClipboardText() {
            char *str = SDL_GetClipboardText();
            if (str) {
                std::string ret = str;
                SDL_free(str);
                return std::move(ret);
            }
            return "";
        }
        
        inline bool hasClipboardText() {
            return SDL_TRUE == SDL_HasClipboardText();
        }


        /*** 図形関連 ***/

        /// 画面上の指定範囲をRGBデータとして取得
        std::unique_ptr<IO::Binary> readPixels(u32 x, u32 y, u32 width, u32 hight);

        /// 画面上のピクセルをRGBデータとして取得
        Color readPixel(u32 x, u32 y);

        /// 点描画
        bool drawPixel(i32 x, i32 y, const Color &color);

        /// 線描画
        bool drawLine(i32 x1, i32 y1, i32 x2, i32 y2, const Color &color);

        /// 矩形描画
        bool drawRect(i32 x, i32 y, i32 width, i32 height, const Color &color);

        /// 矩形塗りつぶし
        bool fillRect(i32 x, i32 y, i32 width, i32 height, const Color &color);
    }
}
