#ifndef FM25QXX_DUAL_H
#define FM25QXX_DUAL_H

#include "fm33fh0xx_fl.h"

uint32_t FM25QxxManufactDeviceID_Dual(void);
void FM25QxxReadFastOutput_Dual(uint32_t address, uint8_t *buffer, uint16_t length);
void FM25QxxReadFastIO_Dual(uint32_t address, uint8_t *buffer, uint16_t length);

#endif
