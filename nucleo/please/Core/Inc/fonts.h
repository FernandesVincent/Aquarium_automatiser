#ifndef FONTS_H
#define FONTS_H

#include "string.h"
#include <stdint.h>

typedef struct {
    uint8_t FontWidth;
    uint8_t FontHeight;
    const uint16_t *data;
} FontDef;

extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

#endif /* FONTS_H */