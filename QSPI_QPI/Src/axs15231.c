#include "fm33fh0xx_fl_qspi.h"
#include "AXS15231.h"
#include "main.h"
#include <stdint.h>

#define AXS15231_CMD_WRITE_DATA      0x2C
#define AXS15231_CMD_SET_COLUMN      0x2A
#define AXS15231_CMD_SET_PAGE        0x2B
#define AXS15231_RED                 0xF800
#define AXS15231_GREEN               0x07E0
#define AXS15231_BLUE                0x001F
#define AXS15231_CMD_WRITE_DATA_DUAL 0x12
#define AXS15231_CMD_WRITE_DATA_SINGLE 0x02

#define TFT_CS_H()    FL_GPIO_SetOutputPin(GPIOC, FL_GPIO_PIN_8)
#define TFT_CS_L()    FL_GPIO_ResetOutputPin(GPIOC, FL_GPIO_PIN_8)

static void QSPI_BlockWrite(uint8_t instruction, const uint8_t* data, uint32_t length)
{
    QSPI_CmdTypeDef cmd = {0};

    cmd.Instruction        = instruction;
    cmd.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    cmd.AddressMode        = FL_QSPI_AD_MODE_NONE;
    cmd.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    cmd.Address            = 0x000000;
    cmd.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    cmd.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    cmd.AlternateByte      = 0;
    cmd.DummyCycles        = 0;
    cmd.DataMode           = length ? FL_QSPI_DATA_MODE_DOUBLE : FL_QSPI_DATA_MODE_NONE;
    cmd.DataLen            = length;

    TFT_CS_L();
    FL_QSPI_EnableABORT(QSPI); 
    QSpiWriteData(&cmd, (uint8_t*)data, length);
    TFT_CS_H();
}

static void QSPI_WriteDataStream(const uint8_t* data, uint32_t length)
{
    QSPI_CmdTypeDef cmd = {0};

    cmd.InstructionMode = FL_QSPI_IMODE_NONE;
    cmd.AddressMode = FL_QSPI_AD_MODE_NONE;
    cmd.DataMode = FL_QSPI_DATA_MODE_DOUBLE;
    cmd.DataLen = length;

    TFT_CS_L();
    QSpiWriteData(&cmd, (uint8_t*)data, length);
    TFT_CS_H();
}


void AXS15231_WriteDataBlock(uint8_t instruction, const uint8_t* data, uint32_t length)
{
    QSPI_CmdTypeDef cmd = {0};

    cmd.Instruction        = instruction;
    cmd.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    cmd.AddressMode        = FL_QSPI_AD_MODE_NONE;
    cmd.DataMode           = FL_QSPI_DATA_MODE_DOUBLE;
    cmd.DataLen            = length;

    TFT_CS_L();
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

    FL_QSPI_Init(QSPI, &cfg);
    FL_QSPI_Enable(QSPI);
}

void AXS15231_WriteCommand(uint8_t cmd)
{
    QSPI_BlockWrite(cmd, NULL, 0);
}

void AXS15231_WriteData(uint8_t data)
{
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

//void AXS15231_FillRed(uint32_t count)
//{
//    uint8_t buffer[256];
//    for (int i = 0; i < sizeof(buffer); i += 2) {
//        buffer[i] = AXS15231_RED >> 8;
//        buffer[i+1] = AXS15231_RED & 0xFF;
//    }
//
//    // 替代写法：单指令模式已失败，可尝试如下整合方式
//    // AXS15231_WriteCommand(AXS15231_CMD_WRITE_DATA);
//    // ... 分段 QSPI_WriteDataStream ...
//
//    uint32_t bytes = count * 2;
//    while (bytes > 0) {
//        uint32_t chunk = (bytes > sizeof(buffer)) ? sizeof(buffer) : bytes;
//        AXS15231_WriteDataBlock(AXS15231_CMD_WRITE_DATA, buffer, chunk);
//        bytes -= chunk;
//    }
//}
void AXS15231_FillRed(uint32_t count)
{
    uint8_t buffer[256];
    uint16_t colors[3] = {AXS15231_RED, AXS15231_GREEN, AXS15231_BLUE};
    uint32_t bytes = count * 2;
    uint32_t index = 0;

    while (bytes > 0) {
        for (int i = 0; i < sizeof(buffer); i += 2) {
            uint16_t color = colors[index++ % 3];
            buffer[i] = color >> 8;
            buffer[i+1] = color & 0xFF;
        }
        uint32_t chunk = (bytes > sizeof(buffer)) ? sizeof(buffer) : bytes;
        AXS15231_WriteDataBlock(AXS15231_CMD_WRITE_DATA, buffer, chunk);
        bytes -= chunk;
    }
}
