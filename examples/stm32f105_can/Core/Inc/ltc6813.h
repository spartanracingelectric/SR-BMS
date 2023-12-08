/*
 * ltc6813.h
 *
 *  Created on: Sep 26, 2023
 *      Author: vsaw3
 */
#include <stdint.h>
#include "main.h"
#include "spi.h"
#include "string.h"


#ifndef INC_LTC6813_H_
#define INC_LTC6813_H_

/* Status enumeration for SPI in order
 * 	to fit transmit+receive error codes in same packet
 *
 * Proportional to HAL_StatusTypeDef.
 *
 * RX error codes shifted left by 4 (one hex char) relative to HAL_StatusTypeDef value.
 */
typedef enum
{
  LTC_SPI_OK       		= 0x00U, //0b00000000
  LTC_SPI_TX_ERROR  	= 0x02U, //0b00000010
  LTC_SPI_TX_BUSY   	= 0x04U, //0b00000100
  LTC_SPI_TX_TIMEOUT  	= 0x08U, //0b00001000
  LTC_SPI_RX_ERROR  	= 0x20U, //0b00100000
  LTC_SPI_RX_BUSY   	= 0x40U, //0b01000000
  LTC_SPI_RX_TIMEOUT  	= 0x80U	 //0b10000000
} LTC_SPI_StatusTypeDef;

/* Calculates  and returns the CRC15 */
uint16_t LTC_PEC15_Calc(uint8_t len, //Number of bytes that will be used to calculate a PEC
                    	uint8_t *data //Array of data that will be used to calculate a PEC
                   	   );

/* Set number of LTC6813/slave devices */
void LTC_Set_Num_Devices(uint8_t num);

/* Get number of LTC6813/slave devices */
uint8_t LTC_Get_Num_Devices(void);

/* Set number of series groups per LTC6813/slave */
void LTC_Set_Num_Series_Groups(uint8_t num);

/* Get number of series groups per LTC6813/slave */
uint8_t LTC_Get_Num_Series_Groups(void);

/* Pull nCS line to SPI1 HIGH */
void LTC_nCS_High(void);

/* Pull nCS line to SPI1 LOW */
void LTC_nCS_Low(void);

/* Wake LTC up from IDLE state into READY state */
LTC_SPI_StatusTypeDef LTC_Wakeup_Idle(void);

/* Read and store raw cell voltages at uint8_t pointer */
LTC_SPI_StatusTypeDef LTC_ReadRawCellVoltages(uint16_t *read_voltages);

#endif /* INC_LTC6813_H_ */
