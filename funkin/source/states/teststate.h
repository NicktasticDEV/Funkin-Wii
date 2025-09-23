#pragma once
#include "FinEngine.h"

#include <grrlib.h>

class TestState : public finengine::FinState {
    private:

    public:
        void init() override;
        void update() override;
        void render() override;
        void cleanup() override;
};