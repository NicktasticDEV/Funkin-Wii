#include "titleteststate.h"

#include <grrlib.h>

#include <wiiuse/wpad.h>
#include <math.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>

#include <asndlib.h>
#include "../oggplayer.h"

#include "fontdef_ttf.h"
#include "sample_ogg.h"

typedef struct
{
    float x, y;
    float zoom;
    float rot;
} Camera;

namespace
{
    GRRLIB_texImg *logo;
    GRRLIB_texImg *bg;
    GRRLIB_ttfFont *font;

    int frameCount = 0;
    float logoY;
    float logoYDelay;

    Camera camera = {0, 0, 1, 90};

    // Draw a texture using WORLD coordinates, applying a 2D camera (translate/zoom/rotate)
    // This uses GRRLIB_DrawImgQuad so it goes through the textured-quad path that accepts arbitrary 2D transforms.
    static inline void DrawImgWorld(float x, float y, GRRLIB_texImg *tex, float degrees, float scaleX, float scaleY, u32 color) {
        if (!tex) return;

        // Sprite size after per-sprite scale
        const float w = (float)tex->w * scaleX;
        const float h = (float)tex->h * scaleY;

        // Build the 4 untransformed corners (top-left origin)
        float x0 = x,     y0 = y;
        float x1 = x + w, y1 = y;
        float x2 = x + w, y2 = y + h;
        float x3 = x,     y3 = y + h;

        // Optional per-sprite rotation around its top-left corner
        const float rad = degrees * (float)M_PI / 180.0f;
        const float cs = cosf(rad), sn = sinf(rad);
        auto rot_point = [&](float px, float py) -> guVector {
            float rx = x + (px - x) * cs - (py - y) * sn;
            float ry = y + (px - x) * sn + (py - y) * cs;
            guVector v = { rx, ry, 0.0f };
            return v;
        };

        guVector pos[4];
        pos[0] = rot_point(x0, y0);
        pos[1] = rot_point(x1, y1);
        pos[2] = rot_point(x2, y2);
        pos[3] = rot_point(x3, y3);

        // Apply CAMERA transform (translate, zoom, optional rotation)
        const float camZoom = camera.zoom;
        const float camRad  = camera.rot * (float)M_PI / 180.0f;
        const float camCs   = cosf(camRad), camSn = sinf(camRad);

        // Screen center for rotating the whole view (prevents spinning around top-left)
        const float cx = (float)rmode->fbWidth * 0.5f;
        const float cy = (float)rmode->efbHeight * 0.5f;

        for (int i = 0; i < 4; ++i) {
            // world -> view translation by camera position
            pos[i].x -= camera.x;
            pos[i].y -= camera.y;

            // ZOOM AROUND SCREEN CENTER
            if (camZoom != 1.0f) {
                float sx = pos[i].x - cx;
                float sy = pos[i].y - cy;
                sx *= camZoom;
                sy *= camZoom;
                pos[i].x = sx + cx;
                pos[i].y = sy + cy;
            }

            // ROTATE AROUND SCREEN CENTER
            if (camera.rot != 0.0f) {
                float sx = pos[i].x - cx;
                float sy = pos[i].y - cy;
                float rx = sx * camCs - sy * camSn;
                float ry = sx * camSn + sy * camCs;
                pos[i].x = rx + cx;
                pos[i].y = ry + cy;
            }
        }

        // Finally, draw the textured quad
        GRRLIB_DrawImgQuad(pos, tex, color);
    }
}

void TitleTestState::init() {
    logo = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/logo.png");
    bg = GRRLIB_LoadTextureFromFile("sd:/fnfwii/images/titlebg.png");
    font = GRRLIB_LoadTTF(fontdef_ttf, fontdef_ttf_size);

    PlayOgg(sample_ogg, sample_ogg_size, 0, OGG_INFINITE_TIME);
}

void TitleTestState::update() {
    WPAD_ScanPads();

    // Exit code
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
    {
        finengine::FinGame::instance().exit();
    }

    // Camera movement
    float camSpeed = 4.0f;
    // Position
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP) camera.y -= camSpeed;
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN) camera.y += camSpeed;
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_LEFT) camera.x -= camSpeed;
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_RIGHT) camera.x += camSpeed;
    // Rotation with A and B
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_A) camera.rot -= camSpeed;
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_B) camera.rot += camSpeed;
    // Zoom
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_PLUS) camera.zoom += 0.1f;
    if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_MINUS) camera.zoom -= 0.1f;

    // Logo Y position update
    float amplitude = 18.0f;
    float frequency = 0.09f;

    logoY = 87 + sin(frameCount * frequency) * amplitude;
    logoYDelay = 87 + sin((frameCount + 8) * frequency) * amplitude;
    frameCount++;
}

void TitleTestState::render() {
    GRRLIB_FillScreen(0xFFFFFFFF);

    GRRLIB_2dMode();
    DrawImgWorld(0, 0, bg, 0, 1, 1, 0xFFFFFFFF);
    DrawImgWorld(56, logoYDelay, logo, 0, 1, 1, 0x000000FF);
    DrawImgWorld(56, logoY, logo, 0, 1, 1, 0xFFFFFFFF);
    GRRLIB_Render();
}

void TitleTestState::cleanup() {
    GRRLIB_FreeTexture(logo);
}