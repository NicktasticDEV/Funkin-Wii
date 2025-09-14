#pragma once
#include "FinEngine.h"

class TestState : public finengine::FinState {
    public:
        void init() override;
        void update() override;
        void render() override;
        void cleanup() override;
};