#include "breakout.h"
#include "callbacks.h"
#include "glib2d.h"
#include "util.h"

#include <intraFont.h>
#include <math.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <stdlib.h>

PSP_MODULE_INFO("PSPBreakout", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024);

void process_input(struct SceCtrlData *data, Breakout_Paddle *paddle) {
    sceCtrlReadBufferPositive(data, 1);
    if (data->Buttons & PSP_CTRL_LEFT) paddle->x -= PADDLE_SPEED;
    else if (data->Buttons & PSP_CTRL_RIGHT)
        paddle->x += PADDLE_SPEED;
    else if (data->Lx != 128) {
        // get analog position as a number between -128 and 127
        float zeroed = data->Lx - 128;
        float final = round(zeroed / 128.0);
        paddle->x += final * PADDLE_SPEED;
    }

    paddle->x = clamp(paddle->x, 0, SCREEN_WIDTH - PADDLE_WIDTH);
}

void load_fonts(intraFont *(*ltn)[16]) {
    char file[40];
    int i;
    for (i = 0; i < 16; i++) {
        sprintf(file, FONT_LOCATION, i);
        printf("Loading font %s\n", file);
        (*ltn)[i] = intraFontLoad(file, 0);
        intraFontSetStyle((*ltn)[i], 1.0f, WHITE, 0, 0.0f, 0);
    }
}

int main() {
    callbacks_setup();
    intraFontInit();

    intraFont *ltn[16];
    load_fonts(&ltn);

    Breakout_Board board = create_board(BLOCKS_X, BLOCKS_Y);
    Breakout_Paddle paddle = create_paddle();
    g2dColor BG = rgba(0x303030FF);
    _Bool started = false;

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    struct SceCtrlData padData;

    while (1) {
        g2dClear(BG);
        process_input(&padData, &paddle);
        draw_board(&board);
        draw_paddle(&paddle);
        intraFontPrint(ltn[8], 10, 20, "Latin Sans-Serif:");
        g2dFlip(G2D_VSYNC);
    }

    destroy_board(&board);
    for (int i = 0; i < 16; i++) intraFontUnload(ltn[i]);
    sceKernelExitGame();

    return 0;
}