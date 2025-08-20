#include <grrlib.h>
#include <stdlib.h>
#include <gccore.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <tinyxml2.h>
#include <math.h>
#include <vector>

#include <ogc/lwp_watchdog.h>

#include "fontdef_ttf.h"

using namespace tinyxml2;

typedef struct ImgRect
{
    const char* name;
    float x;
    float y;
    float w;
    float h;
};

int main(int argc, char **argv) {
    WPAD_Init();
    fatInitDefault();
    SYS_STDIO_Report(true);
    GRRLIB_Init();

    // XML
    XMLDocument doc;
    doc.LoadFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.xml");
    
    std::vector<ImgRect> subtextures;
    XMLElement *root = doc.RootElement();
    XMLElement *subtexture = root->FirstChildElement("SubTexture");
    while (subtexture) {
        ImgRect rect;
        subtexture->QueryStringAttribute("name", &rect.name);
        subtexture->QueryFloatAttribute("x", &rect.x);
        subtexture->QueryFloatAttribute("y", &rect.y);
        subtexture->QueryFloatAttribute("width", &rect.w);
        subtexture->QueryFloatAttribute("height", &rect.h);
        subtextures.push_back(rect);
        subtexture = subtexture->NextSiblingElement("SubTexture");
    }

    // Image
    GRRLIB_texImg *tex_test = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.png");

    // Fonts
    GRRLIB_ttfFont *font = GRRLIB_LoadTTF(fontdef_ttf, fontdef_ttf_size);

    int frameCount = 0;

    u64 lastAnimTick = gettime();
    const u64 animInterval = secs_to_ticks(1) / 24;
    size_t animFrameIndex = 0;

    ImgRect currentRect = subtextures.empty() ? ImgRect{"",0,0,0,0} : subtextures[0];

    // Loop
    while(1) {

        if (!subtextures.empty()) {
            u64 now = gettime();
            if (now - lastAnimTick >= animInterval) {
                do {
                    animFrameIndex = (animFrameIndex + 1) % subtextures.size();
                    lastAnimTick += animInterval;
                } while (now - lastAnimTick >= animInterval);
                currentRect = subtextures[animFrameIndex];
            }
        }

        WPAD_ScanPads();
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;

        GRRLIB_FillScreen(0xBABABAFF);

        GRRLIB_DrawPart(200, 100, currentRect.x, currentRect.y, currentRect.w, currentRect.h, tex_test, 0, 1, 1, 0xFFFFFFFF);

        GRRLIB_PrintfTTF(0, 0, font, "Friday Night Funkin", 24, 0x000000FF);
        GRRLIB_PrintfTTF(0, 450, font, currentRect.name, 24, 0x000000FF);

        GRRLIB_Render();

        frameCount++;
    }

    GRRLIB_FreeTexture(tex_test);
    GRRLIB_FreeTTF(font);
    GRRLIB_Exit();
    exit(0);
}