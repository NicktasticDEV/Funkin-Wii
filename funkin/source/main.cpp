#include "FinEngine.h"
#include <stdio.h>
#include <stdlib.h>

#include "states/teststate.h"

int main(int argc, char **argv) {
    finengine::FinGame* game = new finengine::FinGame(new TestState());

    delete game;
    exit(0);
}