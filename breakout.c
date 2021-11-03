#include "breakout.h"
#include "util.h"

void draw_board(breakout_Board *board) {
    for (int y = 0; y < board->h; y++) {
        for (int x = 0; x < board->w; x++) {
            breakout_Block tmp = board->rows[y][x];
            if (!tmp.broken) {
                fill_rect(tmp.x, tmp.y, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_COLOR);
            }
        }
    }
}

breakout_Board create_board(int nx, int ny) {
    breakout_Board board = {.rows = NULL, .w = nx, .h = ny};

    board.rows = malloc(ny * sizeof(breakout_Block *));

    int start_y = BLOCK_START_Y;

    for (int y = 0; y < ny; y++) {
        board.rows[y] = malloc(sizeof(breakout_Block[nx]));

        int start_x = (SCREEN_WIDTH - (nx * (BLOCK_WIDTH + BLOCK_MARGIN))) / 2;

        for (int x = 0; x < nx; x++) {
            board.rows[y][x].x = start_x + x * BLOCK_WIDTH;
            board.rows[y][x].y = start_y + y * BLOCK_HEIGHT;
            board.rows[y][x].broken = false;

            start_x += BLOCK_MARGIN;
        }
        start_y += BLOCK_MARGIN;
    }

    return board;
}

void destroy_board(breakout_Board *board) {
    for (int y = 0; y < board->h; y++) free(board->rows[y]);
    free(board->rows);
}

breakout_Paddle create_paddle() {
    breakout_Paddle paddle = {.x = SCREEN_WIDTH / 2 - PADDLE_WIDTH};
    return paddle;
}

void draw_paddle(breakout_Paddle *paddle) {
    fill_rect(paddle->x, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_COLOR);
}

void update_ball(breakout_State *game) {
    if (!game->started) {
        game->ball.cx = game->paddle.x + PADDLE_WIDTH / 2;
        return;
    }

    for (int y = 0; y < game->board.h; y++) {
        for (int x = 0; x < game->board.w; x++) {
            if (circle_rect_collision(game->ball.cx, game->ball.cy, BALL_RADIUS,
                                      game->board.rows[y][x].x,
                                      game->board.rows[y][x].y, BLOCK_WIDTH,
                                      BLOCK_HEIGHT)) {
                if (!game->board.rows[y][x].broken) {
                    game->board.rows[y][x].broken = true;
                    game->ball.vy *= -1;
                    game->n_cells -= 1;
                    if (game->n_cells <= 0) game->won = true;
                }
            } else {
                continue;
            }
        }
    }

    if (circle_rect_collision(game->ball.cx, game->ball.cy, BALL_RADIUS,
                              game->paddle.x, PADDLE_Y, PADDLE_WIDTH,
                              PADDLE_HEIGHT)) {
        game->ball.vy *= -1;
    }

    game->ball.cx += game->ball.vx;
    game->ball.cy += game->ball.vy;

    if (game->ball.cy > SCREEN_HEIGHT - BALL_RADIUS) game->lost = true;

    if (game->ball.cx > SCREEN_WIDTH || game->ball.cx < 0) game->ball.vx *= -1;
    if (game->ball.cy < 0) game->ball.vy *= -1;
}

void draw_ball(breakout_State *game) {
    update_ball(game);
    fill_circle(game->ball.cx, game->ball.cy, BALL_RADIUS, YELLOW);
}

breakout_Ball create_ball(breakout_Paddle *paddle) {
    breakout_Ball ball = {.cx = paddle->x + PADDLE_WIDTH / 2,
                          .cy = PADDLE_Y - BALL_RADIUS - 2,
                          .vx = 2,
                          .vy = 2};

    return ball;
}

void breakout_initialise(breakout_State *state) {
    state->board = create_board(BLOCKS_X, BLOCKS_Y);
    state->paddle = create_paddle();
    state->ball = create_ball(&state->paddle);
    state->started = false;
    state->won = false;
    state->lost = false;
    state->n_cells = state->board.w * state->board.h;
    state->paused = false;
    state->quit = false;
}