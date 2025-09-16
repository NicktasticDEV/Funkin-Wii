#include "FinEngine.h"
#include <stdio.h>
#include <stdlib.h>

#include "states/titlestate.h"

int main(int argc, char **argv) {
    finengine::FinGame* game = new finengine::FinGame(new TitleState());

    delete game;
    exit(0);
}