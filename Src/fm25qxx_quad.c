#include "fm25qxx_quad.h"
#include "qspi.h"

static QSPI_CmdTypeDef   xfer;
    
uint32_t FM25QxxManufactDeviceID_Quad(void)
{
    uint8_t id[2] = {0};

    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_ManufactDeviceID_Quad;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_FOUR;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_FOUR;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0xf0;
    xfer.DummyCycles        = 4;
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = sizeof(id);
    (void)QSpiReadData(&xfer, id, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);        
    
    return ((id[0] << 8)|id[1]);
}


void FM25QxxReadFastOutput_Quad(uint32_t address, uint8_t *buffer, uint16_t length)
{        
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_FastReadOUT_Quad;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_SINGLE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = address; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0;
    xfer.DummyCycles        = 8;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = length;        
    (void)QSpiReadData(&xfer, buffer, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);        
}

void FM25QxxReadFastIO_Quad(uint32_t address, uint8_t *buffer, uint16_t length)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_FastReadIO_Quad;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_FOUR;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;         
    xfer.Address            = address; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_FOUR;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0xf0;
    xfer.DummyCycles        = 4;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_FOUR;
    xfer.DataLen            = length;        
   (void)QSpiReadData(&xfer, buffer, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);        
}
