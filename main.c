#include "breakout.h"
#include "callbacks.h"
#include "glib2d.h"
#include "util.h"

#include <intraFont.h>
#include <math.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <psprtc.h>
#include <stdlib.h>
#include <string.h>

#define TARGET_FPS 60

PSP_MODULE_INFO("PSPbreakout", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024);

void process_input(breakout_State *game) {
    struct SceCtrlData data;
    sceCtrlReadBufferPositive(&data, 1);

    if (data.Buttons & PSP_CTRL_START) {
        game->paused = !game->paused;
        return;
    }

    if (data.Buttons & PSP_CTRL_CIRCLE) {
        if (game->paused || game->lost || game->won) {
            game->quit = true;
            return;
        }
    }

    if (!game->started && (data.Buttons & PSP_CTRL_CROSS)) {
        if (game->won || game->lost) {
            game->won = false;
            game->lost = false;
            destroy_board(&game->board);
            breakout_initialise(game);
        }
        game->started = true;
        return;
    }
    if (data.Buttons & PSP_CTRL_LEFT) game->paddle.x -= PADDLE_SPEED;
    else if (data.Buttons & PSP_CTRL_RIGHT)
        game->paddle.x += PADDLE_SPEED;
    else if (data.Lx != 128) {
        // get analog position as a number between -128 and 127
        float zeroed = data.Lx - 128;
        float final = round(zeroed / 128.0);
        game->paddle.x += final * PADDLE_SPEED;
    }

    game->paddle.x = clamp(game->paddle.x, 0, SCREEN_WIDTH - PADDLE_WIDTH);
}

void load_latin_fonts(intraFont *(*arr)[16]) {
    char file[40];
    int i;
    for (i = 0; i < 16; i++) {
        sprintf(file, FONT_LOCATION, i);
        printf("Loading font %s\n", file);
        (*arr)[i] = intraFontLoad(file, 0);
        intraFontSetStyle((*arr)[i], 1.0f, WHITE, 0, 0.0f, 0);
    }
}

void draw_text_centered(intraFont *fnt, float ypos, const char *msg) {
    if (!msg) return;
    float length = intraFontMeasureText(fnt, msg);
    float text_x = (SCREEN_WIDTH - length) / 2;
    intraFontPrint(fnt, text_x, ypos, msg);
}

int main() {
    callbacks_setup();
    intraFontInit();

    intraFont *latin_fonts[16];
    load_latin_fonts(&latin_fonts);

    breakout_State game;
    breakout_initialise(&game);

    g2dColor BG = rgba(0x202020FF);

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    u64 last_tick;

    while (1) {
        // Framelimit code
        u32 res = sceRtcGetTickResolution();
        u32 min_delta = res / TARGET_FPS;
        u64 this_tick;
        sceRtcGetCurrentTick(&this_tick);
        u64 delta = this_tick - last_tick;
        last_tick = this_tick;
        if (delta < min_delta) continue;

        g2dClear(BG);
        process_input(&game);
        if (game.quit) goto end;
        if (game.paused) {
            draw_text_centered(latin_fonts[8], 10,
                               "PAUSED - Press Start to unpause");
            draw_text_centered(latin_fonts[8], 30, "(O to quit)");
            sceKernelDelayThread(2000); // delay for 2ms
        } else {
            if (!game.won && !game.lost) {
                if (!game.started) {
                    draw_text_centered(latin_fonts[8], 120, "Press X to start");
                }
                draw_board(&game.board);
                draw_paddle(&game.paddle);
                draw_ball(&game);
            } else if (game.won) {
                draw_text_centered(latin_fonts[8], 120, "You won!");
                game.started = false;
            } else if (game.lost) {
                draw_text_centered(latin_fonts[8], 120, "You lost!");
                game.started = false;
            }

            if (game.won || game.lost) {
                draw_text_centered(latin_fonts[8], 140,
                                   "Press X to play again");
                draw_text_centered(latin_fonts[8], 160, "(O to quit)");
            }
        }
        g2dFlip(G2D_VSYNC);
    }

end:
    destroy_board(&game.board);
    for (int i = 0; i < 16; i++) intraFontUnload(latin_fonts[i]);
    sceKernelExitGame();

    return 0;
}