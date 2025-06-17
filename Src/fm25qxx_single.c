#include "fm25qxx_single.h"
#include "qspi.h"

static QSPI_CmdTypeDef   xfer;

void FM25QxxReset(void)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_EnableReset;
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
//    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_Reset;
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

    FL_DelayUs(30);
}
void FM25QxxWriteEnable(void)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
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

void FM25QxxWriteDisable(void)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
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

uint8_t FM25QxxReadStatus1(void)
{
    uint8_t buf[1] = {0u};
          
// Status Bit0-7    
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_ReadStatusReg1;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_SINGLE;
    xfer.DataLen            = sizeof(buf);        
    (void)QSpiReadData(&xfer, buf, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
        
    return buf[0];
}

uint8_t FM25QxxReadStatus2(void)
{
    uint8_t buf[1] = {0u};
          
// Status Bit8-15    
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_ReadStatusReg2;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0x00;
    xfer.DummyCycles        = 0u;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_SINGLE;
    xfer.DataLen            = sizeof(buf);        
    (void)QSpiReadData(&xfer, buf, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
        
    return buf[0];
}

void FM25QxxWriteStatus1(uint8_t status)
{
    FM25QxxWriteEnable();
    
    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_WriteStatusReg1;
    xfer.AddressMode         = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;
    xfer.Address             = 0x000000; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 0u;        
    xfer.DataMode            = FL_QSPI_DATA_MODE_SINGLE;
    xfer.DataLen             = 1u;        
    (void)QSpiWriteData(&xfer, &status, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    FM25QxxWriteDisable();
    
    //等待状态寄存器最大写入周期
    FL_DelayMs(15);
}

void FM25QxxWriteStatus2(uint8_t status)
{
    FM25QxxWriteEnable();
    
    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_WriteStatusReg2;
    xfer.AddressMode         = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;
    xfer.Address             = 0x000000; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 0u;        
    xfer.DataMode            = FL_QSPI_DATA_MODE_SINGLE;
    xfer.DataLen             = 1u;        
    (void)QSpiWriteData(&xfer, &status, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    FM25QxxWriteDisable();
    
    //等待状态寄存器最大写入周期
    FL_DelayMs(15);
}

void FM25QxxEnable_QE(void)
{
    FM25QxxWriteStatus2(0x02);
}

/* wait write or erase done. */
static void X25Q_WaitBusyBlocking()
{
    while(0u != (FM25QxxReadStatus1() & 0x1))
    {
    }
}


void FM25QxxEraseSector(uint32_t address)
{
    FM25QxxWriteEnable();               
    
    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_SectorErase;        
    xfer.AddressMode         = FL_QSPI_AD_MODE_SINGLE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address             = address; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 0u;        
    xfer.DataMode            = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen             = 0u;        
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);    
    
    X25Q_WaitBusyBlocking();  /* wait for erase sector done. */
    
    FM25QxxWriteDisable();
}

void FM25QxxEraseChip(void)
{
    FM25QxxWriteEnable();  
    
    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_ChipErase;        
    xfer.AddressMode         = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address             = 0x00; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 0u;        
    xfer.DataMode            = FL_QSPI_DATA_MODE_NONE;
    xfer.DataLen             = 0u;        
    (void)QSpiWriteData(&xfer, NULL, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);        
        
    X25Q_WaitBusyBlocking();  /* wait for erase sector done. */

    FM25QxxWriteDisable();
}

/* write page. */
static void X25Q_WritePage(uint32_t addr, uint32_t size, uint8_t *buf)
{
    if (addr + size > FM25Q16A_MemSize) /* addr overflow. */
    {
        return;
    }

    FM25QxxWriteEnable(); /* must enable write before write page. */
    
    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_PageProgram;        
    xfer.AddressMode         = FL_QSPI_AD_MODE_SINGLE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;         
    xfer.Address             = addr; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 0u;        
    xfer.DataMode            = FL_QSPI_DATA_MODE_SINGLE;
    xfer.DataLen             = size;    
    (void)QSpiWriteData(&xfer, buf, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);        
        
    X25Q_WaitBusyBlocking(); /* wait for write page done (chip idle). */

    FM25QxxWriteDisable(); /* close write. */
}

void FM25QxxProgramPage(uint32_t address, uint8_t *buffer, uint16_t length)
{    
    uint32_t xfer_count  = 0u;
    uint32_t xfer_remain = length;
    uint32_t xfer_size   = 0u;

    /* align write. */
    if (0u != address % FM25Q16A_PageSize)
    {
        uint32_t xfer_align = FM25Q16A_PageSize - (address % FM25Q16A_PageSize);

        xfer_size = (xfer_remain > xfer_align ? xfer_align : xfer_remain);

        X25Q_WritePage(address + xfer_count, xfer_size, &buffer[xfer_count]);
        xfer_remain -= xfer_size;
        xfer_count += xfer_size;
    }

    /* page write. */
    while(xfer_remain > 0u)
    {
        xfer_size = (xfer_remain > FM25Q16A_PageSize ? FM25Q16A_PageSize : xfer_remain);
        X25Q_WritePage(address + xfer_count, xfer_size, &buffer[xfer_count]);
        xfer_remain -= xfer_size;
        xfer_count += xfer_size;
    }

}

void FM25QxxReadFast(uint32_t address, uint8_t *buffer, uint16_t length)
{
    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_FastRead;        
    xfer.AddressMode         = FL_QSPI_AD_MODE_SINGLE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;         
    xfer.Address             = address; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 8;
    xfer.DataMode            = FL_QSPI_DATA_MODE_SINGLE;
    xfer.DataLen             = length;        
    (void)QSpiReadData(&xfer, buffer, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
}

uint32_t FM25QxxJEDECID(void)
{
    uint8_t id[4] = {0};

    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_JedecDeviceID;        
    xfer.AddressMode         = FL_QSPI_AD_MODE_NONE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;         
    xfer.Address             = 0; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 0;        
    xfer.DataMode            = FL_QSPI_DATA_MODE_SINGLE;    
    xfer.DataLen             = sizeof(id);        
    (void)QSpiReadData(&xfer, id, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    return (id[0] << 16)|(id[1] << 8) | (id[2]);
}

uint32_t FM25QxxManufactDeviceID(void)
{    
    uint8_t id[2] = {0};
                
    xfer.InstructionMode     = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction         = CMD_FM25Q_ManufactDeviceID;        
    xfer.AddressMode         = FL_QSPI_AD_MODE_SINGLE;
    xfer.AddressSize         = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address             = 0x000000; 
    xfer.AlternateByteMode   = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize   = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte       = 0x00;
    xfer.DummyCycles         = 0;        
    xfer.DataMode            = FL_QSPI_DATA_MODE_SINGLE;    
    xfer.DataLen             = sizeof(id);
    (void)QSpiReadData(&xfer, id, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    return ((id[0] << 8)|id[1]);
}


