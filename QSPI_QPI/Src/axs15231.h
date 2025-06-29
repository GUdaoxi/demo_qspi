#ifndef __AXS15231_H
#define __AXS15231_H

#include <stdint.h>
#include "qspi.h"          // 一定要包含你的 QSPI 驱动头，才能使用 QSPI_CmdTypeDef 以及 QSpiWriteData()

#define TFT_CMD_SWRESET     0x01
#define TFT_CMD_SLPIN       0x10
#define TFT_CMD_SLPOUT      0x11
#define TFT_CMD_DISPOFF     0x28
#define TFT_CMD_DISPON      0x29
#define TFT_CMD_MADCTL      0x36
#define TFT_CMD_COLMOD      0x3A
#define TFT_CMD_CASET       0x2A
#define TFT_CMD_RASET       0x2B
#define TFT_CMD_RAMWR       0x2C

/* MADCTL 参数位 */
#define MADCTL_MX           0x40
#define MADCTL_MY           0x80
#define MADCTL_MV           0x20
#define MADCTL_BGR          0x08


#define AXS15231_CMD_WRITE_DATA      0x2C
#define AXS15231_CMD_SET_COLUMN      0x2A
#define AXS15231_CMD_SET_PAGE        0x2B
#define AXS15231_RED                 0xF800
#define AXS15231_GREEN               0x07E0
#define AXS15231_BLUE                0x001F
#define AXS15231_CMD_WRITE_DATA_DUAL 0x12
#define AXS15231_CMD_WRITE_DATA_SINGLE 0x02

/* 接口函数 */
// Initialize the LCD over QSPI
void AXS15231_QSPI_Init(void);

// Send a single command byte
void AXS15231_WriteCommand(uint8_t cmd);

// Send a single data byte
void AXS15231_WriteData(uint8_t data);

// Set drawing window (column/page)
void AXS15231_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

// Fill a number of pixels with red (count = width*height)
void AXS15231_FillRed(uint32_t count);
// Fill with an arbitrary RGB565 color
void AXS15231_FillColor(uint16_t color, uint32_t count);

// Send an initialization sequence similar to the SPI example
void AXS15231_ResetAndInit(void);

#endif  