/*
 * ltc6813.c
 *
 *  Created on: Sep 26, 2023
 *      Author: vsaw3
 */

#include "ltc6813.h"

static const uint16_t LTC_CMD_RDCVA = 0x0004;
static const uint16_t LTC_CMD_RDCVB = 0x0006;
static const uint16_t LTC_CMD_RDCVC = 0x0008;
static const uint16_t LTC_CMD_RDCVD = 0x000A;
static const uint16_t LTC_CMD_RDCVE = 0x0009;
static const uint16_t LTC_CMD_RDCVF = 0x000B;

static const uint16_t LTC_CMD_RDCV[6] = {
										LTC_CMD_RDCVA,
										LTC_CMD_RDCVB,
										LTC_CMD_RDCVC,
										LTC_CMD_RDCVD,
										LTC_CMD_RDCVE,
										LTC_CMD_RDCVF
										};

static const uint8_t LTC_SPI_TX_BIT_OFFSET = 0; //Num bits to shift RX status code
static const uint8_t LTC_SPI_RX_BIT_OFFSET = 4; //Num bits to shift RX status code
static const uint8_t TX_REG_LEN = 6; // number of bytes in the register + 2 bytes for the PEC
static const uint8_t RX_REG_LEN = 8; // number of bytes in the register + 2 bytes for the PEC
static const uint8_t LTC_SERIES_GROUPS_PER_RDCV = 3; //Number of cell voltage groups per 8 byte register

static const unsigned int crc15Table[256] = {0x0,0xc599, 0xceab, 0xb32, 0xd8cf, 0x1d56, 0x1664, 0xd3fd, 0xf407, 0x319e, 0x3aac,  //!<precomputed CRC15 Table
    0xff35, 0x2cc8, 0xe951, 0xe263, 0x27fa, 0xad97, 0x680e, 0x633c, 0xa6a5, 0x7558, 0xb0c1,
    0xbbf3, 0x7e6a, 0x5990, 0x9c09, 0x973b, 0x52a2, 0x815f, 0x44c6, 0x4ff4, 0x8a6d, 0x5b2e,
    0x9eb7, 0x9585, 0x501c, 0x83e1, 0x4678, 0x4d4a, 0x88d3, 0xaf29, 0x6ab0, 0x6182, 0xa41b,
    0x77e6, 0xb27f, 0xb94d, 0x7cd4, 0xf6b9, 0x3320, 0x3812, 0xfd8b, 0x2e76, 0xebef, 0xe0dd,
    0x2544, 0x2be, 0xc727, 0xcc15, 0x98c, 0xda71, 0x1fe8, 0x14da, 0xd143, 0xf3c5, 0x365c,
    0x3d6e, 0xf8f7,0x2b0a, 0xee93, 0xe5a1, 0x2038, 0x7c2, 0xc25b, 0xc969, 0xcf0, 0xdf0d,
    0x1a94, 0x11a6, 0xd43f, 0x5e52, 0x9bcb, 0x90f9, 0x5560, 0x869d, 0x4304, 0x4836, 0x8daf,
    0xaa55, 0x6fcc, 0x64fe, 0xa167, 0x729a, 0xb703, 0xbc31, 0x79a8, 0xa8eb, 0x6d72, 0x6640,
    0xa3d9, 0x7024, 0xb5bd, 0xbe8f, 0x7b16, 0x5cec, 0x9975, 0x9247, 0x57de, 0x8423, 0x41ba,
    0x4a88, 0x8f11, 0x57c, 0xc0e5, 0xcbd7, 0xe4e, 0xddb3, 0x182a, 0x1318, 0xd681, 0xf17b,
    0x34e2, 0x3fd0, 0xfa49, 0x29b4, 0xec2d, 0xe71f, 0x2286, 0xa213, 0x678a, 0x6cb8, 0xa921,
    0x7adc, 0xbf45, 0xb477, 0x71ee, 0x5614, 0x938d, 0x98bf, 0x5d26, 0x8edb, 0x4b42, 0x4070,
    0x85e9, 0xf84, 0xca1d, 0xc12f, 0x4b6, 0xd74b, 0x12d2, 0x19e0, 0xdc79, 0xfb83, 0x3e1a, 0x3528,
    0xf0b1, 0x234c, 0xe6d5, 0xede7, 0x287e, 0xf93d, 0x3ca4, 0x3796, 0xf20f, 0x21f2, 0xe46b, 0xef59,
    0x2ac0, 0xd3a, 0xc8a3, 0xc391, 0x608, 0xd5f5, 0x106c, 0x1b5e, 0xdec7, 0x54aa, 0x9133, 0x9a01,
    0x5f98, 0x8c65, 0x49fc, 0x42ce, 0x8757, 0xa0ad, 0x6534, 0x6e06, 0xab9f, 0x7862, 0xbdfb, 0xb6c9,
    0x7350, 0x51d6, 0x944f, 0x9f7d, 0x5ae4, 0x8919, 0x4c80, 0x47b2, 0x822b, 0xa5d1, 0x6048, 0x6b7a,
    0xaee3, 0x7d1e, 0xb887, 0xb3b5, 0x762c, 0xfc41, 0x39d8, 0x32ea, 0xf773, 0x248e, 0xe117, 0xea25,
    0x2fbc, 0x846, 0xcddf, 0xc6ed, 0x374, 0xd089, 0x1510, 0x1e22, 0xdbbb, 0xaf8, 0xcf61, 0xc453,
    0x1ca, 0xd237, 0x17ae, 0x1c9c, 0xd905, 0xfeff, 0x3b66, 0x3054, 0xf5cd, 0x2630, 0xe3a9, 0xe89b,
    0x2d02, 0xa76f, 0x62f6, 0x69c4, 0xac5d, 0x7fa0, 0xba39, 0xb10b, 0x7492, 0x5368, 0x96f1, 0x9dc3,
    0x585a, 0x8ba7, 0x4e3e, 0x450c, 0x8095
                                            };

