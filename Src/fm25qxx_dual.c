#include "fm25qxx_dual.h"
#include "qspi.h"

static QSPI_CmdTypeDef   xfer;

uint32_t FM25QxxManufactDeviceID_Dual(void)
{    
    uint8_t id[2] = {0};

    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_ManufactDeviceID_Dual;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_DOUBLE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = 0x000000; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_DOUBLE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0xf0;
    xfer.DummyCycles        = 0;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_DOUBLE;
    xfer.DataLen            = sizeof(id);        
    (void)QSpiReadData(&xfer, id, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
    
    return ((id[0] << 8)|id[1]);
}

void FM25QxxReadFastOutput_Dual(uint32_t address, uint8_t *buffer, uint16_t length)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_FastReadOUT_Dual;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_SINGLE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits; 
    xfer.Address            = address; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_NONE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0;
    xfer.DummyCycles        = 8;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_DOUBLE;
    xfer.DataLen            = length;        
    (void)QSpiReadData(&xfer, buffer, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
}

void FM25QxxReadFastIO_Dual(uint32_t address, uint8_t *buffer, uint16_t length)
{
    xfer.InstructionMode    = FL_QSPI_IMODE_SINGLE;
    xfer.Instruction        = CMD_FM25Q_FastReadIO_Dual;        
    xfer.AddressMode        = FL_QSPI_AD_MODE_DOUBLE;
    xfer.AddressSize        = FL_QSPI_AD_SIZE_24bits;     
    xfer.Address            = address; 
    xfer.AlternateByteMode  = FL_QSPI_AB_MODE_DOUBLE;
    xfer.AlternateByteSize  = FL_QSPI_AB_SIZE_8bits;
    xfer.AlternateByte      = 0xf0;
    xfer.DummyCycles        = 0;        
    xfer.DataMode           = FL_QSPI_DATA_MODE_DOUBLE;    
    xfer.DataLen            = length;        
   (void)QSpiReadData(&xfer, buffer, xfer.DataLen);
    FL_QSPI_ClearFlag_TransferComplete(QSPI);
}
