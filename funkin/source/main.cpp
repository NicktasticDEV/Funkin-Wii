#include "FinEngine.h"
#include <grrlib.h>

#include <stdlib.h>
#include <gccore.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <asndlib.h>

#include "states/titleteststate.h"
#include "states/sparrowteststate.h"

int main(int argc, char **argv) {
    WPAD_Init();
    fatInitDefault();
    SYS_STDIO_Report(true);
    GRRLIB_Init();
    ASND_Init();

    finengine::FinGame* game = new finengine::FinGame(new TitleTestState());

    delete game;
    exit(0);
}