static uint8_t num_devices = 1; //Keep visibility within this file
static uint8_t num_series_groups = 12; //Number of series groups
static uint8_t cell_monitor_type = CELL_MON_LTC6813_1;
static uint16_t cell_hard_undervoltage	= 27000;
static uint16_t cell_hard_overvoltage	= 42000;

/* Set number of LTC6813/slave devices */
void LTC_Set_Num_Devices(uint8_t num)
{
	if (num) num_devices = num; //Non-zero
}

/* Get number of LTC6813/slave devices */
uint8_t LTC_Get_Num_Devices(void)
{
	return num_devices;
}

/* Set number of series groups per LTC6813/slave */
void LTC_Set_Num_Series_Groups(uint8_t num)
{
	if (num && (num <= 18)) num_series_groups = num; //Non-zero and 18 or less
}

/* Get number of series groups per LTC6813/slave */
uint8_t LTC_Get_Num_Series_Groups(void)
{
	return num_series_groups;
}

/* Pull nCS line to SPI1 HIGH */
void LTC_SPI_nCS_High(void)
{
	HAL_GPIO_WritePin(LTC_SPI_nCS_GPIO_Port, LTC_SPI_nCS_Pin, GPIO_PIN_SET); //Pull CS high
}

/* Pull nCS line to SPI1 LOW */
void LTC_SPI_nCS_Low(void)
{
	HAL_GPIO_WritePin(LTC_SPI_nCS_GPIO_Port, LTC_SPI_nCS_Pin, GPIO_PIN_RESET); //Pull CS high
}

/* Wrapper for HAL SPI Transmit */
LTC_SPI_StatusTypeDef LTC_SPI_Transmit(uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;
	LTC_SPI_StatusTypeDef hal_ret;

	LTC_SPI_nCS_Low();
	hal_ret = HAL_SPI_Transmit(&hspi1, pData, Size, Timeout);
	while( hspi1.State == HAL_SPI_STATE_BUSY );	//If busy, then wait																// Wait until transmission is complete
	LTC_SPI_nCS_High();
	if (hal_ret) { //Non-zero means error
		//Shift 1 by returned HAL_StatusTypeDef value to get LTC_SPI_StatusTypeDef equivalent
		ret |= (1 << (hal_ret+LTC_SPI_TX_BIT_OFFSET)); //TX error
	}

	return ret;
}

