/*
 * BSP_CAN.h
 *
 *  Created on: 15 mars 2019
 *      Author: Marc-Andre
 */

#ifndef BSP_BSP_CAN_H_
#define BSP_BSP_CAN_H_

#include "stdint.h"
#include "canDriver.h"

//Boards ID defined here

#define BOARD_ID_SHIFT 			1
#define BOARD_ID_SIZE			5
#define MESSAGE_ID_SIZE			6

#define BOARD_ID_MASK	( ( (1<<BOARD_ID_SIZE)-1)<<BOARD_ID_SHIFT)
#define BOARD_EMERGENCY_ID		0
#define BOARD_MISSION_ID		1
#define BOARD_COMMUNICATION_ID	2
#define BOARD_ACQUISITION_ID	3
#define BOARD_MOTHERBOARD_ID 	4

#define CAN_BOARD MOTHERBOARD
#define CAN_BOARD_ID BOARD_MOTHERBOARD_ID

enum can_board{
	EMERGENCY = 0,
	MISSION,
	COMMUNICATION,
	ACQUISITION,
	MOTHERBOARD
};

typedef union{
	uint32_t UINT32_T;
	int32_t INT32_T;
	float	FLOAT;
	uint8_t UINT8_T[8];
	int8_t INT8_T[8];
} can_regData_u;

typedef struct{
	can_regData_u data;
	uint32_t lastTick;
	const char* name;
	void (*changeCallback)(uint32_t regId);
} can_reg_t;

uint32_t can_canInit();

uint32_t can_canSetRegister(uint32_t index,can_regData_u data);

#endif /* BSP_BSP_CAN_H_ */
