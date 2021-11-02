#ifndef __UTIL_H__
#define __UTIL_H__

#include "glib2d.h"
#include <stdint.h>
#include <stdlib.h>

#define FONT_DIR "flash0:/font/ltn%d.pgf"

#define true 1
#define false 0

void draw_rect(int x, int y, int w, int h, g2dColor color);
g2dColor rgba(uint32_t color);
#endif