/* Wrapper for HAL SPI Receive */
LTC_SPI_StatusTypeDef LTC_SPI_Receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) {
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;
	LTC_SPI_StatusTypeDef hal_ret;

	LTC_SPI_nCS_Low();
	hal_ret = HAL_SPI_Receive(&hspi1, pData, Size, Timeout);
	while( hspi1.State == HAL_SPI_STATE_BUSY );	//If busy, then wait
	LTC_SPI_nCS_High();
	if (hal_ret) { //Non-zero means error
		//Shift 1 by returned HAL_StatusTypeDef value to get LTC_SPI_StatusTypeDef equivalent
		ret |= (1 << (hal_ret+LTC_SPI_RX_BIT_OFFSET)); //RX error
	}

	return ret;
}

/* Wrapper for HAL SPI TransmitReceive */
LTC_SPI_StatusTypeDef LTC_SPI_TransmitReceive(uint8_t *pData_Tx, uint16_t Size_Tx, uint8_t *pData_Rx, uint16_t Size_Rx, uint32_t Timeout) {
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;
	LTC_SPI_StatusTypeDef hal_ret;

	uint8_t *writeArray, *readArray;

	writeArray = malloc(sizeof(uint8_t)*(Size_Tx+Size_Rx));
	readArray = malloc(sizeof(uint8_t)*(Size_Tx+Size_Rx));

	memset(writeArray,0xFF, Size_Tx+Size_Rx);
	memcpy(writeArray, pData_Tx, Size_Tx);
	HAL_Delay(5); //Delay 5ms

	LTC_SPI_nCS_Low();
	hal_ret = HAL_SPI_TransmitReceive(&hspi1, writeArray, readArray, Size_Tx+Size_Rx, Timeout);
	while( hspi1.State == HAL_SPI_STATE_BUSY );	//If busy, then wait
	LTC_SPI_nCS_High();
	if (hal_ret) { //Non-zero means error
		//Shift 1 by returned HAL_StatusTypeDef value to get LTC_SPI_StatusTypeDef equivalent
		ret |= (1 << (hal_ret+LTC_SPI_TX_BIT_OFFSET)); //TX error
		ret |= (1 << (hal_ret+LTC_SPI_RX_BIT_OFFSET)); //RX error
	}

	memcpy(pData_Rx, readArray + Size_Tx, Size_Rx);
	HAL_Delay(5); //Delay 5ms

	free(writeArray);
	free(readArray);

	return ret;
}

/* Calculates  and returns the CRC15 */
uint16_t LTC_PEC15_Calc(uint8_t len, //Number of bytes that will be used to calculate a PEC
                    uint8_t *data //Array of data that will be used to calculate a PEC
                   )
{
	uint16_t remainder, addr;
	remainder = 16;	//Initialize the PEC to 0x10000

	for (uint8_t i = 0; i<len; i++) // loops for each byte in data array
	{
		addr = ((remainder>>7)^data[i])&0xff;//calculate PEC table address
		remainder = (remainder<<8)^crc15Table[addr];
	}

	return(remainder*2);//The CRC15 has a 0 in the LSB so the remainder must be multiplied by 2
}

/*
Generic function to write 68xx commands and write payload data.
Function calculates PEC for tx_cmd data and the data to be transmitted.
 */
void LTC_Write(uint8_t tx_cmd[2], //The command to be transmitted
			   uint8_t data[] // Payload Data
			  )
{
	const uint8_t CMD_LEN = 4+(8*LTC_Get_Num_Devices());
	uint8_t *cmd;
	uint16_t data_pec;
	uint16_t cmd_pec;
	uint8_t cmd_index;

	cmd = (uint8_t *)malloc(CMD_LEN*sizeof(uint8_t));
	cmd[0] = tx_cmd[0];
	cmd[1] = tx_cmd[1];
	cmd_pec = LTC_PEC15_Calc(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);

	cmd_index = 4;
	for (uint8_t current_ic = LTC_Get_Num_Devices(); current_ic > 0; current_ic--)               // Executes for each LTC681x, this loops starts with the last IC on the stack.
    {	                                                                            //The first configuration written is received by the last IC in the daisy chain
		for (uint8_t current_byte = 0; current_byte < TX_REG_LEN; current_byte++)
		{
			cmd[cmd_index] = data[((current_ic-1)*6)+current_byte];
			cmd_index = cmd_index + 1;
		}

		data_pec = LTC_PEC15_Calc(TX_REG_LEN, &data[(current_ic-1)*6]);    // Calculating the PEC for each ICs configuration register data
		cmd[cmd_index] = (uint8_t)(data_pec >> 8);
		cmd[cmd_index + 1] = (uint8_t)data_pec;
		cmd_index = cmd_index + 2;
	}

	LTC_SPI_Transmit((uint8_t *)cmd, CMD_LEN, 100);

	free(cmd);
}

