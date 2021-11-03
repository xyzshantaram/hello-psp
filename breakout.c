#include "breakout.h"
#include "util.h"

void draw_board(Breakout_Board *board) {
    for (int y = 0; y < board->h; y++) {
        for (int x = 0; x < board->w; x++) {
            Breakout_Block tmp = board->rows[y][x];
            if (!tmp.broken) {
                fill_rect(tmp.x, tmp.y, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_COLOR);
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

        int start_x = (SCREEN_WIDTH - (nx * (BLOCK_WIDTH + BLOCK_MARGIN))) / 2;

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

void destroy_board(Breakout_Board *board) {
    for (int y = 0; y < board->h; y++) free(board->rows[y]);
    free(board->rows);
}

Breakout_Paddle create_paddle() {
    Breakout_Paddle paddle = {.x = SCREEN_WIDTH / 2 - PADDLE_WIDTH};
    return paddle;
}

void draw_paddle(Breakout_Paddle *paddle) {
    fill_rect(paddle->x, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOR);
}