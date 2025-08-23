#include "sparrowtest.h"

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

#include "FinEngine.h"

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

// Variables
namespace
{
    XMLDocument doc;
    std::vector<ImgRect> subtextures;
    GRRLIB_texImg *tex_test;
    GRRLIB_ttfFont *font;
    int frameCount = 0;
    u64 lastAnimTick = gettime();
    const u64 animInterval = secs_to_ticks(1) / 24;
    size_t animFrameIndex = 0;
    ImgRect currentRect;

    bool loadSuccess = false;
}

// Initialization code
void SparrowTestState::init() {
    // Initialize systems
    WPAD_Init();
    fatInitDefault();
    SYS_STDIO_Report(true);
    GRRLIB_Init();

    // Load files
    font = GRRLIB_LoadTTF(fontdef_ttf, fontdef_ttf_size);
    tex_test = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.png");
    doc.LoadFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.xml");

    // Parse XML
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
    currentRect = subtextures.empty() ? ImgRect{"",0,0,0,0} : subtextures[0];
}

// Update code
void SparrowTestState::update() {
    WPAD_ScanPads();

    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        finengine::FinGame::instance().exit();
    }

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
}

// Render code
void SparrowTestState::render() {
    GRRLIB_FillScreen(0xBABABAFF);
    GRRLIB_PrintfTTF(0, 0, font, "Friday Night Funkin", 24, 0x000000FF);


    GRRLIB_DrawPart(200, 100, currentRect.x, currentRect.y, currentRect.w, currentRect.h, tex_test, 0, 1, 1, 0xFFFFFFFF);
    GRRLIB_PrintfTTF(0, 450, font, currentRect.name, 24, 0x000000FF);

    GRRLIB_Render();

    frameCount++;
}

// Cleanup code
void SparrowTestState::cleanup() {
    GRRLIB_FreeTTF(font);
    GRRLIB_FreeTexture(tex_test);
    GRRLIB_Exit();
    subtextures.clear();
}
