/*
 * BSP_CAN.h
 *
 *  Created on: 15 mars 2019
 *      Author: Marc-Andre
 */

#ifndef BSP_BSP_CAN_H_
#define BSP_BSP_CAN_H_

#include "stdint.h"

typedef struct __attribute__ ((__packed__)) {
	//byte 0
	uint8_t RegId;
	//byte 1
	unsigned : 4;
	enum {INT32,UINT32,FLOAT,CHAR_ARRAY} dataType : 4;

} canReg_t;





#endif /* BSP_BSP_CAN_H_ */
