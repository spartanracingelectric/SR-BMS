/*
 * ltc6813.h
 *
 *  Created on: Sep 26, 2023
 *      Author: vsaw3
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
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

typedef struct {
	bool gpio1;						// Read/Write open drain GPIO1
	bool gpio2;						// Read/Write open drain GPIO2
	bool gpio3;						// Read/Write open drain GPIO3
	bool gpio4;						// Read/Write open drain GPIO4
	bool gpio5;						// Read/Write open drain GPIO5
	bool gpio6;						// Read/Write open drain GPIO6
	bool gpio7;						// Read/Write open drain GPIO7
	bool gpio8;						// Read/Write open drain GPIO8
	bool gpio9;						// Read/Write open drain GPIO9
	bool ref_on;					// Reference ON
	bool sw_timer_flag;				// Read software timer pin
	bool adc_option;				// ADC Option register, configuration of over sampling ratio
	uint8_t num_cells;				// Number of cells to monitor (that can cause interrupt)
	uint32_t discharge_enable_mask;	// 1=EnableDischarge, 0=DisableDischarge
	uint8_t discharge_timeout;		// Discharge timeout limit
	float cell_undervoltage_limit;	// Undervoltage level, interrupt if exceeded
	float cell_overvoltage_limit;	// Overvoltage limit, interrupt if exceeded
} LTC_ConfigTypeDef;

typedef enum {
	CELL_MON_NONE = 0,
	CELL_MON_LTC6811_1,
	CELL_MON_LTC6812_1,
	CELL_MON_LTC6813_1
} LTC_CellMonitorTypeEnum;

typedef enum {
	 /*
	  |MD| Dec  | ADC Conversion Model	|
	  |--|------|-----------------------|
	  |01| 1    | Fast 			   	  	|
	  |10| 2    | Normal				|
	  |11| 3    | Filtered 		   	  	|
	*/
	MD_FAST = 1,
	MD_NORMAL,	//2
	MD_FILTERED	//3
} LTC_CellVoltageAdcModeTypeEnum;

typedef enum {
	 /*!****************************************************
	  \brief Controls if discharging transistors are enabled
	  or disabled during cell conversions.

	 |DCP | Discharge Permitted During conversion	|
	 |----|-----------------------------------------|
	 |0   | No - discharge is not permitted			|
	 |1   | Yes - discharge is permitted			|

	********************************************************/

	DCP_DISABLED = 0,
	DCP_ENABLED
} LTC_CellVoltageAdcDischargePermitTypeEnum;

typedef enum {
	 /*!
	 |CH | Dec  | Channels to convert |
	 |---|------|---------------------|
	 |000| 0    | All Cells  		  |
	 |001| 1    | Cell 1 and Cell 7   |
	 |010| 2    | Cell 2 and Cell 8   |
	 |011| 3    | Cell 3 and Cell 9   |
	 |100| 4    | Cell 4 and Cell 10  |
	 |101| 5    | Cell 5 and Cell 11  |
	 |110| 6    | Cell 6 and Cell 12  |
	*/

	CELL_CH_ALL = 0,
	CELL_CH_1_7,	//1
	CELL_CH_2_8,	//2
	CELL_CH_3_9,	//3
	CELL_CH_4_10,	//4
	CELL_CH_5_11,	//5
	CELL_CH_6_12	//6
} LTC_CellVoltageAdcChannelTypeEnum;

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
void LTC_SPI_nCS_High(void);

/* Pull nCS line to SPI1 LOW */
void LTC_SPI_nCS_Low(void);

/* Wrapper for HAL SPI Transmit */
LTC_SPI_StatusTypeDef LTC_SPI_Transmit(uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* Wrapper for HAL SPI Receive */
LTC_SPI_StatusTypeDef LTC_SPI_Receive(uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* Wrapper for HAL SPI TransmitReceive */
LTC_SPI_StatusTypeDef LTC_SPI_TransmitReceive(uint8_t *pData_Tx, uint16_t Size_Tx, uint8_t *pData_Rx, uint16_t Size_Rx, uint32_t Timeout);

/* Wake LTC up from IDLE state into READY state */
LTC_SPI_StatusTypeDef LTC_Wakeup_Idle(void);

/* Initialize cell configurations to LTC */
LTC_SPI_StatusTypeDef LTC_InitCellMonitor(void);

/* Clear cell voltage registers for next measurement */
LTC_SPI_StatusTypeDef LTC_WriteClearCellVoltageRegisters(void);

/* Start next measurement of cell voltages */
LTC_SPI_StatusTypeDef LTC_WriteStartCellVoltageConversion(uint8_t adc_mode, uint8_t discharge_permit, uint8_t ch_to_conv);

/* Read and store raw cell voltages at uint8_t pointer */
LTC_SPI_StatusTypeDef LTC_ReadRawCellVoltages(uint16_t *read_voltages);

#endif /* INC_LTC6813_H_ */
