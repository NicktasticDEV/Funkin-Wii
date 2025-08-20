#include "FinEngine.h"

namespace finengine {
    FinGame* FinGame::s_instance = nullptr;

    FinGame::FinGame() {
        if (!s_instance) {
            s_instance = this;
        }
    }

    FinGame::~FinGame() {
        if (s_instance == this) {
            s_instance = nullptr;
        }
    }
}