/* Generic function to write 68xx commands and read data. Function calculated PEC for tx_cmd data */
int8_t LTC_Read(uint8_t tx_cmd[2], // The command to be transmitted
				uint8_t *rx_data // Data to be read
				)
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;
	LTC_SPI_StatusTypeDef hal_ret;

	const uint8_t ARR_SIZE_REG = LTC_Get_Num_Devices()*RX_REG_LEN;
	uint8_t cmd[4];
	uint8_t data[256];
	int8_t pec_error = 0;
	uint16_t cmd_pec;
	uint16_t data_pec;
	uint16_t received_pec;

	cmd[0] = tx_cmd[0];
	cmd[1] = tx_cmd[1];
	cmd_pec = LTC_PEC15_Calc(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);

	hal_ret = LTC_SPI_TransmitReceive((uint8_t *)cmd, 4, (uint8_t *)data, ARR_SIZE_REG, 100);
	//HAL_SPI_Receive(&hspi1, (uint8_t *)data, ARR_SIZE_REG, 100);

	for (uint8_t current_ic = 0; current_ic < num_devices; current_ic++) //Executes for each LTC681x in the daisy chain and packs the data
	{																//into the rx_data array as well as check the received data for any bit errors
		for (uint8_t current_byte = 0; current_byte < RX_REG_LEN; current_byte++)
		{
			rx_data[(current_ic*8)+current_byte] = data[current_byte + (current_ic*RX_REG_LEN)];
		}

		received_pec = (rx_data[(current_ic*8)+6]<<8) + rx_data[(current_ic*8)+7];
		data_pec = LTC_PEC15_Calc(6, &rx_data[current_ic*8]);

		if (received_pec != data_pec)
		{
		  pec_error = -1;
		}
	}

	return(pec_error);
}


/* Wake LTC up from IDLE state into READY state */
/* May not need this function */
LTC_SPI_StatusTypeDef LTC_Wakeup_Idle(void)
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;

	uint8_t hex_ff = 0xFF;

	ret |= LTC_SPI_Transmit(&hex_ff, 1, 100); //Send byte 0xFF to wake LTC up

	return ret;
}

/* Wake LTC up from SLEEP state into READY state */
void LTC_Wakeup_Sleep(void)
{
	HAL_Delay(1); //Delay 1ms, change to tick-based later
	LTC_SPI_nCS_Low(); //Pull CS low
	HAL_Delay(1); //Delay 1ms, change to tick-based later
	LTC_SPI_nCS_High(); //Pull CS high
	HAL_Delay(1); //Delay 1ms, change to tick-based later
}

int8_t LTC_DriverReadCFGR(uint8_t rx_config[][8])
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;
	LTC_SPI_StatusTypeDef hal_ret;

	const uint8_t ARR_SIZE_REG = LTC_Get_Num_Devices()*RX_REG_LEN;
	uint8_t cmd[4] = {0x00 , 0x02, 0x2b, 0x0a};
	uint8_t rx_data[ARR_SIZE_REG];
	int8_t pec_error = 0;
	uint16_t calc_pec;
	uint16_t data_pec;

//	LTC_SPI_nCS_Low();
	hal_ret = LTC_SPI_TransmitReceive((uint8_t *)cmd, 4, (uint8_t *)rx_data, ARR_SIZE_REG, 100);
