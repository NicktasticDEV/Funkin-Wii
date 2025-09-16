#include "FinEngine.h"
#include <stdio.h>
#include <stdlib.h>

#include "system/system.h"

namespace finengine {
    FinGame* FinGame::s_instance = nullptr;

    FinGame::FinGame(FinState* initialState) : currentState(initialState) {
        // Set instance
        if (!s_instance) {
            s_instance = this;
        }

        // Initialize systems
        System_Init();

        // State initialization
        currentState->init();

        // State update
        while (isRunning) {
            currentState->update();
            currentState->render();
        }

        // Cleanup
        currentState->cleanup();
        System_Shutdown();
    }

    void FinGame::exit() {
        isRunning = false;
    }

    FinGame::~FinGame() {
        if (s_instance == this) {
            s_instance = nullptr;
        }
    }
}