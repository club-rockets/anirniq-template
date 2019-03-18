/*
 * BSP_CAN.c
 *
 *  Created on: 15 mars 2019
 *      Author: Marc-Andre
 */

#include "BSP_CAN.H"
#include "BSP_can_regDef.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "cmsis_os.h"

canInstance_t can1Instance = {0};

uint32_t can_canInit(){

	//initialise IO's
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pins : PB8 PB9 */
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	can1Instance.instance = CAN1;
	can1Instance.debugFreeze = 0;
	can1Instance.opMode = loopback;
	can1Instance.baudPrescaler = 50;
	can1Instance.timeQuanta1 = 8;
	can1Instance.timeQuanta2 = 1;
	can1Instance.timeReSync = 1;

	canInit(&can1Instance);

	//init filters for boards

	canFilter_t filter = {0};

	filter.mask11.mask0 = BOARD_ID_MASK;
	filter.mask11.ID0 = BOARD_EMERGENCY_ID_SHIFTED;
	filter.mask11.mask1 = BOARD_ID_MASK;
	filter.mask11.ID1 = BOARD_MISSION_ID_SHIFTED;
	canSetFilter(&can1Instance,&filter,mask11Bit,0,0);

	filter.mask11.mask0 = BOARD_ID_MASK;
	filter.mask11.ID0 = BOARD_COMMUNICATION_ID_SHIFTED;
	filter.mask11.mask1 = BOARD_ID_MASK;
	filter.mask11.ID1 = BOARD_ACQUISITION_ID_SHIFTED;
	canSetFilter(&can1Instance,&filter,mask11Bit,1,0);

	filter.mask11.mask0 = BOARD_ID_MASK;
	filter.mask11.ID0 = BOARD_MOTHERBOARD_ID_SHIFTED;
	filter.mask11.mask1 = BOARD_ID_MASK;
	filter.mask11.ID1 = BOARD_MOTHERBOARD_ID_SHIFTED;
	canSetFilter(&can1Instance,&filter,mask11Bit,2,0);

	return 0;
}

uint32_t can_canSetRegister(uint32_t index,can_regData_u data){

	can_registers[CAN_BOARD][index].data = data;
	can_registers[CAN_BOARD][index].lastTick = osKernelSysTick();

	//todo init can with transmit interrupt
	//send register

	return 0;
}