//	if (hal_ret) { //Non-zero means error
//		//Shift 1 by returned HAL_StatusTypeDef value to get LTC_SPI_StatusTypeDef equivalent
//		ret |= (1 << (hal_ret+LTC_SPI_TX_BIT_OFFSET)); //TX error
//	}
//	hal_ret = HAL_SPI_Receive(&hspi1, (uint8_t *)rx_data, ARR_SIZE_REG, 100);
//	if (hal_ret) { //Non-zero means error
//		//Shift 1 by returned HAL_StatusTypeDef value to get LTC_SPI_StatusTypeDef equivalent
//		ret |= (1 << (hal_ret+LTC_SPI_RX_BIT_OFFSET)); //RX error
//	}
//	LTC_SPI_nCS_High();

	for (uint8_t current_ic = 0; current_ic < LTC_Get_Num_Devices(); current_ic++) { 			//executes for each LTC6804 in the daisy chain and packs the data into the r_config array as well as check the received Config data for any bit errors
		for (uint8_t current_byte = 0; current_byte < RX_REG_LEN; current_byte++)	{
			rx_config[current_ic][current_byte] = rx_data[current_byte + (current_ic*RX_REG_LEN)];
		}
		calc_pec = (rx_config[current_ic][6]<<8) + rx_config[current_ic][7];
		data_pec = LTC_PEC15_Calc(6, &rx_config[current_ic][0]);
		if (calc_pec != data_pec) {
			pec_error = -1;
		}
	}

	return pec_error;
}

LTC_SPI_StatusTypeDef LTC_DriverReadCFGRA(uint8_t num_devices_arg, uint8_t rx_buf[][8])
{
	return LTC_SPI_OK;
}

LTC_SPI_StatusTypeDef LTC_DriverReadCFGRB(uint8_t num_devices_arg, uint8_t rx_buf[][8])
{
	return LTC_SPI_OK;
}

LTC_SPI_StatusTypeDef LTC_DriverWriteCFGRA(void)
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;

	const uint8_t CMD_LEN = 4+(8*LTC_Get_Num_Devices());
	uint8_t *cmd;
	uint16_t cfg_pec;
	uint8_t cmd_index; //command counter
	uint8_t tx_cfg[LTC_Get_Num_Devices()][6];
	uint16_t cmd_pec;

	cmd = (uint8_t *)malloc(CMD_LEN*sizeof(uint8_t));
	cmd[0] = 0x00; // config register command
	cmd[1] = 0x01; // config register command
	cmd_pec = LTC_PEC15_Calc(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);
	cmd_index = 4;

	for (uint8_t current_ic = LTC_Get_Num_Devices(); current_ic > 0; current_ic--) { 			// executes for each LTC6804 in daisy chain, this loops starts with the last IC on the stack. The first configuration written is received by the last IC in the daisy chain
		for (uint8_t current_byte = 0; current_byte < TX_REG_LEN; current_byte++) { // executes for each of the 6 bytes in the CFGR register current_byte is the byte counter
			cmd[cmd_index] = tx_cfg[current_ic-1][current_byte]; 						//adding the config data to the array to be sent
			cmd_index = cmd_index + 1;
		}
		cfg_pec = LTC_PEC15_Calc(TX_REG_LEN, &tx_cfg[current_ic-1][0]);		// calculating the PEC for each ICs configuration register data
		cmd[cmd_index] = (uint8_t)(cfg_pec >> 8);
		cmd[cmd_index + 1] = (uint8_t)cfg_pec;
		cmd_index = cmd_index + 2;
	}

	LTC_Wakeup_Sleep();

	ret |= LTC_SPI_Transmit((uint8_t *)cmd, CMD_LEN, 100);

	free(cmd);
	return LTC_SPI_OK;
}

