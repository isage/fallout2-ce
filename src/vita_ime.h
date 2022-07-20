#ifndef VITA_IME_H
#define VITA_IME_H

#if defined(__vita__)
#include <psp2/libime.h>

extern int ime_active;

void showVitaIme();
#endif

#endif