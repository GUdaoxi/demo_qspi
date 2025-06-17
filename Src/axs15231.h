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
// Quad SPI memory write command used by AXS15231B when transferring data over
// four data lines
#define TFT_CMD_RAMWR4      0x32

/* MADCTL 参数位 */
#define MADCTL_MX           0x40
#define MADCTL_MY           0x80
#define MADCTL_MV           0x20
#define MADCTL_BGR          0x08

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

#endif
