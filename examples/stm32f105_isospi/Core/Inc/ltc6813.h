/*
 * ltc6813.h
 *
 *  Created on: Sep 26, 2023
 *      Author: vsaw3
 */
#include <stdint.h>
#include "main.h"

#ifndef INC_LTC6813_H_
#define INC_LTC6813_H_

/* Calculates  and returns the CRC15 */
uint16_t LTC_PEC15_Calc(uint8_t len, //Number of bytes that will be used to calculate a PEC
                    	uint8_t *data //Array of data that will be used to calculate a PEC
                   	   );



#endif /* INC_LTC6813_H_ */
