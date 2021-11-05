#include <aula/sdl/application.hpp>

namespace Aula {
    namespace SDL {
        // 描画対象が Window かどうか
        static bool _renderTarget = false;
        
        // 描画対象テクスチャの高さ
        static u32 _renderTargetHeight = 0;
        
        // キー・マウス入力タイマー
        static u32 _keyTimer[285], _mouseTimer[3];
        
        // キー・マウス繰り返し入力モード移行タイムアウト [ms]
        static u32 _keyRepeatTime = 500;

        // キー・マウス入力状態
        static u8 _key[285], _sendKey[285], _mouse[3], _sendMouse[3];
        
        // マウス移動量
        static Point _mouseMove;
        
        // マウス位置
        static Point _mousePosition;
        
        // マウスが移動（ワープ）したか
        static bool _isMouseMoved = false, _isMouseWarped = false;
        
        // マウスホイール移動量
        static Point _mouseWheel;

        // メインウィンドウ
        static SDL_Window *_window = nullptr;

        // メインレンダラー
        static SDL_Renderer *_renderer = nullptr;

        // メインレンダラー名
        static std::string _rendererName;

        /// @private レンダラードライバー数
        inline u32 getRendererDriverNum() {
            return SDL_GetNumRenderDrivers();
        }
        
        /// @private レンダラードライバー名
        inline std::string getRendererDriverName(u32 index) {
            SDL_RendererInfo info;
            if (0 == SDL_GetRenderDriverInfo(index, &info)) return info.name;
            return "?";
        }
        
        /// @private レンダラードライバーindex取得
        inline i32 getRendererDriverIndex(const std::string &name) {
            u32 n = SDL::getRendererDriverNum();
            
            for (u32 i = 0; i < n; ++i) {
                if (name == getRendererDriverName(i)) return i;
            }
            return -1;
        }

        /// @private レンダラーハンドルからレンダラー名取得
        inline std::string getRendererName(SDL_Renderer *handle) {
            SDL_RendererInfo info;
            if (0 == SDL_GetRendererInfo(handle, &info)) return info.name;
            return "?";
        }

        /// @private 現在の描画対象スクリーンの描画色を設定
        inline bool setColor(const Color &color) {
            return _renderer ? 0 == SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, color.alpha) : false;
        }

        /// @private キー入力状態全取得
        static void getAllKeyStates() {
            const u8 *keyState = SDL_GetKeyboardState(nullptr);
            for (u32 i = 0; i < 285; ++i) {
                if (_sendKey[i] > 0) { // キーエミュレーション
                    _key[i] = _sendKey[i];
                    _sendKey[i] = 0;
                } else { // 実際のキー押下状態取得
                    if (_key[i] == 1) {
                        if (_key[i] < 2) ++_key[i];
                    } else {
                        _key[i] = 0;
                    }
                }
                // キーリピート判定カウンタ処理
                if (_key[i] == 1) {
                    _keyTimer[i] = (u32)clock();
                } else if (_key[i] == 2 && ((u32)clock() - _keyTimer[i]) > _keyRepeatTime) {
                    _key[i] = 3; // _keyRepeatTimeミリ秒以上押しっぱなしなら_key[i]を3にする
                }
            }
        }
        
        /// @private マウス入力状態全取得
        static void getMouseStates(){
            static Point oldPos;
            u32 state = SDL_GetMouseState((int*)&_mousePosition.x, (int*)&_mousePosition.y);
            
            // マウス位置変化量保存
            _mouseMove.x = _mousePosition.x - oldPos.x, _mouseMove.y = _mousePosition.y - oldPos.y;
            oldPos.x = _mousePosition.x, oldPos.y = _mousePosition.y;
            if (_mouseMove.x != 0 || _mouseMove.y != 0) {
                if (!_isMouseWarped) _isMouseMoved = true;
            } else {
                _isMouseMoved = false;
            }
            if (_isMouseWarped) _isMouseWarped = false;
            // 左中右ボタンの状態を検出
            for (u8 i = 0; i < 3; ++i) {
                if (_sendMouse[i] > 0) { // マウスボタンエミュレーション
                    _mouse[i] = _sendMouse[i];
                    _sendMouse[i] = 0;
                } else { // 実際のマウスボタン押下状態取得
                    if (state & SDL_BUTTON(i + 1)) {
                        if (_mouse[i] < 2) ++_mouse[i];
                    } else {
                        _mouse[i] = 0;
                    }
                }
                // キーリピート判定カウンタ処理
                if (_mouse[i] == 1) {
                    _mouseTimer[i] = (u32)clock();
                } else if(_mouse[i] == 2 && ((u32)clock() - _mouseTimer[i]) > _keyRepeatTime) {
                    _mouse[i] = 3; // _keyRepeatTimeミリ秒以上押しっぱなしなら_mouse[i]を3にする
                }
            }
        }


