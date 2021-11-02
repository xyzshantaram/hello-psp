#include "breakout.h"

void draw_board(Breakout_Board board, int nx, int ny) {
    for (int y = 0; y < ny; y++) {
        for (int x = 0; x < nx; x++) {
            Breakout_Block tmp = board.rows[y][x];
            if (!tmp.broken) {
                draw_rect(tmp.x, tmp.y, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_COLOR);
            }
        }
    }
}

Breakout_Board create_board(int nx, int ny) {
    Breakout_Board board = {.rows = NULL, .w = nx, .h = ny};

    board.rows = malloc(ny * sizeof(Breakout_Block *));

    int start_y = 28;

    for (int y = 0; y < ny; y++) {
        board.rows[y] = malloc(sizeof(Breakout_Block[nx]));

        int start_x =
            (480 - ((BLOCK_WIDTH) + (nx - 1) * (BLOCK_WIDTH + BLOCK_MARGIN))) /
            2;

        for (int x = 0; x < nx; x++) {
            board.rows[y][x].x = start_x + x * BLOCK_WIDTH;
            board.rows[y][x].y = start_y + y * BLOCK_HEIGHT;

            printf("created %d, %d\n", board.rows[y][x].x, board.rows[y][x].y);
            board.rows[y][x].broken = false;

            start_x += BLOCK_MARGIN;
        }
        start_y += BLOCK_MARGIN;
    }

    return board;
}