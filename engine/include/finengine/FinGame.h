#pragma once
#include "FinState.h"

namespace finengine {

    class FinGame {
        public:
            FinGame(FinState *initialState);
            ~FinGame();

            static FinGame& instance() { return *s_instance; }
            static FinGame* instancePtr() { return s_instance; }
            void SwitchState(FinState* state);
            void Exit();

        private:
            static FinGame* s_instance;
            FinState* currentState = nullptr;
            FinState* nextState = nullptr;
            bool isRunning = true;
    };

}
