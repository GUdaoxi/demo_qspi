#include "FM25Qxx_QPI.h"
#include "fm25qxx_single.h"
#include "qspi.h"
#include <stdio.h>

static QSPI_CmdTypeDef   xfer;

void FM25QxxInit_QPI(void)
{    
    // 使能QE
    FM25QxxEnable_QE();
    
    // 使能QPI
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_EnableQPI;
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;
    xfer.DataMode           = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen            = 0u;
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
}

void FM25QxxDeInit_QPI(void)
{
    uint16_t status;
    
    // 退出QPI
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_DisableQPI;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen            = 0u;        
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    FL_DelayMs(15);

    status = FM25QxxReadStatus1();
    status = FM25QxxReadStatus2();        
    FM25QxxWriteStatus2(status & 0xfd);
    
    QSpiDeInit();
}

static void FM25QxxWriteEnable_QPI(void)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_WriteEnable;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen            = 0u;        
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
}

static void FM25QxxWriteDisable_QPI(void)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_WriteDisable;
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen            = 0u;        
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
}

uint8_t FM25QxxReadStatus1_QPI(void)
{
    uint8_t buf[1] = {0u}; 
// Status Bit0-7    
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_ReadStatusReg1;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = sizeof(buf);        
    (void)QSpiReadData(&xfer, buf, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    return buf[0];
}

uint8_t FM25QxxReadStatus2_QPI(void)
{
    uint8_t buf[1] = {0u};
   
// Status Bit8-15
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_ReadStatusReg2;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = sizeof(buf);        
    (void)QSpiReadData(&xfer, buf, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    return buf[0];
}

void FM25QxxWriteStatus1_QPI(uint8_t status)
{
    FM25QxxWriteEnable_QPI();
    
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_WriteStatusReg1;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = 1u;        
    (void)QSpiWriteData(&xfer, &status, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    FM25QxxWriteDisable_QPI();
        
        //等待写完成
    FL_DelayMs(5);
}

void FM25QxxWriteStatus2_QPI(uint8_t status)
{
    FM25QxxWriteEnable_QPI();
    
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_WriteStatusReg2;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = 1u;        
    (void)QSpiWriteData(&xfer, &status, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
      
    FM25QxxWriteDisable_QPI();
    
    //等待写完成
    FL_DelayMs(5);
}

/* wait write or erase done. */
static void X25Q_WaitBusyBlocking_QPI()
{
    while(0u != (FM25QxxReadStatus1_QPI() & 0x01) )
    {
    }
}


void FM25QxxEraseSector_QPI(uint32_t address)
{
    FM25QxxWriteEnable_QPI();                    
    
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_SectorErase;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_FOUR;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;
    xfer.Address            = address; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen            = 0u;        
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    X25Q_WaitBusyBlocking_QPI();  /* wait for erase sector done. */
    
    FM25QxxWriteDisable_QPI();
}

void FM25QxxEraseChip_QPI(void)
{
    FM25QxxWriteEnable_QPI();                    
    
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_ChipErase;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen            = 0u;        
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
            
    X25Q_WaitBusyBlocking_QPI();  /* wait for erase sector done. */
                
    FM25QxxWriteDisable_QPI();
}

/* write page. */
static void X25Q_WritePage_QPI(uint32_t addr, uint32_t size, uint8_t *buf)
{
    if (addr + size > FM25Q16A_MemSize) /* addr overflow. */
    {
        return;
    }

    FM25QxxWriteEnable_QPI(); /* must enable write before write page. */
    
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_PageProgram;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_FOUR;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = addr; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = size;    
    (void)QSpiWriteData(&xfer, buf, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);

    X25Q_WaitBusyBlocking_QPI(); /* wait for write page done (chip idle). */

    FM25QxxWriteDisable_QPI(); /* close write. */
}

void FM25QxxProgramPage_QPI(uint32_t address, uint8_t *buffer, uint16_t length)
{
    uint32_t xfer_count  = 0u;
    uint32_t xfer_remain = length;
    uint32_t xfer_size   = 0u;

    /* align write. */
    if (0u != address % FM25Q16A_PageSize)
    {
        uint32_t xfer_align = FM25Q16A_PageSize - (address % FM25Q16A_PageSize);

        xfer_size = (xfer_remain > xfer_align ? xfer_align : xfer_remain);

        X25Q_WritePage_QPI(address + xfer_count, xfer_size, &buffer[xfer_count]);
        xfer_remain -= xfer_size;
        xfer_count += xfer_size;
    }

    /* page write. */
    while(xfer_remain > 0u)
    {
        xfer_size = (xfer_remain > FM25Q16A_PageSize ? FM25Q16A_PageSize : xfer_remain);
        X25Q_WritePage_QPI(address + xfer_count, xfer_size, &buffer[xfer_count]);
        xfer_remain -= xfer_size;
        xfer_count += xfer_size;
    }      
}

void FM25QxxReadFast_QPI(uint32_t address, uint8_t *buffer, uint16_t length)
{        
    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_FastRead;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_FOUR;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = address;
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 2;
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = length;
    (void)QSpiReadData(&xfer, buffer, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
}

uint32_t FM25QxxJEDECID_QPI(void)
{
    uint8_t id[4] = {0};

    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
    xfer.Instruction        = CMD_FM25Q_JedecDeviceID;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0;
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0;
    xfer.DummyCycles        = 0;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = sizeof(id);        
    (void)QSpiReadData(&xfer, id, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    return (id[0] << 16)|(id[1] << 8) | (id[2]);
}

// 使能XIP
//void FM25QxxXIP_QPI(void)
//{
//    xfer.InstructionMode    = FL_QSPI_IMODE_FOUR;
//    xfer.Instruction        = CMD_FM25Q_FastReadIO_Quad;        
//    xfer.AddressMode        = FL_QSPI_AD_MODE_FOUR;
//    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
//    xfer.Address            = 0x10000000; 
//    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_FOUR;
//    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
//    xfer.AlternateByte      = 0x20;
//    xfer.DummyCycles        = 2;
//    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
//    xfer.DataLen            = 0;
//    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
//    FL_QSPI_ClearFlag_TransferComplete(QSPI);
//}
