#include "sparrowtest.h"

// Libs
#include <grrlib.h>
#include "FinEngine.h"
#include <tinyxml2.h>
#include <asndlib.h>
#include "../oggplayer.h"

// OS
#include <stdlib.h>
#include <gccore.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <math.h>
#include <vector>
#include <ogc/lwp_watchdog.h>
#include <malloc.h>

// Data
#include "fontdef_ttf.h"
#include "sample_ogg.h"

// Namespaces
using namespace tinyxml2;

// This is for the sparrow V2 frames
typedef struct ImgRect
{
    const char* name;
    float x;
    float y;
    float w;    // Width
    float h;    // Height
    float fx;   // Frame X
    float fy;   // Frame Y
    float fw;   // Frame Width
    float fh;   // Frame Height
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
    // Load files
    font = GRRLIB_LoadTTF(fontdef_ttf, fontdef_ttf_size);
    tex_test = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.png");
    doc.LoadFile("sd:/fnfwii/images/characters/boyfriend/boyfriend_main.xml");

    PlayOgg(sample_ogg, sample_ogg_size, 0, OGG_INFINITE_TIME);

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
        subtexture->QueryFloatAttribute("frameX", &rect.fx);
        subtexture->QueryFloatAttribute("frameY", &rect.fy);
        subtextures.push_back(rect);
        subtexture = subtexture->NextSiblingElement("SubTexture");
    }
    currentRect = subtextures.empty() ? ImgRect{"",0,0,0,0} : subtextures[0];
}

// Update code
void SparrowTestState::update() {
    WPAD_ScanPads();

    // Exit code
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        finengine::FinGame::instance().exit();
    }

    // Sparrow anim stuff
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


    GRRLIB_DrawPart(200-currentRect.fx, 100-currentRect.fy, currentRect.x, currentRect.y, currentRect.w, currentRect.h, tex_test, 0, 1, 1, 0xFFFFFFFF);
    GRRLIB_Rectangle(200 - currentRect.fx, 100 - currentRect.fy, currentRect.w, currentRect.h, 0xFF0000FF, false);

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