        bool createWindow(const WindowConfig &config) {
            u32 flag = 0;
            if (config.isFullscreen) flag |= SDL_WINDOW_FULLSCREEN;
            if (config.isResizable) flag |= SDL_WINDOW_RESIZABLE;
            
            destroyWindow();
            if (
                nullptr == (_window = SDL_CreateWindow(
                    config.title.c_str(),
                    config.position.x == -1? SDL_WINDOWPOS_CENTERED: config.position.x,
                    config.position.y == -1? SDL_WINDOWPOS_CENTERED: config.position.y,
                    config.size.width,
                    config.size.height,
                    flag
                ))
            ) return false;
            if (
                nullptr == (_renderer = SDL_CreateRenderer(
                    _window, 
                    getRendererDriverIndex(config.renderer),
                    SDL_RENDERER_ACCELERATED
                ))
            ) return false;
            _rendererName = getRendererName(_renderer); // 描画エンジン名保存
            return setBlendMode(BLEND_ALPHA); // アルファブレンディング
        }
        
        void destroyWindow() {
            if (_renderer) {
                SDL_DestroyRenderer(_renderer);
                _renderer = nullptr;
            }
            if (_window) {
                SDL_DestroyWindow(_window);
                _window = nullptr;
            }
        }

        SDL_Window *getWindowHandle() {
            return _window;
        }

        SDL_Renderer *getRendererHandle() {
            return _renderer;
        }

        const std::string &getRendererName() {
            return _rendererName;
        }

        bool setWindowMode(bool flag) {
            return _window ? 0 == SDL_SetWindowFullscreen(_window, flag? 0: SDL_WINDOW_FULLSCREEN) : false;
        }

        bool setIcon(const IO::Binary &imgdata) {
            SDL_Surface *surf = IMG_Load_RW(SDL_RWFromMem((void*)imgdata.getPointer(), imgdata.getSize()), 1);
            if (!_window || !surf) return false;
            SDL_SetWindowIcon(_window, surf);
            SDL_FreeSurface(surf);
            return true;
        }
        
        bool clearScreen(const Color &color) {
            return _window && setColor(color) ? 0 == SDL_RenderClear(_renderer) : false;
        }
        
        bool setBlendMode(u8 mode) {
            return _renderer ? 0 == SDL_SetRenderDrawBlendMode(_renderer, (SDL_BlendMode)mode) : false;
        }

        bool setRenderTarget(Texture *texture) {
            SDL_Texture *tex = texture ? (SDL_Texture*)texture->getHandle(): nullptr;
            if (!_renderer || 0 != SDL_SetRenderTarget(_renderer, tex)) return false;
            
            if (tex) {
                _renderTarget = true;
                _renderTargetHeight = texture->getSize().height;
            } else {
                _renderTarget = false;
            }
            return true;
        }


        bool defaultEventProcedure(Event *ev) {
            switch (ev->type) {
            case QUIT:
                // 終了イベント
                return false;
            case MOUSEWHEEL:
                // マウスホイール量を取得
                _mouseWheel.x = ev->wheel.x, _mouseWheel.y = ev->wheel.y;
                break;
            case WINDOWEVENT:
                // 各ウィンドウ毎のイベント
                if (ev->window.event == WINDOWEVENT_CLOSE) {
                    // ウィンドウを閉じる
                    destroyWindow();
                }
                break;
            }
            return true;
        }

        bool pollEvent(const std::function<bool(Event *ev)> &eventProc) {
            SDL_Event ev;
            if (_renderer && SDL_PollEvent(&ev) && eventProc && !eventProc((Event*)&ev)) return false;
            SDL_RenderPresent(_renderer); // present a back-screen to front-screen
            getAllKeyStates(); // 全キー入力状態取得
            getMouseStates();  // 全マウス入力状態取得
            System::sleep(1);
            return true;
        }


