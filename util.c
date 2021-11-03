#include "util.h"

void fill_rect(int x, int y, int w, int h, g2dColor color) {
    g2dBeginRects(NULL); // No texture
    g2dSetColor(color);
    g2dSetScaleWH(w, h);
    g2dSetCoordXY(x, y);
    g2dAdd();
    g2dEnd();
}

void stroke_rect(int x, int y, int w, int h, g2dColor color) {
}

void fill_circle(int x, int y, int r, g2dColor color) {
}

void add_point(int x, int y, g2dColor color) {
    g2dSetColor(color);
    g2dSetCoordXY(x, y);
    g2dAdd();
}

void circlePoints(int cx, int cy, int x, int y, int pix) {
    if (x == 0) {
        add_point(cx, cy + y, pix);
        add_point(cx, cy - y, pix);
        add_point(cx + y, cy, pix);
        add_point(cx - y, cy, pix);
    } else if (x == y) {
        add_point(cx + x, cy + y, pix);
        add_point(cx - x, cy + y, pix);
        add_point(cx + x, cy - y, pix);
        add_point(cx - x, cy - y, pix);
    } else if (x < y) {
        add_point(cx + x, cy + y, pix);
        add_point(cx - x, cy + y, pix);
        add_point(cx + x, cy - y, pix);
        add_point(cx - x, cy - y, pix);
        add_point(cx + y, cy + x, pix);
        add_point(cx - y, cy + x, pix);
        add_point(cx + y, cy - x, pix);
        add_point(cx - y, cy - x, pix);
    }
}

void stroke_circle(int cx, int cy, int r, g2dColor color) {
    g2dBeginPoints();
    int x = 0;
    int y = r;
    int p = (5 - r * 4) / 4;

    circlePoints(cx, cy, x, y, color);
    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        circlePoints(cx, cy, x, y, color);
    }
    g2dEnd();
}

g2dColor rgba(uint32_t color) {
    uint64_t r = (0xff000000 & color) >> 24;
    uint64_t g = (0xff0000 & color) >> 16;
    uint64_t b = (0xff00 & color) >> 8;
    uint64_t a = (0xff & color);

    return G2D_RGBA(r, g, b, a);
}
