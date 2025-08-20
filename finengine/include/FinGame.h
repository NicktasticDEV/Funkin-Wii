#pragma once
#include "FinEngine.h"

namespace finengine {

    class FinGame {
        public:
            FinGame();
            ~FinGame();

            static FinGame& instance() { return *s_instance; }
            static FinGame* instancePtr() { return s_instance; }

        private:
            static FinGame* s_instance;
    };

}
