#include "fm33fh0xx_fl_qspi.h"
#include "AXS15231.h"
#include "main.h"
#include <stdint.h>


#ifndef AXS15231_CMD_WRITE_DATA
#define AXS15231_CMD_WRITE_DATA      0x2C
#endif
#ifndef AXS15231_CMD_SET_COLUMN
#define AXS15231_CMD_SET_COLUMN      0x2A
#endif
#ifndef AXS15231_CMD_SET_PAGE
#define AXS15231_CMD_SET_PAGE        0x2B
#endif
#ifndef AXS15231_RED
#define AXS15231_RED                 0xF800    // RGB565 红色
#endif

#define AXS15231_CMD_WRITE_DATA_DUAL 0x12
#define AXS_QSPI                    QSPI

#define TFT_CS_H()    FL_GPIO_SetOutputPin(GPIOC, FL_GPIO_PIN_8)
#define TFT_CS_L()    FL_GPIO_ResetOutputPin(GPIOC, FL_GPIO_PIN_8)

static void QSPI_BlockWrite(uint8_t instruction, const uint8_t* data, uint32_t length)
{
    QSPI_CmdTypeDef cmd = {0};

    // 配置 QSPI 命令结构
    cmd.Instruction        = instruction;
    cmd.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    cmd.AddressMode        = FL_QSPI_AD_MODE_NONE;
    cmd.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    cmd.Address            = 0x000000;
    cmd.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    cmd.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    cmd.AlternateByte      = 0;
    cmd.DummyCycles        = 0;
    //cmd.DataMode           = length ? FL_QSPI_DATA_MODE_FOUR : FL_QSPI_DATA_MODE_NONE;
        cmd.DataMode           = length ? FL_QSPI_DATA_MODE_DOUBLE : FL_QSPI_DATA_MODE_NONE;
    cmd.DataLen            = length;

    TFT_CS_L();
    FL_QSPI_EnableABORT(QSPI); 
    QSpiWriteData(&cmd, (uint8_t*)data, length);
    TFT_CS_H();
}

void AXS15231_QSPI_Init(void)
{
    QSPI_InitTypeDef cfg = {0};
    cfg.ClockPrescaler     = 8 - 1;
    cfg.FifoThreshold      = FL_QSPI_FIFOTHR_8;
    cfg.SampleShifting     = FL_DISABLE;
    cfg.ChipSelectHighTime = FL_QSPI_CYCLE_2;
    cfg.ClockMode          = FL_QSPI_CLKMODE_0;

    FL_QSPI_Init(AXS_QSPI, &cfg);
    FL_QSPI_Enable(AXS_QSPI);
}

void AXS15231_WriteCommand(uint8_t cmd)
{
    QSPI_BlockWrite(cmd, NULL, 0);
}

void AXS15231_WriteData(uint8_t data)
{
   // QSPI_BlockWrite(AXS15231_CMD_WRITE_DATA, &data, 1);
    QSPI_BlockWrite(AXS15231_CMD_WRITE_DATA_DUAL, &data, 1);
}

void AXS15231_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint8_t buf[4];
    buf[0] = x0 >> 8; buf[1] = x0;
    buf[2] = x1 >> 8; buf[3] = x1;
    QSPI_BlockWrite(AXS15231_CMD_SET_COLUMN, buf, 4);

    buf[0] = y0 >> 8; buf[1] = y0;
    buf[2] = y1 >> 8; buf[3] = y1;
    QSPI_BlockWrite(AXS15231_CMD_SET_PAGE, buf, 4);
}

void AXS15231_FillRed(uint32_t count)
{
    uint8_t hi = AXS15231_RED >> 8;
    uint8_t lo = AXS15231_RED & 0xFF;
		uint32_t i;
    for( i= 0; i < count; i++) {
        AXS15231_WriteData(hi);
        AXS15231_WriteData(lo);
    }
}