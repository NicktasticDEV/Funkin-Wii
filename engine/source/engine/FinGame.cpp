#include "FinEngine.h"
#include <stdio.h>
#include <stdlib.h>

#include "system/system.h"

namespace finengine {
    FinGame* FinGame::s_instance = nullptr;

    FinGame::FinGame(FinState* initialState) : nextState(initialState) {
        // Set instance
        if (!s_instance) {
            s_instance = this;
        }

        // Initialize systems
        System_Init();

        printf("Game Initialized\n");

        // State update
        while (isRunning) {

            // State init
            if (nextState)
            {
                printf("Switching State now\n");

                if (currentState)
                {
                    currentState->cleanup();
                    delete currentState;
                }

                currentState = nextState;
                nextState = nullptr;

                if (currentState)
                {
                    currentState->init();
                    printf("State Initialized\n");
                }
            }

            currentState->update();
            currentState->render();
        }

        // Cleanup
        currentState->cleanup();
        System_Shutdown();
    }

    void FinGame::SwitchState(FinState* state) {
        printf("Switching State started\n");
        nextState = state;
    }
    

    void FinGame::Exit() {
        isRunning = false;
    }

    FinGame::~FinGame() {
        if (s_instance == this) {
            s_instance = nullptr;
        }
    }
}