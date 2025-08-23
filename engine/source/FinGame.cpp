#include "FinEngine.h"
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <stdio.h>
#include <stdlib.h>

namespace finengine {
    FinGame* FinGame::s_instance = nullptr;

    FinGame::FinGame(FinState* initialState) : currentState(initialState) {
        // Set instance
        if (!s_instance) {
            s_instance = this;
        }

        // Initialize systems
        GRRLIB_Init();
        WPAD_Init();

        // Initialize state
        currentState->init();

        
    }

    FinGame::~FinGame() {
        if (s_instance == this) {
            s_instance = nullptr;
        }
    }
}