#include "base.h"
#include <fcntl.h>

#ifdef _WINDOWS
    #include <conio.h>
    #include <io.h>
#else
    #include <termios.h>
#endif

namespace Aula {
    namespace Console{
        #ifdef _WINDOWS
            static i16 g_curAttr = WHITE; // 現在のコンソールテキスト属性
        #endif
        
        bool setAttribute(i8 wFore, i8 wBack, bool bHigh, bool bUnderscore) {
            #ifdef _WINDOWS
                return FALSE != SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    g_curAttr = (wFore | (wBack*16) | (bHigh? FOREGROUND_INTENSITY: 0)
                        | (bUnderscore? COMMON_LVB_UNDERSCORE: 0)));
            #else
                static const i8 col[] = {0, 4, 2, 6, 1, 5, 3, 7};
                return 0 < printf("\033[3%dm\033[4%dm%s%s", col[wFore], col[wBack],
                    bHigh? "\033[1m": "", bUnderscore? "\033[4m": "");
            #endif
        }
        
        bool setCursorPosition(i16 shXPos, i16 shYPos) {
            #ifdef _WINDOWS
                COORD    coord;
                
                coord.X = shXPos;
                coord.Y = shYPos;
                return FALSE != SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            #else
                return 0 < printf("\033[%d;%dH", shXPos, shYPos);
            #endif
        }
        
        bool clear() {
            #ifdef _WINDOWS
                CONSOLE_SCREEN_BUFFER_INFO    csbi;
                u32    dwNumberOfCharsWritten;        // 書き込まれたセル数
                COORD  coord = {0, 0};
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                // コンソールスクリーンバッファに関する情報を取得
                if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return false;
                // バッファ内の指定した座標から指定した数の文字セル分だけ、前景色と背景色を設定
                if (!FillConsoleOutputAttribute(hConsole, g_curAttr,
                    csbi.dwSize.X * csbi.dwSize.Y, coord, &dwNumberOfCharsWritten)) return false;
                // バッファ内の指定した座標から、指定した文字を指定した数だけ書き込む
                return FALSE != FillConsoleOutputCharacter(hConsole, ' ',
                        csbi.dwSize.X * csbi.dwSize.Y, coord, &dwNumberOfCharsWritten);
            #else
                return 0 < printf("\033[2J");
            #endif
        }
        
        bool isKeyPressed() {
            #ifdef _WINDOWS
                return 0 != _kbhit();
            #else
                struct termios oldt, newt;
                i32 ch, oldf;
                
                tcgetattr(STDIN_FILENO, &oldt);
                newt = oldt;
                newt.c_lflag &= ~(ICANON | ECHO);
                tcsetattr(STDIN_FILENO, TCSANOW, &newt);
                oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
                fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
                ch = getchar();
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                fcntl(STDIN_FILENO, F_SETFL, oldf);
                if(ch != EOF){
                    ungetc(ch, stdin);
                    return true;
                }
                return false;
            #endif
        }
        
        i32 getPressedKey() {
            #ifdef _WINDOWS
                return _getch();
            #else
                struct termios oldt, newt;
                i32 ch;
                
                tcgetattr( STDIN_FILENO, &oldt );
                newt = oldt;
                newt.c_lflag &= ~( ICANON | ECHO );
                tcsetattr( STDIN_FILENO, TCSANOW, &newt );
                ch = getchar();
                tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
                return ch;
            #endif
        }
        
        
        #ifdef _WINDOWS
            /*** コンソール表示 ***/
            static BOOL WINAPI HandlerRoutine(DWORD type) { //割り込み制御
                switch (type) {
                case CTRL_C_EVENT:        //Ctrl+Cを受け取った
                case CTRL_BREAK_EVENT:    //Ctrl+Breakを受け取った
                case CTRL_CLOSE_EVENT:    //コンソールを閉じた
                    return TRUE;        //無効にするのでTRUEを返す
                case CTRL_LOGOFF_EVENT:
                case CTRL_SHUTDOWN_EVENT:
                    return FALSE;
                }
                return FALSE;    //それ以外の時は強制終了
            }
            
            void open() {
                if (AllocConsole()) { //コンソール割り当て
                    //標準出力関連付け
                    *stdout = *_fdopen(_open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
                    setvbuf(stdout, nullptr, _IONBF, 0);
                    //標準エラー出力関連付け
                    *stderr = *_fdopen(_open_osfhandle((intptr_t)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT), "w");
                    setvbuf(stderr, nullptr, _IONBF, 0);
                    //標準入力関連付け
                    *stdin = *_fdopen(_open_osfhandle((intptr_t)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r");
                    setvbuf(stdin, nullptr, _IOFBF, 256);
                    //割り込みハンドラ関数追加
                    SetConsoleCtrlHandler(HandlerRoutine, TRUE);
                }
            }
        #endif
    }
}