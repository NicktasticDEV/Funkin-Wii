#include <grrlib.h>
#include <stdlib.h>
#include <gccore.h>
#include <stdio.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <tinyxml2.h>
#include <math.h>
#include <vector>
#include "FinGame.h"

#include <ogc/lwp_watchdog.h>

#include "fontdef_ttf.h"

#include "states/sparrowtest.h"

int main(int argc, char **argv) {
    finengine::FinGame* game = new finengine::FinGame(new SparrowTestState());
    
    delete game;
    exit(0);
}