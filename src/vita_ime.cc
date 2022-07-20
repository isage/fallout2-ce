#if defined(__vita__)
#include "vita_ime.h"
#include <SDL.h>
#include <psp2/kernel/clib.h>

#if !defined(SCE_IME_LANGUAGE_ENGLISH_US)
#define SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#endif

SceWChar16 libime_out[SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1];
static char libime_initval[8] = { 1 };
SceImeCaret caret_rev;
int ime_active = 0;

void VITA_ImeEventHandler(void *arg, const SceImeEventData *e)
{
    switch (e->id) {
        case SCE_IME_EVENT_UPDATE_TEXT:
            if (e->param.text.caretIndex == 0)
            {
                SDL_Event nevent;
                nevent.type = SDL_KEYDOWN;
                nevent.key.keysym.sym = SDLK_BACKSPACE;
                nevent.key.keysym.mod = KMOD_NONE;
                nevent.key.keysym.scancode = SDL_SCANCODE_BACKSPACE;
                nevent.key.state = SDL_PRESSED;
                SDL_PushEvent(&nevent);

                nevent.type = SDL_KEYUP;
                nevent.key.keysym.sym = SDLK_BACKSPACE;
                nevent.key.keysym.mod = KMOD_NONE;
                nevent.key.keysym.scancode = SDL_SCANCODE_BACKSPACE;
                nevent.key.state = SDL_RELEASED;
                SDL_PushEvent(&nevent);
                sceImeSetText((SceWChar16 *)libime_initval, 4);
            }
            else
            {
                uint16_t lower = sceClibTolower(*(SceWChar16 *)&libime_out[1]);
                if (lower > 0)
                {
                    SDL_Event nevent;
                    nevent.type = SDL_KEYDOWN;
                    nevent.key.keysym.sym = lower;
                    nevent.key.keysym.mod = KMOD_NONE;
                    nevent.key.keysym.scancode = SDL_GetScancodeFromKey(lower);
                    nevent.key.state = SDL_PRESSED;
                    SDL_PushEvent(&nevent);

                    nevent.type = SDL_KEYUP;
                    nevent.key.keysym.sym = lower;
                    nevent.key.keysym.mod = KMOD_NONE;
                    nevent.key.keysym.scancode = SDL_GetScancodeFromKey(lower);
                    nevent.key.state = SDL_RELEASED;
                    SDL_PushEvent(&nevent);
                }

                SDL_memset(&caret_rev, 0, sizeof(SceImeCaret));
                SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1) * sizeof(SceWChar16)));
                caret_rev.index = 1;
                sceImeSetCaret(&caret_rev);
                sceImeSetText((SceWChar16 *)libime_initval, 4);
            }
            break;
        case SCE_IME_EVENT_PRESS_ENTER:
        {
            SDL_Event nevent;
            nevent.type = SDL_KEYDOWN;
            nevent.key.keysym.sym = SDLK_RETURN;
            nevent.key.keysym.mod = KMOD_NONE;
            nevent.key.keysym.scancode = SDL_SCANCODE_RETURN;
            nevent.key.state = SDL_PRESSED;
            SDL_PushEvent(&nevent);

            nevent.type = SDL_KEYUP;
            nevent.key.keysym.sym = SDLK_RETURN;
            nevent.key.keysym.mod = KMOD_NONE;
            nevent.key.keysym.scancode = SDL_SCANCODE_RETURN;
            nevent.key.state = SDL_RELEASED;
            SDL_PushEvent(&nevent);
            break;
        }
        case SCE_IME_EVENT_PRESS_CLOSE:
            sceImeClose();
            ime_active = 0;
            break;
    }
}

void showVitaIme()
{
    if (!ime_active)
    {
        SceUInt32 libime_work[SCE_IME_WORK_BUFFER_SIZE / sizeof(SceInt32)];
        SceImeParam param;

        sceImeParamInit(&param);

        SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1) * sizeof(SceWChar16)));

        param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
        param.languagesForced = SCE_FALSE;
        param.type = SCE_IME_TYPE_BASIC_LATIN;
        param.option = SCE_IME_OPTION_NO_ASSISTANCE;
        param.inputTextBuffer = libime_out;
        param.maxTextLength = SCE_IME_MAX_TEXT_LENGTH;
        param.handler = VITA_ImeEventHandler;
        param.filter = NULL;
        param.initialText = (SceWChar16 *)libime_initval;
        param.arg = NULL;
        param.work = libime_work;

        int res = sceImeOpen(&param);
        if (res < 0) {
          sceClibPrintf("Failed to init IME\n");
        }
        ime_active = 1;
    }
}
#endif
