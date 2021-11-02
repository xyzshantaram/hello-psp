#include "util.h"

void draw_rect(int x, int y, int w, int h, g2dColor color) {
    g2dBeginRects(NULL); // No texture
    g2dSetColor(color);
    g2dSetScaleWH(w, h);
    g2dSetCoordXY(x, y);
    g2dAdd();
    g2dEnd();
}

g2dColor rgba(uint32_t color) {
    uint64_t r = (0xff000000 & color) >> 24;
    uint64_t g = (0xff0000 & color) >> 16;
    uint64_t b = (0xff00 & color) >> 8;
    uint64_t a = (0xff & color);

    return G2D_RGBA(r, g, b, a);
}
