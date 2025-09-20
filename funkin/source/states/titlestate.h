#pragma once
#include "FinEngine.h"

#include <grrlib.h>

class TitleState : public finengine::FinState {
    private:
        GRRLIB_texImg *logo;
        GRRLIB_texImg *bg;

        int frameCount = 0;
        float logoY;
        float logoYDelay;

    public:
        void init() override;
        void update() override;
        void render() override;
        void cleanup() override;
};