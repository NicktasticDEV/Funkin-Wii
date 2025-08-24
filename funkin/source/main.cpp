#include <grrlib.h>
#include <stdlib.h>
#include <gccore.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <tinyxml2.h>
#include <math.h>
#include <vector>
#include <asndlib.h>
#include "FinGame.h"

#include <ogc/lwp_watchdog.h>

#include "fontdef_ttf.h"

#include "states/sparrowtest.h"
#include "states/titletest.h"

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