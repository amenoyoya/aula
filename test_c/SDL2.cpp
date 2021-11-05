#include <aula/sdl/application.hpp>

#ifdef _MSC_VER
    #pragma comment(lib, "libaula_sdl.lib")
    #pragma comment(lib, "SDL2.lib")
    #pragma comment(lib, "SDL2main.lib")
    #pragma comment(lib, "SDL2_ttf.lib")
    #pragma comment(lib, "SDL2_image.lib")

    #pragma comment(lib, "user32.lib")
    #pragma comment(lib, "shell32.lib")
    #pragma comment(lib, "shlwapi.lib")
    #pragma comment(lib, "winmm.lib")
    #pragma comment(lib, "imm32.lib")
    #pragma comment(lib, "advapi32.lib")
    #pragma comment(lib, "gdi32.lib")
    #pragma comment(lib, "ole32.lib")
    #pragma comment(lib, "oleaut32.lib")
    #pragma comment(lib, "version.lib")
    #pragma comment(lib, "setupapi.lib")
#endif

#ifdef _MSC_VER
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    Aula::SDL::WindowConfig config;

    config.title = _U8("✅SDLウィンドウ");

    // プログラムの終了時に Aula::SDL::destroyWindow, Aula::SDL::quit を呼ぶ
    atexit(Aula::SDL::quit);
    atexit(Aula::SDL::destroyWindow);

    if (!Aula::SDL::initialize() || !Aula::SDL::createWindow(config)) {
        Aula::IO::Stderr->write(Aula::SDL::getLastError());
        return 1;
    }
    Aula::IO::Stdout->write("current renderer: " + Aula::SDL::getRendererName());

    Aula::SDL::Font font("C:\\Windows\\Fonts\\meiryo.ttc", 24);
    if (font.getState() == Aula::Object::State::FAILED) {
        Aula::IO::Stderr->write(Aula::SDL::getLastError());
        return 1;
    }
    Aula::SDL::Texture message(font, _U8("⭕こんにちは世界🌏"));

    while (Aula::SDL::pollEvent()) {
        if (!Aula::SDL::setRenderTarget() || !Aula::SDL::clearScreen(Aula::SDL::Color(0, 0, 125))) {
            Aula::IO::Stderr->write(Aula::SDL::getLastError());
            break;
        }
        message.draw(50, 50);
    }
    return 0;
}