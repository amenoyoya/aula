#define UNICODE
#define SDL_MAIN_HANDLED // デスクトップ環境ならSDLのmain関数は使わない

#include <SDL.h>
#include <cstdio>

#ifdef _MSC_VER
    #pragma comment(lib, "SDL2.lib")
    #pragma comment(lib, "SDL2main.lib")

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
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "failed to initialize SDL\n");
        return 1;
    }
    if (nullptr == (window = SDL_CreateWindow("SDL get started", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN))) {
        fprintf(stderr, "failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}