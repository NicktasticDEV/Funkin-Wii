#pragma once
#include "FinEngine.h"

#include <grrlib.h>
#include <tinyxml2.h>
#include <stdlib.h>
#include <vector>
#include <ogc/lwp_watchdog.h>

using namespace tinyxml2;

class TestState : public finengine::FinState {
    private:
        struct ImgRect
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

        XMLDocument doc;
        std::vector<ImgRect> subtextures;
        GRRLIB_texImg *tex_test;
        GRRLIB_ttfFont *font;
        int frameCount = 0;
        u64 lastAnimTick;
        const u64 animInterval = secs_to_ticks(1) / 24;
        size_t animFrameIndex = 0;
        ImgRect currentRect;
        bool loadSuccess = false;

    public:
        void init() override;
        void update() override;
        void render() override;
        void cleanup() override;
};