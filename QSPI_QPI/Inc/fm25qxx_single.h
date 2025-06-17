#ifndef FM25QXX_SINGLE_H
#define FM25QXX_SINGLE_H

#include "fm33fh0xx_fl.h"

void FM25QxxReset(void);
void FM25QxxWriteEnable(void);
void FM25QxxWriteDisable(void);

void FM25QxxEnable_QE(void);
	
uint8_t FM25QxxReadStatus1(void);
uint8_t FM25QxxReadStatus2(void);
void FM25QxxWriteStatus1(uint8_t status);
void FM25QxxWriteStatus2(uint8_t status);

void FM25QxxEraseSector(uint32_t address);
void FM25QxxEraseChip(void);
void FM25QxxProgramPage(uint32_t address, uint8_t *buffer, uint16_t length);
void FM25QxxReadFast(uint32_t address, uint8_t *buffer, uint16_t length);

uint32_t FM25QxxJEDECID(void);
uint32_t FM25QxxManufactDeviceID(void);

#endif