LTC_SPI_StatusTypeDef LTC_DriverWriteCFGRB(void)
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;

	const uint8_t CMD_LEN = 4+(8*LTC_Get_Num_Devices());
	uint8_t *cmd;
	uint16_t cfg_pec;
	uint8_t cmd_index; //command counter
	uint8_t tx_cfg[LTC_Get_Num_Devices()][6];
	uint16_t cmd_pec;

	cmd = (uint8_t *)malloc(CMD_LEN*sizeof(uint8_t));
	cmd[0] = 0x00; // config register B command
	cmd[1] = 0x24; // config register B command
	cmd_pec = LTC_PEC15_Calc(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);
	cmd_index = 4;

	for (uint8_t current_ic = LTC_Get_Num_Devices(); current_ic > 0; current_ic--) { 			// executes for each LTC6804 in daisy chain, this loops starts with the last IC on the stack. The first configuration written is received by the last IC in the daisy chain
		for (uint8_t current_byte = 0; current_byte < TX_REG_LEN; current_byte++) { // executes for each of the 6 bytes in the CFGR register current_byte is the byte counter
			cmd[cmd_index] = tx_cfg[current_ic-1][current_byte]; 						//adding the config data to the array to be sent
			cmd_index = cmd_index + 1;
		}
		cfg_pec = (uint16_t)LTC_PEC15_Calc(TX_REG_LEN, &tx_cfg[current_ic-1][0]);		// calculating the PEC for each ICs configuration register data
		cmd[cmd_index] = (uint8_t)(cfg_pec >> 8);
		cmd[cmd_index + 1] = (uint8_t)cfg_pec;
		cmd_index = cmd_index + 2;
	}

	LTC_Wakeup_Sleep();

	ret |= LTC_SPI_Transmit((uint8_t *)cmd, CMD_LEN, 100);

	free(cmd);
	return LTC_SPI_OK;
}

// LTC_ConfigTypeDef cs = configuration struct
// uint8_t nd			= number of devices/ltc
// uint8_t cpm			= series cells per module
// uint8_t tspm			= temp sensors per module
// uint8_t cmt			= cell monitor type
LTC_SPI_StatusTypeDef LTC_DriverInitCellMonitor(LTC_ConfigTypeDef cs, uint8_t cpm, uint8_t tspm, uint8_t cmt)
{
//	driverSWLTC6804ConfigStruct = configStruct;
//	driverSWLTC6804TotalNumberOfICs = totalNumberOfLTCs;
//	driverSWLTC6804MaxNoOfCellPerModule = noOfCellPerModule;
//	driverSWLTC6804MaxNoOfTempSensorPerModule = noOfTempSensorPerModule;

	uint8_t rxConfig [num_devices][8];
	uint8_t LTCScanCount = 0;
	int8_t returnPEC = -1;

	LTC_Wakeup_Sleep();

	//Attempt up to 5 times
	while((LTCScanCount < 5) && (returnPEC == -1)){
		returnPEC =	LTC_DriverReadCFGR(rxConfig);

		LTC_Wakeup_Sleep();

		LTC_DriverWriteCFGRA();

		if (cmt == CELL_MON_LTC6812_1 || cmt == CELL_MON_LTC6813_1){
			LTC_DriverWriteCFGRB();
		}

		LTC_Wakeup_Sleep();
		LTCScanCount++;
	}

	return LTC_SPI_OK;
}

/* Initialize cell configurations to LTC */
LTC_SPI_StatusTypeDef LTC_InitCellMonitor(void)
{
	LTC_ConfigTypeDef cfg_struct;
	cfg_struct.gpio1                    = true;	// Do not pull down this pin (false = pull down)
	cfg_struct.gpio2                    = true;
	cfg_struct.gpio3                    = true;
	cfg_struct.gpio4                    = true;
	cfg_struct.gpio5                    = true;
	cfg_struct.gpio6                    = true;
	cfg_struct.gpio7                    = true;
	cfg_struct.gpio8                    = true;
	cfg_struct.gpio9                    = true;
	cfg_struct.ref_on		            = true;
	cfg_struct.adc_option               = true;
	cfg_struct.num_cells                = num_series_groups;
	cfg_struct.discharge_enable_mask    = 0x00000000;
	cfg_struct.discharge_timeout        = 0;
	cfg_struct.cell_undervoltage_limit  = cell_hard_undervoltage;
	cfg_struct.cell_overvoltage_limit   = cell_hard_overvoltage;
	LTC_DriverInitCellMonitor(cfg_struct, 18, 12, cell_monitor_type);

	// Safety signal is managed by the controller, it is configured as open drain and will be kept low by. watchdog will make the output to be released.
	//driverHWSwitchesSetSwitchState(SWITCH_SAFETY_OUTPUT,SWITCH_RESET);

	//modPowerElectronicsCellMonitorsTypeActive = (configCellMonitorICTypeEnum)modPowerElectronicsGeneralConfigHandle->cellMonitorType;

	return LTC_SPI_OK;
}

