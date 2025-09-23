#include "teststate.h"

#include "FinEngine.h"
#include <grrlib.h>
#include <romfs-ogc.h>

#include <wiiuse/wpad.h>
#include <math.h>
#include <stdio.h>

void TestState::init() {
    
}

void TestState::update() {
    WPAD_ScanPads();

    // Exit code
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        finengine::FinGame::instance().Exit();
    }

    
}

void TestState::render() {
    GRRLIB_FillScreen(0xFFFFFFFF);

    

    GRRLIB_Render();
}

void TestState::cleanup() {
    
}