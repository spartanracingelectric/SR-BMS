/*
 * ltc6813.h
 *
 *  Created on: Sep 26, 2023
 *      Author: vsaw3
 */
#include <stdint.h>
#include "main.h"
#include "spi.h"

#ifndef INC_LTC6813_H_
#define INC_LTC6813_H_

/* Calculates  and returns the CRC15 */
uint16_t LTC_PEC15_Calc(uint8_t len, //Number of bytes that will be used to calculate a PEC
                    	uint8_t *data //Array of data that will be used to calculate a PEC
                   	   );

/* Set number of LTC6813/slave devices */
void LTC_Set_Num_Devices(uint8_t num);

/* Get number of LTC6813/slave devices */
uint8_t LTC_Get_Num_Devices(void);

/* Pull nCS line to SPI1 HIGH */
void LTC_nCS_High(void);

/* Pull nCS line to SPI1 LOW */
void LTC_nCS_Low(void);

/* Wake LTC up from IDLE state into READY state */
HAL_StatusTypeDef LTC_Wakeup_Idle(void);

#endif /* INC_LTC6813_H_ */
