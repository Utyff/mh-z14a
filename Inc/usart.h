#ifndef F0_USART_H
#define F0_USART_H

#define UART1_RX_SIZE 32

extern uint8_t uart1CountTX;
extern uint8_t uart1Size;
extern uint8_t uart1TX[32];
extern uint8_t uart1CountRX;
extern uint8_t uart1RX[UART1_RX_SIZE];

void uart1Send(uint8_t *in, uint8_t size);

void printS(const char *);

void print8(uint8_t val);

void print16(uint16_t val);

void Configure_USART();

#endif //F0_USART_H
