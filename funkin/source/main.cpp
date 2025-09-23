#include "FinEngine.h"
#include <stdio.h>
#include <stdlib.h>
#include <romfs-ogc.h>
#include <wiiuse/wpad.h>

#include "states/titlestate.h"

int main(int argc, char **argv) {
    romfsInit();
    WPAD_Init();

    finengine::FinGame* game = new finengine::FinGame(new TitleState());

    delete game;

    romfsExit();
    WPAD_Shutdown();
    exit(0);
}