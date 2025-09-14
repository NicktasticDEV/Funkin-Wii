#include "teststate.h"

#include "FinEngine.h"
#include <grrlib.h>

#include <romfs-ogc.h>

#include <wiiuse/wpad.h>
#include <stdio.h>


namespace
{
    GRRLIB_texImg *logo;
}

void TestState::init() {

    int res = romfsInit();
    if (res)
    {
        printf("romfsInit failed: %d\n", res);
    }
    else
    {
        printf("romfsInit succeeded\n");
    }

    logo = GRRLIB_LoadTextureFromFile("romfs:/images/logo.png");
}

void TestState::update() {
    WPAD_ScanPads();

    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        finengine::FinGame::instance().exit();
    }

}

void TestState::render() {
    GRRLIB_FillScreen(0xAAAAAAFF);
    GRRLIB_DrawImg(100, 100, logo, 0, 1, 1, 0xFFFFFFFF);

    GRRLIB_Render();
}

void TestState::cleanup() {
    GRRLIB_FreeTexture(logo);
    romfsExit();
}