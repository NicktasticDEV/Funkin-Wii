#include "titletest.h"

#include <grrlib.h>

#include <wiiuse/wpad.h>
#include <math.h>
#include <ogc/lwp_watchdog.h>

#include <asndlib.h>
#include "../oggplayer.h"

#include "fontdef_ttf.h"
#include "sample_ogg.h"

namespace
{
    GRRLIB_texImg *logo;
    GRRLIB_texImg *bg;
    GRRLIB_ttfFont *font;

    int frameCount = 0;
    float logoY;
    float logoYDelay;
}

void TitleTestState::init() {
    logo = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/logo.png");
    bg = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/titlebg.png");
    font = GRRLIB_LoadTTF(fontdef_ttf, fontdef_ttf_size);

    PlayOgg(sample_ogg, sample_ogg_size, 0, OGG_INFINITE_TIME);
}

void TitleTestState::update() {
    WPAD_ScanPads();
    // Exit code
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        finengine::FinGame::instance().exit();
    }
    // Logo Y position update
    float amplitude = 18.0f;
    float frequency = 0.09f;

    logoY = 87 + sin(frameCount * frequency) * amplitude;
    logoYDelay = 87 + sin((frameCount + 8) * frequency) * amplitude;
    frameCount++;
}

void TitleTestState::render() {
    GRRLIB_FillScreen(0xFFFFFFFF);

    GRRLIB_DrawImg(0, 0, bg, 0, 1, 1, 0xFFFFFFFF);
    GRRLIB_DrawImg(56, logoYDelay, logo, 0, 1, 1, 0x000000FF);
    GRRLIB_DrawImg(56, logoY, logo, 0, 1, 1, 0xFFFFFFFF);

    //GRRLIB_PrintfTTF(0, 0, font, "Friday Night Funkin' Wii Demo", 12, 0xFFFFFFFF);


    GRRLIB_Render();
}

void TitleTestState::cleanup() {
    GRRLIB_FreeTexture(logo);
}