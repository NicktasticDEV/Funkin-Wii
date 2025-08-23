#pragma once
#include "FinState.h"

namespace finengine {

    class FinGame {
        public:
            FinGame(FinState *initialState);
            ~FinGame();

            static FinGame& instance() { return *s_instance; }
            static FinGame* instancePtr() { return s_instance; }
            void setState(FinState* state);
            void exit();

        private:
            static FinGame* s_instance;
            FinState* currentState = nullptr;
    };

}
