#ifndef FM25QXX_QUAD_H
#define FM25QXX_QUAD_H

#include "fm33fh0xx_fl.h"

uint32_t FM25QxxManufactDeviceID_Quad(void);
void FM25QxxReadFastOutput_Quad(uint32_t address, uint8_t *buffer, uint16_t length);
void FM25QxxReadFastIO_Quad(uint32_t address, uint8_t *buffer, uint16_t length);

#endif
