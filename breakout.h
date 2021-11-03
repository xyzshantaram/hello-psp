#include "util.h"
#include <stdio.h>

#ifndef __BREAKOUT_H__
#define __BREAKOUT_H__

#define BLOCK_HEIGHT 10
#define BLOCK_WIDTH 20
#define BLOCKS_X 18
#define BLOCKS_Y 4
#define BLOCK_START_Y 40
#define BLOCK_MARGIN 1
#define BLOCK_COLOR rgba(0x007cdfff)
#define BALL_RADIUS 4
#define PADDLE_WIDTH 40
#define PADDLE_HEIGHT 10
#define PADDLE_Y 225
#define PADDLE_COLOR rgba(0x663399ff)
#define PADDLE_SPEED 6

typedef struct block {
    int x;
    int y;
    _Bool broken;
} breakout_Block;

typedef struct board {
    int w;
    int h;
    breakout_Block **rows;
} breakout_Board;

typedef struct ball {
    int cx;
    int cy;
    int vx;
    int vy;
} breakout_Ball;

typedef struct paddle {
    int x;
} breakout_Paddle;

typedef struct game {
    breakout_Board board;
    breakout_Ball ball;
    breakout_Paddle paddle;
    _Bool started;
    _Bool won;
    _Bool lost;
    _Bool paused;
    _Bool quit;
    int n_cells;
} breakout_State;

void draw_ball(breakout_State *game);
void draw_board(breakout_Board *board);
void draw_paddle(breakout_Paddle *paddle);

breakout_Ball create_ball();
breakout_Board create_board(int nx, int ny);
breakout_Paddle create_paddle();
void breakout_initialise(breakout_State *state);

#endif