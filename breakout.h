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

void draw_board(Breakout_Board *board);
Breakout_Board create_board(int nx, int ny);

#endif