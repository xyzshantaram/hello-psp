#include "util.h"
#include <stdio.h>

#ifndef __BREAKOUT_H__
#define __BREAKOUT_H__

#define BLOCK_HEIGHT 10
#define BLOCK_WIDTH 20
#define BLOCKS_X 18
#define BLOCKS_Y 4
#define BLOCK_MARGIN 1
#define BLOCK_COLOR rgba(0x007cdfff)
#define BALL_RADIUS 2
#define PADDLE_WIDTH 40
#define PADDLE_HEIGHT 10
#define PADDLE_Y 240
#define PADDLE_COLOR rgba(0x663399ff)

typedef struct block {
    int x;
    int y;
    _Bool broken;
} Breakout_Block;

typedef struct board {
    int w;
    int h;
    Breakout_Block **rows;
} Breakout_Board;

typedef struct ball {
    int cx;
    int cy;
    int vx;
    int vy;
} Breakout_Ball;

typedef struct paddle {
    int x;
} Breakout_Paddle;

void draw_board(Breakout_Board *board);
void draw_paddle(Breakout_Paddle *paddle);
Breakout_Paddle create_paddle();
Breakout_Board create_board(int nx, int ny);

#endif