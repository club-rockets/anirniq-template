/*
 * heartBeat.h
 *
 *  Created on: 14 mars 2019
 *      Author: Marc-Andre
 *
 *      This thread blinks a led to show that the board is alive
 *
 */


#include "APP_heartBeat.h"
#include "stm32f4xx_hal.h"

void tsk_heartBeat(void const * argument){

	while(1){
		HAL_GPIO_TogglePin(HEARTBEAT_LED_PORT,HEARTBEAT_LED_PIN);
		osDelay(100);
	}
}
