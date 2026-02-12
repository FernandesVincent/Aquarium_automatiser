#include "ssd1308.h"
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef* ssd1308_i2c = &hi2c1;

static uint8_t SSD1308_Buffer[SSD1308_WIDTH * SSD1308_HEIGHT / 8];

void ssd1308_I2C_write(uint8_t address, uint8_t reg, uint8_t data) {
    uint8_t buffer[2];
    buffer[0] = reg;
    buffer[1] = data;
    HAL_I2C_Master_Transmit(ssd1308_i2c, address, buffer, 2, 10);
}

void ssd1308_I2C_write_multiple(uint8_t address, uint8_t reg, uint8_t* data, uint16_t size) {
    uint8_t buffer[size + 1];
    buffer[0] = reg;
    for (int i = 0; i < size; i++) {
        buffer[i + 1] = data[i];
    }
    HAL_I2C_Master_Transmit(ssd1308_i2c, address, buffer, size + 1, 10);
}

void ssd1308_write_command(uint8_t command) {
    ssd1308_I2C_write(SSD1308_BASE_ADDRESS, SSD1308_CMD_REGISTER, command);
}

void ssd1308_write_data(uint8_t data) {
    ssd1308_I2C_write(SSD1308_BASE_ADDRESS, SSD1308_DATA_REGISTER, data);
}

uint8_t ssd1308_init(SSD1308_t* ssd1308) {
    if (HAL_I2C_IsDeviceReady(ssd1308_i2c, SSD1308_BASE_ADDRESS, 3, 100) != HAL_OK) {
        return 1;
    }
    HAL_Delay(100);
    ssd1308_write_command(0xAE); //display off
	ssd1308_write_command(0x20); //Set Memory Addressing Mode   
	ssd1308_write_command(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	ssd1308_write_command(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	ssd1308_write_command(0xC8); //Set COM Output Scan Direction
	ssd1308_write_command(0x00); //---set low column address
	ssd1308_write_command(0x10); //---set high column address
	ssd1308_write_command(0x40); //--set start line address
	ssd1308_write_command(0x81); //--set contrast control register
	ssd1308_write_command(0xFF);
	ssd1308_write_command(0xA1); //--set segment re-map 0 to 127
	ssd1308_write_command(0xA6); //--set normal display
	ssd1308_write_command(0xA8); //--set multiplex ratio(1 to 64)
	ssd1308_write_command(0x3F); //
	ssd1308_write_command(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	ssd1308_write_command(0xD3); //-set display offset
	ssd1308_write_command(0x00); //-not offset
	ssd1308_write_command(0xD5); //--set display clock divide ratio/oscillator frequency
	ssd1308_write_command(0xF0); //--set divide ratio
	ssd1308_write_command(0xD9); //--set pre-charge period
	ssd1308_write_command(0x22); //
	ssd1308_write_command(0xDA); //--set com pins hardware configuration
	ssd1308_write_command(0x12);
	ssd1308_write_command(0xDB); //--set vcomh
	ssd1308_write_command(0x20); //0x20,0.77xVcc
	ssd1308_write_command(0x8D); //--set DC-DC enable
	ssd1308_write_command(0x14); //
	ssd1308_write_command(0xAF); //--turn on SSD1308 panel
    ssd1308_write_command(0x2E); // deactivate scrolling

    ssd1308_fill(SSD1308_PIXEL_OFF);
    ssd1308_update_screen();
    ssd1308->currentX = 0;
    ssd1308->currentY = 0;
    ssd1308->isInverted = 0;
    ssd1308->isInit = 1;

    return 0;
}

void ssd1308_update_screen(void) {
    for (uint8_t page = 0; page < 8; page++) {
        ssd1308_write_command(0xB0 + page);
        ssd1308_write_command(0x00);
        ssd1308_write_command(0x10);
        ssd1308_I2C_write_multiple(SSD1308_BASE_ADDRESS, SSD1308_DATA_REGISTER, &SSD1308_Buffer[SSD1308_WIDTH * page], SSD1308_WIDTH);
    }
}

void ssd1308_invert_display(SSD1308_t* ssd1308) {
    if (ssd1308->isInverted) {
        ssd1308_write_command(SSD1308_CMD_SET_NORMAL_DISPLAY);
        ssd1308->isInverted = 0;
    } else {
        ssd1308_write_command(SSD1308_CMD_SET_INVERTED_DISPLAY);
        ssd1308->isInverted = 1;
    }
}

void ssd1308_fill(uint8_t color) {
    memset(SSD1308_Buffer, (color == SSD1308_PIXEL_ON) ? 0xFF : 0x00, sizeof(SSD1308_Buffer));
}

void ssd1308_draw_pixel(SSD1308_t* ssd1308, uint16_t x, uint16_t y, uint8_t color) {
    if (x >= SSD1308_WIDTH || y >= SSD1308_HEIGHT) {
        return;
    }

    if(ssd1308->isInverted) {
        color = (color == SSD1308_PIXEL_ON) ? SSD1308_PIXEL_OFF : SSD1308_PIXEL_ON;
    }

    if (color == SSD1308_PIXEL_ON) {
        SSD1308_Buffer[x + (y / 8) * SSD1308_WIDTH] |= (1 << (y % 8));
    } else {
        SSD1308_Buffer[x + (y / 8) * SSD1308_WIDTH] &= ~(1 << (y % 8));
    }
}

void ssd1308_gotoXY(SSD1308_t* ssd1308, uint16_t x, uint16_t y) {
    ssd1308->currentX = x;
    ssd1308->currentY = y;
}

void ssd1308_put_char(SSD1308_t *ssd1308, char ch, FontDef* Font, uint8_t color) {
    if (SSD1308_HEIGHT <= (ssd1308->currentY + Font->FontHeight) ||
        SSD1308_WIDTH <= (ssd1308->currentX + Font->FontWidth)) {
        return;
    }
    for (uint32_t i = 0; i < Font->FontHeight; i++) {
        uint32_t line = Font->data[(ch - 32) * Font->FontHeight + i];
        for (uint32_t j = 0; j < Font->FontWidth; j++) {
            if ((line << j) & 0x8000) {
                ssd1308_draw_pixel(ssd1308, ssd1308->currentX + j, ssd1308->currentY + i, color);
            } else {
                ssd1308_draw_pixel(ssd1308, ssd1308->currentX + j, ssd1308->currentY + i, (color == SSD1308_PIXEL_ON) ? SSD1308_PIXEL_OFF : SSD1308_PIXEL_ON);
            }
        }
    }
    ssd1308->currentX += Font->FontWidth;
}


void ssd1308_put_string(SSD1308_t *ssd1308, char* str, FontDef* Font, uint8_t color) {
    while (*str) {
        ssd1308_put_char(ssd1308, *str++, Font, color);
    }
}