#include "titlestate.h"

#include <grrlib.h>
#include <romfs-ogc.h>
#include <wiiuse/wpad.h>
#include <math.h>
#include <stdio.h>

namespace
{
    GRRLIB_texImg *logo;
    GRRLIB_texImg *bg;

    int frameCount = 0;
    float logoY;
    float logoYDelay;
}

void TitleState::init() {
    romfsInit();
    WPAD_Init();

    logo = GRRLIB_LoadTextureFromFile("romfs:/images/logo.png");
    bg = GRRLIB_LoadTextureFromFile("romfs:/images/titlebg.png");
}

void TitleState::update() {
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

void TitleState::render() {
    GRRLIB_FillScreen(0xFFFFFFFF);

    GRRLIB_DrawImg(0, 0, bg, 0, 1, 1, 0xFFFFFFFF);
    GRRLIB_DrawImg(56, logoYDelay, logo, 0, 1, 1, 0x000000FF);
    GRRLIB_DrawImg(56, logoY, logo, 0, 1, 1, 0xFFFFFFFF);

    GRRLIB_Render();
}

void TitleState::cleanup() {
    GRRLIB_FreeTexture(logo);
    GRRLIB_FreeTexture(bg);
    romfsExit();
}