/*these directories can be found when downloading Code Composer Studio (CCS)
@ https://www.ti.com/tool/download/CCSTUDIO , run ccs_setup_12.4.0.00007.exe, select SimpleLinkTM MSP432TM low power + performance MCUs.

You may also need to download the SDK installer Win_simplelink_msp432p4_sdk_3_40_01_02.exe
*/
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

// creating a function that sends battery data over UART
void sendBatteryData(uint16_t voltage);

int main(void)
{
    MAP_WDT_A_holdTimer(); // Halting the Watchdog

    // Digitally Controlled Oscillator (DCO)
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12); // set DCO to 12MHz

    // Configure UART pins and module
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    const eUSCI_UART_ConfigV1 uartConfig =
    {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                     // BRDIV = 78
        2,                                      // UCxBRF = 2
        0,                                      // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                   // 8 bit data length
    };

    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);
    MAP_UART_enableModule(EUSCI_A0_BASE);

    // mock data being sent to the microcontroller to test the function
    uint16_t batteryVs[] = {0x2522, 0x3252, 0x4554, 0x8522, 0x5225};
    size_t numOfV = sizeof(batteryVs) / sizeof(batteryVs[0]);

    // sends each voltage in the array
    size_t i;
    for (i = 0; i < numOfV; ++i)
    {
        sendBatteryData(batteryVs[i]);
    }

    while (1)
    {
        // echo has received the data
        uint8_t receivedData = MAP_UART_receiveData(EUSCI_A0_BASE);
        MAP_UART_transmitData(EUSCI_A0_BASE, receivedData);
    }
}

void sendBatteryData(uint16_t voltage)
{
    // calculate voltage 
    float voltageInVolts = voltage * 0.0001;

    // send voltage in format: "3.4615\r\n"
    char voltageBuffer[10];
    snprintf(voltageBuffer, sizeof(voltageBuffer), "%.4f V", voltageInVolts);

    // sends the v data
    int i;
    for (i = 0; voltageBuffer[i] != '\0'; ++i)
    {
        MAP_UART_transmitData(EUSCI_A0_BASE, voltageBuffer[i]);
    }

    // Will send the line ending "\r\n"
    MAP_UART_transmitData(EUSCI_A0_BASE, '\r');
    MAP_UART_transmitData(EUSCI_A0_BASE, '\n');
}
