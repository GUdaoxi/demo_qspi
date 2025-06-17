#ifndef QSPI_H
#define QSPI_H

#include "fm33fh0xx_fl.h"

#define FM25Q16A_MemSize            0x200000
#define FM25Q16A_PageSize           0x100

//FM25Q系列芯片ID列表   
#define JDID_FM25Q_08   0xA14014 	
#define JDID_FM25Q_16 	0xA14015
#define JDID_FM25Q_32 	0xA14016
#define JDID_FM25Q_64 	0xA14017
#define JDID_FM25Q_128	0xA14018

#define MDID_FM25Q_08   0xA113	
#define MDID_FM25Q_16 	0xA114
#define MDID_FM25Q_32 	0xA115
#define MDID_FM25Q_64 	0xA116
#define MDID_FM25Q_128	0xA117

//FM25Q系列芯片指令列表
#define CMD_FM25Q_EnableReset             0x66
#define CMD_FM25Q_Reset                   0x99
         
#define CMD_FM25Q_WriteEnable             0x06 
#define CMD_FM25Q_WriteDisable            0x04 
        
#define CMD_FM25Q_ReadStatusReg1          0x05
#define CMD_FM25Q_ReadStatusReg2          0x35
      
#define CMD_FM25Q_WriteStatusReg1         0x01 
#define CMD_FM25Q_WriteStatusReg2         0x31 

#define CMD_FM25Q_PageProgram             0x02

#define CMD_FM25Q_SectorErase             0x20
#define CMD_FM25Q_BlockErase32K           0x52
#define CMD_FM25Q_BlockErase64K           0xD8
#define CMD_FM25Q_ChipErase               0x60

#define CMD_FM25Q_JedecDeviceID           0x9F 

// Standard SPI                         
#define CMD_FM25Q_FastRead                0x0B 
#define CMD_FM25Q_ManufactDeviceID        0x90 
// Dual SPI                             
#define CMD_FM25Q_FastReadOUT_Dual        0x3B
#define CMD_FM25Q_FastReadIO_Dual         0xBB
#define CMD_FM25Q_ManufactDeviceID_Dual   0x92
// Quad SPI                            
#define CMD_FM25Q_FastReadOUT_Quad        0x6B
#define CMD_FM25Q_FastReadIO_Quad         0xEB
#define CMD_FM25Q_ManufactDeviceID_Quad   0x94
// QPI                                 
#define CMD_FM25Q_EnableQPI               0x38
#define CMD_FM25Q_DisableQPI              0xFF

void QSpiInit(void);
void QSpiDeInit(void);
bool QSpiWriteData(QSPI_CmdTypeDef *Cmd, uint8_t *data, uint16_t length);
bool QSpiReadData(QSPI_CmdTypeDef *Cmd, uint8_t *data, uint16_t length);

#endif
