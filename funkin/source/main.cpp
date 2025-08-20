#include <grrlib.h>
#include <stdlib.h>
#include <gccore.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <tinyxml2.h>

using namespace tinyxml2;

int main(int argc, char **argv) {
    WPAD_Init();
    fatInitDefault();
    SYS_STDIO_Report(true);

    GRRLIB_Init();

    // XML
    XMLDocument doc;
    doc.LoadFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.xml");

    // Image
    GRRLIB_texImg *tex_test = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.png");

    // Loop
    while(1) {

        WPAD_ScanPads();
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
        GRRLIB_FillScreen(0xBABABAFF);

        GRRLIB_DrawPart(0,0, 1, 1, 254, 257, tex_test, 0, 1, 1, 0xFFFFFFFF);

        GRRLIB_Render();
    }

    GRRLIB_FreeTexture(tex_test);
    GRRLIB_Exit();
    exit(0);
}