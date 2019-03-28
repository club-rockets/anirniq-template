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
#define MESSAGE_ID_MASK ( ( (1<<MESSAGE_ID_SIZE)-1)<<(BOARD_ID_SHIFT+BOARD_ID_SIZE))
#define BOARD_EMERGENCY_ID		0
#define BOARD_MISSION_ID		1
#define BOARD_COMMUNICATION_ID	2
#define BOARD_ACQUISITION_ID	3
#define BOARD_MOTHERBOARD_ID 	4

#define CAN_BOARD MOTHERBOARD
#define CAN_BOARD_ID BOARD_MOTHERBOARD_ID

#define CAN_REG_DATA_SIZE 8

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
	void (*changeCallback)(uint32_t,uint32_t);
} can_reg_t;



uint32_t can_canInit();

uint32_t can_canSetRegisterData(uint32_t index,can_regData_u* data);

uint32_t can_getRegisterData(enum can_board board, uint32_t index, can_regData_u* reg);

uint32_t can_getRegisterTimestamp(enum can_board board, uint32_t index);

uint32_t can_setRegisterCallback(uint32_t index, void (*callback)(uint32_t,uint32_t));

//called on reception of a new packet
void can_regUpdateCallback(void);

//Send can frame but doesnt update local register (to be used in loopback mode)
uint32_t can_canSetRegisterLoopback(uint32_t board, uint32_t index,can_regData_u* data);

//set local register without sending it to canbus (use for testing)
uint32_t can_canSetRegisterSelf(uint32_t board, uint32_t index,can_regData_u* data);

#endif /* BSP_BSP_CAN_H_ */
