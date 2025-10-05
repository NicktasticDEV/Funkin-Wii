#include "teststate.h"

// Libs
#include <grrlib.h>
#include "FinEngine.h"
#include <tinyxml2.h>
#include <romfs-ogc.h>

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

// Namespaces
using namespace tinyxml2;

// Initialization code
void TestState::init() {
    printf("TestState Init\n");

    lastAnimTick = gettime();

    // Load font from romfs
    font = GRRLIB_LoadTTFFromFile("romfs:/fonts/fontdef.ttf");
    if (!font) {
        printf("Failed to load font\n");
    }

    tex_test = GRRLIB_LoadTextureFromFile("romfs:/images/characters/boyfriend/boyfriend_main.png");
    if (!tex_test) {
        printf("Failed to load texture\n");
    }

    doc.LoadFile("romfs:/images/characters/boyfriend/boyfriend_main.xml");
    if (doc.ErrorID() != 0) {
        printf("Failed to load XML: %d\n", doc.ErrorID());
        return;
    }

    printf("Loading done\n");

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
void TestState::update() {
    WPAD_ScanPads();

    // Exit code
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        finengine::FinGame::instance().Exit();
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
void TestState::render() {
    GRRLIB_2dMode();


    GRRLIB_FillScreen(0xBABABAFF);
    GRRLIB_PrintfTTF(0, 0, font, "Friday Night Funkin", 24, 0x000000FF);


    GRRLIB_DrawPart(200-currentRect.fx, 100-currentRect.fy, currentRect.x, currentRect.y, currentRect.w, currentRect.h, tex_test, 0, 1, 1, 0xFFFFFFFF);
    GRRLIB_Rectangle(200 - currentRect.fx, 100 - currentRect.fy, currentRect.w, currentRect.h, 0xFF0000FF, false);

    GRRLIB_PrintfTTF(0, 450, font, currentRect.name, 24, 0x000000FF);

    GRRLIB_Render();

    frameCount++;
}

// Cleanup code
void TestState::cleanup() {
    GRRLIB_FreeTTF(font);
    GRRLIB_FreeTexture(tex_test);
    GRRLIB_Exit();
    subtextures.clear();
}
