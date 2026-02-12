#ifndef SSD1308_H
#define SSD1308_H

#include "i2c.h"
#include "fonts.h"
#include "stm32l4xx_hal.h"
#include <stdint.h>

// SSD1308 Characteristics
#define SSD1308_BASE_ADDRESS 0x3C << 1 // 0x3D << 1
#define SSD1308_WIDTH 128
#define SSD1308_HEIGHT 64
#define SSD1308_PIXEL_OFF 0x00
#define SSD1308_PIXEL_ON 0x01
#define SSD1308_CMD_REGISTER 0x00
#define SSD1308_DATA_REGISTER 0x40

// SSD1308 Base Commands
#define SSD1308_CMD_SET_NORMAL_DISPLAY 0xA6
#define SSD1308_CMD_SET_INVERTED_DISPLAY 0xA7

typedef struct {
    int id;
    uint16_t currentX;
    uint16_t currentY;
    int isInverted;
    int isInit;
    uint8_t lastCommand;
} SSD1308_t;

void ssd1308_I2C_write(uint8_t address, uint8_t reg, uint8_t data);
void ssd1308_I2C_write_multiple(uint8_t address, uint8_t reg, uint8_t* data, uint16_t size);
uint8_t ssd1308_init(SSD1308_t* ssd1308);
void ssd1308_write_command(uint8_t command);
void ssd1308_write_data(uint8_t data);
void ssd1308_update_screen(void);
void ssd1308_invert_display(SSD1308_t* ssd1308);
void ssd1308_fill(uint8_t color);
void ssd1308_draw_pixel(SSD1308_t* ssd1308, uint16_t x, uint16_t y, uint8_t color);
void ssd1308_gotoXY(SSD1308_t* ssd1308, uint16_t x, uint16_t y);
void ssd1308_put_char(SSD1308_t *ssd1308, char ch, FontDef* Font, uint8_t color);
void ssd1308_put_string(SSD1308_t *ssd1308, char* str, FontDef* Font, uint8_t color);


#endif /* SSD1308_H */