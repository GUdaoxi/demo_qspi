#include "qspi.h"

// QSPI_nCS：PC8  || PB2
// QSPI_CLK：PC9  || PB3
// QSPI_DQ0：PC10 || PB10
// QSPI_DQ1：PC11 || PB11
// QSPI_DQ2：PC12 || PB12
// QSPI_DQ3：PC13 || PB13

void QSpiInit(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct={0};
    QSPI_InitTypeDef       QSPI_Init={0};
    
    GPIO_InitStruct.pin           = FL_GPIO_PIN_8|FL_GPIO_PIN_9|FL_GPIO_PIN_12|FL_GPIO_PIN_13;
    GPIO_InitStruct.mode          = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType    = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull          = FL_GPIO_BOTH_DISABLE;
    GPIO_InitStruct.remapPin      = FL_GPIO_PINREMAP_FUNCTON2;
    GPIO_InitStruct.driveStrength = FL_GPIO_DRIVESTRENGTH_X3;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    GPIO_InitStruct.pin           = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode          = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType    = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull          = FL_GPIO_BOTH_DISABLE;
    GPIO_InitStruct.remapPin      = FL_GPIO_PINREMAP_FUNCTON2;
    GPIO_InitStruct.driveStrength = FL_GPIO_DRIVESTRENGTH_X3;
    (void)FL_GPIO_Init(GPIOB, &GPIO_InitStruct);    
    
    GPIO_InitStruct.pin           = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode          = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType    = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull          = FL_GPIO_BOTH_DISABLE;
    GPIO_InitStruct.remapPin      = FL_GPIO_PINREMAP_FUNCTON0;
    GPIO_InitStruct.driveStrength = FL_GPIO_DRIVESTRENGTH_X3;
    (void)FL_GPIO_Init(GPIOB, &GPIO_InitStruct);    
    
    QSPI_Init.ClockPrescaler     = 2-1;
    QSPI_Init.FifoThreshold      = FL_QSPI_FIFOTHR_8;
    QSPI_Init.SampleShifting     = FL_DISABLE;
    QSPI_Init.ChipSelectHighTime = FL_QSPI_CYCLE_1;
    QSPI_Init.ClockMode          = FL_QSPI_CLKMODE_0;
    (void)FL_QSPI_Init(QSPI, &QSPI_Init);
    
    FL_QSPI_EnableABORT(QSPI);     //终止传输
    FL_QSPI_Enable(QSPI);          //使能QSPI
}

void QSpiDeInit(void)
{

}

static void QSPI_DR_WriteByte(uint8_t SetValue)
{
    *((uint8_t *)&(QSPI->DR)) = (SetValue);
}

static uint8_t QSPI_DR_ReadByte(void)
{
    return (*((uint8_t *)&(QSPI->DR)));
}

__USED static void QSPI_DR_WriteHalfword(uint16_t SetValue)
{
    *((uint16_t *)&(QSPI->DR)) = (SetValue);
}

__USED static uint16_t QSPI_DR_ReadHalfword(void)
{
    return (*((uint16_t *)&(QSPI->DR)));
}

__USED static void QSPI_DR_WriteWord(uint32_t SetValue)
{
    *((uint32_t *)&(QSPI->DR)) = (SetValue);
}

__USED static uint32_t QSPI_DR_ReadWord(void)
{
    return (*((uint32_t *)&(QSPI->DR)));
}

bool QSpiWriteData(QSPI_CmdTypeDef *Cmd, uint8_t *data, uint16_t length)
{
      FL_QSPI_EnableABORT(QSPI);     //终止传输
    
    /* 配置传输数据长度 */
    FL_QSPI_WriteDataLength(QSPI, Cmd->DataLen - 1);    
    /* 配置发送的alternate bytes */
    FL_QSPI_WriteAlternateBytes(QSPI, Cmd->AlternateByte);
    
    QSPI->CCR = (FL_QSPI_OPERATION_MODE_WRITE| Cmd->DataMode|(Cmd->DummyCycles << 18) |
                   Cmd->AlternateByteSize |Cmd->AlternateByteMode |Cmd->AddressSize |
                   Cmd->AddressMode | Cmd->InstructionMode |Cmd->Instruction);
    
    /* 发送的地址 */
    FL_QSPI_WriteAddress(QSPI, Cmd->Address);
    
    while (length--)
    {
        QSPI_DR_WriteByte(*data);
        data++;
    }
    while(FL_QSPI_IsActiveFlag_Busy(QSPI));
    
    return true;
}

bool QSpiReadData(QSPI_CmdTypeDef *Cmd, uint8_t *data, uint16_t length)
{
      FL_QSPI_EnableABORT(QSPI);     //终止传输
    /* 配置传输数据长度 */
    FL_QSPI_WriteDataLength(QSPI, Cmd->DataLen - 1);    
    /* 配置发送的alternate bytes */
    FL_QSPI_WriteAlternateBytes(QSPI, Cmd->AlternateByte);

    QSPI->CCR = (FL_QSPI_OPERATION_MODE_READ| Cmd->DataMode|(Cmd->DummyCycles << 18) |
                   Cmd->AlternateByteSize |Cmd->AlternateByteMode |Cmd->AddressSize |
                   Cmd->AddressMode | Cmd->InstructionMode |Cmd->Instruction);
                
    /* 发送的地址 */
    FL_QSPI_WriteAddress(QSPI, Cmd->Address);


    while (length--)
    {
        while (FL_QSPI_ReadFIFOLevel(QSPI) == 0);
        *data = QSPI_DR_ReadByte();
        data++;
    }
    while (FL_QSPI_IsActiveFlag_Busy(QSPI));
    
    return true;
}





