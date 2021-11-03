#include "breakout.h"
#include "callbacks.h"
#include "glib2d.h"
#include "util.h"

#include <intraFont.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <stdlib.h>

PSP_MODULE_INFO("PSPBreakout", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024);

void process_input(struct SceCtrlData *data) {
}

int main() {
    callbacks_setup();
    intraFontInit();
    intraFont *ltn[16];

    char file[40];
    int i;
    for (i = 0; i < 16; i++) {
        sprintf(file, "flash0:/font/ltn%d.pgf", i);
        ltn[i] = intraFontLoad(file,
                               0); //<- this is where the actual loading happens
        intraFontSetStyle(ltn[i], 1.0f, WHITE, 0, 0.0f, 0);
    }

    Breakout_Board board = create_board(BLOCKS_X, BLOCKS_Y);

    while (1) {
        g2dClear(BLACK);
        draw_board(&board);
        intraFontPrint(ltn[8], 10, 20, "Latin Sans-Serif:");
        stroke_circle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 40, RED);
        g2dFlip(G2D_VSYNC);
    }

    destroy_board(&board);
    for (int i = 0; i < 16; i++) intraFontUnload(ltn[i]);
    sceKernelExitGame();

    return 0;
}