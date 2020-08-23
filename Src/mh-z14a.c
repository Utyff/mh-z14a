#include "stm32f0xx.h"
#include "mh-z14a.h"
#include "usart.h"
#include "main.h"

uint8_t z14CmdGetCO2[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
uint16_t z14_co2;

void z14DisableAutoCalibration() {
    z14CmdGetCO2[2] = 0x79;
    z14CmdGetCO2[3] = 0x0;
    uart1Send(z14CmdGetCO2, 9);
    z14CmdGetCO2[2] = 0x86;
}

void z14GetCO2() {
    _memset(uart1RX, 0, 9);
    uart1CountRX = 0;
    uart1Send(z14CmdGetCO2, 9);

    while (uart1CountRX != 9);

    uint8_t crc = 0;
    for (int i = 1; i < 8; i++) crc += uart1RX[i];
    crc = 0xFF - crc + 1;

    if (uart1RX[0] == 0xFF && uart1RX[1] == 0x86 && uart1RX[8] == crc) {
        z14_co2 = (uart1RX[2] << 8u) + uart1RX[3];
        printS("; CO2: ");
        print16(z14_co2);
    } else {
        printS("Z14 CRC error: ");
        print16(crc);
        printS(" / ");
        print8(uart1RX[0]);
        printS(" ");
        print8(uart1RX[1]);
        printS(" ");
        print8(uart1RX[2]);
        printS(" ");
        print8(uart1RX[3]);
        printS(" ");
        print8(uart1RX[4]);
        printS(" ");
        print8(uart1RX[5]);
        printS(" ");
        print8(uart1RX[6]);
        printS(" ");
        print8(uart1RX[7]);
        printS(" ");
        print8(uart1RX[8]);
        printS("\n\r");
    }
}
