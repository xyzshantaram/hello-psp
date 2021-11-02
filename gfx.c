#include "gfx.h"
#include <pspdisplay.h>
#include <pspge.h>
#include <psputils.h>

uint32_t *draw_buffer;
uint32_t *disp_buffer;

void GFX_init() {
    draw_buffer = sceGeEdramGetAddr();
    disp_buffer = (uint32_t *)sceGeEdramGetAddr() +
                  (SCREEN_HEIGHT * DISPLAY_BUFFER_WIDTH * 4);

    sceDisplaySetMode(0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceDisplaySetFrameBuf(disp_buffer, DISPLAY_BUFFER_WIDTH,
                          PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
}

// Takes a u32 of the form 0xRRGGBBAA and returns a u32 0xAABBGGRR.
uint32_t color(uint32_t hex) {
    // extract and complement each 8-bit number
    uint64_t r = ((0xff000000 & hex) >> 24);
    uint64_t g = ((0xff0000 & hex) >> 16);
    uint64_t b = ((0xff00 & hex) >> 8);
    uint64_t a = (0xff & hex);

    return (a << 24) + (b << 16) + (g << 8) + r;
}

void GFX_clear(uint32_t hex) {
    for (int i = 0; i < DISPLAY_BUFFER_WIDTH * SCREEN_HEIGHT; i++) {
        draw_buffer[i] = color(hex);
    }
}

void GFX_swap_buffers() {
    uint32_t *temp = disp_buffer;
    disp_buffer = draw_buffer;
    draw_buffer = temp;

    sceKernelDcacheWritebackInvalidateAll();
    sceDisplaySetFrameBuf(disp_buffer, DISPLAY_BUFFER_WIDTH,
                          PSP_DISPLAY_PIXEL_FORMAT_8888,
                          PSP_DISPLAY_SETBUF_NEXTFRAME);
}

void GFX_draw_rect(unsigned int x, unsigned int y, unsigned int w,
                   unsigned int h, uint32_t hex) {

    // bounds checking
    if (x > SCREEN_WIDTH) x = SCREEN_WIDTH;
    if (y > SCREEN_HEIGHT) y = SCREEN_HEIGHT;
    if (x + w > SCREEN_WIDTH) w = SCREEN_WIDTH - x;
    if (y + h > SCREEN_HEIGHT) h = SCREEN_HEIGHT - y;

    int off = x + (y * DISPLAY_BUFFER_WIDTH);
    for (int y1 = 0; y1 < h; y1++) {
        for (int x1 = 0; x1 < w; x1++) {
            draw_buffer[x1 + off + y1 * DISPLAY_BUFFER_WIDTH] = color(hex);
        }
    }
}
