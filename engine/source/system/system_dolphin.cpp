#ifdef FINENGINE_OS_WII

#include "system.h"

#include <stdio.h>
#include <grrlib.h>


void System_Init() {
    SYS_STDIO_Report(true);
    GRRLIB_Init();
}

void System_Shutdown() {
    GRRLIB_Exit();
}

#endif