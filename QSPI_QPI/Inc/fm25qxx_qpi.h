#ifndef FM25QXX_QPI_H
#define FM25QXX_QPI_H

#include "fm33fh0xx_fl.h"

void FM25QxxInit_QPI(void);
void FM25QxxDeInit_QPI(void);

uint8_t FM25QxxReadStatus1_QPI(void);
uint8_t FM25QxxReadStatus2_QPI(void);
void FM25QxxWriteStatus1_QPI(uint8_t status);
void FM25QxxWriteStatus2_QPI(uint8_t status);

void FM25QxxEraseSector_QPI(uint32_t addr);
void FM25QxxEraseChip_QPI(void);
void FM25QxxProgramPage_QPI(uint32_t address, uint8_t *buffer, uint16_t length);
void FM25QxxReadFast_QPI(uint32_t address, uint8_t *buffer, uint16_t length);

uint32_t FM25QxxJEDECID_QPI(void);

void FM25QxxXIP_QPI(void);

#endif
