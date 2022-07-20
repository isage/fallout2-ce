#include "win32.h"

#include "core.h"
#include "main.h"
#include "window_manager.h"

#include <SDL.h>
#include <stdlib.h>

#if defined(__vita__)
#include <psp2/sysmodule.h>
#include <psp2/power.h>
#endif

#ifdef _WIN32
// 0x51E444
bool gProgramIsActive = false;

// GNW95MUTEX
HANDLE _GNW95_mutex = NULL;

// 0x4DE700
int main(int argc, char* argv[])
{
    _GNW95_mutex = CreateMutexA(0, TRUE, "GNW95MUTEX");
    if (GetLastError() == ERROR_SUCCESS) {
        SDL_ShowCursor(SDL_DISABLE);

        gProgramIsActive = true;
        falloutMain(argc, argv);

        CloseHandle(_GNW95_mutex);
    }
    return 0;
}
#else
bool gProgramIsActive = false;

int main(int argc, char* argv[])
{
#if __APPLE__
    char* basePath = SDL_GetBasePath();
    chdir(basePath);
    SDL_free(basePath);
#endif

#if defined(__vita__)
    chdir("ux0:/data/fallout2/");
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME);
    SDL_SetHintWithPriority(SDL_HINT_TOUCH_MOUSE_EVENTS, "0", SDL_HINT_OVERRIDE);
    scePowerSetArmClockFrequency(444);
    scePowerSetGpuClockFrequency(222);
#endif

    SDL_ShowCursor(SDL_DISABLE);
    gProgramIsActive = true;
    return falloutMain(argc, argv);
}
#endif