        void setKeyRepeatTime(u32 time) {
            _keyRepeatTime = time;
        }

        u32 getKeyRepeatTime() {
            return _keyRepeatTime;
        }

        u8 getKeyState(u32 keycode) {
            return keycode < 285 ? _key[keycode] : 0;
        }

        void sendKeyState(u32 keycode, u8 state) {
            if (keycode < 285) _sendKey[keycode] = state;
        }
        
        u8 getMouseState(u32 mousecode) {
            return mousecode < 3 ? _mouse[mousecode] : 0;
        }
        
        void sendMouseState(u32 mousecode, u8 state) {
            if (mousecode < 3) _sendMouse[mousecode] = state;
        }
        
        Point getMouseMove() {
            return _mouseMove;
        }
        
        Point getMousePosition() {
            return _mousePosition;
        }
        
        bool isMouseMoved() {
            return _isMouseMoved;
        }
        
        bool isMouseWarped() {
            return _isMouseWarped;
        }
        
        Point getMouseWheel() {
            return _mouseWheel;
        }
        
        void warpMouse(i32 x, i32 y) {
            SDL_WarpMouseInWindow(_window, x, y);
            _isMouseWarped = true;
        }


        /// @private 値の交換
        inline void swap(u8 &a, u8 &b){
            u8 temp = a; a = b, b = temp;
        }
        
        std::unique_ptr<IO::Binary> readPixels(u32 x, u32 y, u32 width, u32 height) {
            if (!_window || !_renderer) return nullptr;

            std::unique_ptr<IO::Binary> binary(new IO::Binary(width * height * 3));
            if (_renderTarget && strncmp(_rendererName.c_str(), "opengl", 6) == 0) {
                // テクスチャに対するreadPixelsでopenglの場合、上下反転
                SDL_Rect rect = { (int)x, (int)(_renderTargetHeight - (y + height)), (int)width, (int)height };
                if (0 != SDL_RenderReadPixels(_renderer, &rect, SDL_PIXELFORMAT_RGB24, (void *)binary->getPointer(), width * 3)) return nullptr;
                // 上下反転
                u8 *bits = (u8*)binary->getPointer();
                for (u32 y = 0; y < height / 2; ++y) {
                    u32 yu = y, yb = height - y - 1;
                    for (u32 x = 0 ; x < width; ++x) {
                        for (u8 i = 0 ; i < 3; ++i) {
                            u32 iu = ( x + yu * width ) * 3 + i,  ib = ( x + yb * width ) * 3 + i;
                            swap(bits[iu] , bits[ib]);
                        }
                    }
                }
                return std::move(binary);
            }
            // 通常readPixels
            SDL_Rect rect = { (int)x, (int)y, (int)width, (int)height };
            return 0 == SDL_RenderReadPixels(_renderer, &rect, SDL_PIXELFORMAT_RGB24, (void *)binary->getPointer(), width * 3)
                ? std::move(binary)
                : nullptr;
        }
        
        Color readPixel(u32 x, u32 y) {
            auto data = readPixels(x, y, 1, 1);
            return data ? Color((*data)[0], (*data)[1], (*data)[2]) : Color(0, 0, 0);
        }
        
        bool drawPixel(i32 x, i32 y, const Color &color) {
            return _renderer ? setColor(color) && 0 == SDL_RenderDrawPoint(_renderer, x, y) : false;
        }
        
        bool drawLine(i32 x1, i32 y1, i32 x2, i32 y2, const Color &color) {
            return _renderer ? setColor(color) && 0 == SDL_RenderDrawLine(_renderer, x1, y1, x2, y2) : false;
        }
        
        bool drawRect(i32 x, i32 y, i32 width, i32 height, const Color &color) {
            SDL_Rect rect = { x, y, width, height };
            return _renderer ? setColor(color) && 0 == SDL_RenderDrawRect(_renderer, &rect) : false;
        }
        
        bool fillRect(i32 x, i32 y, i32 width, i32 height, const Color &color) {
            SDL_Rect rect = { x, y, width, height };
            return _renderer? setColor(color) && 0 == SDL_RenderFillRect(_renderer, &rect) : false;
        }
    }
}