/* Clear cell voltage registers for next measurement */
LTC_SPI_StatusTypeDef LTC_WriteClearCellVoltageRegisters(void)
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;

	uint8_t cmd[4];
	uint16_t cmd_pec;

	cmd[0] = 0x07;
	cmd[1] = 0x11;
	cmd_pec = LTC_PEC15_Calc(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec );

	LTC_Wakeup_Sleep();

	ret |= LTC_SPI_Transmit((uint8_t *)cmd, 4, 100);

	return ret;
}

/* Start next measurement of cell voltages */
LTC_SPI_StatusTypeDef LTC_WriteStartCellVoltageConversion(uint8_t adc_mode, uint8_t discharge_permit, uint8_t ch_to_conv)
{
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;

	uint8_t cmd[4];
	uint16_t cmd_pec;
	uint8_t adcv[2]; //!< Cell Voltage conversion command.

	adcv[0] = ((adc_mode & 0x02) >> 1) + 0x02;
	adcv[1] = ((adc_mode & 0x01) << 7) + 0x60 + (discharge_permit<<4) + ch_to_conv;

	cmd[0] = adcv[0];
	cmd[1] = adcv[1];
	cmd_pec = LTC_PEC15_Calc(2, adcv);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);

	LTC_Wakeup_Sleep();

	ret |= LTC_SPI_Transmit((uint8_t *)cmd, 4, 100);

	return ret;
}

/* Read and store raw cell voltages at uint8_t 2d pointer */
LTC_SPI_StatusTypeDef LTC_ReadRawCellVoltages(uint16_t *read_voltages) {
	LTC_SPI_StatusTypeDef ret = LTC_SPI_OK;
	LTC_SPI_StatusTypeDef hal_ret;
	const uint8_t ARR_SIZE_REG = LTC_Get_Num_Devices()*RX_REG_LEN;
	uint8_t read_voltages_reg[ARR_SIZE_REG];

	// CMD0 write: CC[8:10]
	// CMD1 write: CC[0:7]
	// Page 59 LTC6813 datasheet
	for (uint8_t i = 0; i < (LTC_Get_Num_Series_Groups()/LTC_SERIES_GROUPS_PER_RDCV); i++) {
		uint8_t cmd[4];
		uint16_t cmd_pec;

		cmd[0] = (0xFF & (LTC_CMD_RDCV[i] >> 8)); //RDCVA
		cmd[1] = (0xFF & (LTC_CMD_RDCV[i])); //RDCVA
		cmd_pec = LTC_PEC15_Calc(2, cmd);
		cmd[2] = (uint8_t)(cmd_pec >> 8);
		cmd[3] = (uint8_t)(cmd_pec);

		LTC_Wakeup_Sleep(); //Wake LTC up

		LTC_SPI_nCS_Low(); //Pull CS low
		//hal_ret = LTC_SPI_TransmitReceive((uint8_t *)cmd, 4, (uint8_t *)read_voltages_reg, ARR_SIZE_REG, 100);
		hal_ret = HAL_SPI_Transmit(&hspi1, (uint8_t *)cmd, 4, 100);
		if (hal_ret) { //Non-zero means error
			//Shift 1 by returned HAL_StatusTypeDef value to get LTC_SPI_StatusTypeDef equivalent
			ret |= (1 << (hal_ret+LTC_SPI_TX_BIT_OFFSET)); //TX error
		}
		hal_ret = HAL_SPI_Receive(&hspi1, (uint8_t *)read_voltages_reg, ARR_SIZE_REG, 100);
		if (hal_ret) { //Non-zero means error
			//Shift 1 by returned HAL_StatusTypeDef value to get LTC_SPI_StatusTypeDef equivalent
			ret |= (1 << (hal_ret+LTC_SPI_RX_BIT_OFFSET)); //RX error
		}
		LTC_SPI_nCS_High(); //Pull CS high

		for (uint8_t j = 0; j < LTC_Get_Num_Devices(); j++) {
			memcpy(read_voltages+(i*LTC_SERIES_GROUPS_PER_RDCV)+(j*LTC_Get_Num_Series_Groups()), read_voltages_reg+(j*RX_REG_LEN), sizeof(read_voltages_reg)-(2*sizeof(read_voltages_reg[0])) );
			HAL_Delay(5); //Delay 5ms to allow memcpy completion
		}

	}

	return ret;
}
