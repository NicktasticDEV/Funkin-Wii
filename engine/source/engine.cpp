#include <gccore.h>
#include <wiiuse/wpad.h>
#include <stdio.h>
#include "engine.h"

void engine_init(void) {
    // Put shared initialization here later.
    printf("[engine] init\n");
}

void engine_update(void) {
    // Put common per-frame logic here later.
    (void)WPAD_ScanPads; // keep wpad include used for now
}
