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

    Breakout_Board board = create_board(BLOCKS_X, BLOCKS_Y);

    while (1) {
        g2dClear(BLACK);
        draw_board(board, BLOCKS_X, BLOCKS_Y);
        g2dFlip(G2D_VSYNC);
    }

    sceKernelExitGame();
    return 0;
}