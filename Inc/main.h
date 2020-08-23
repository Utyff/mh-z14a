#ifndef F0_MAIN_H
#define F0_MAIN_H

#include "stm32f0xx.h"

#define LED1_Pin GPIO_IDR_4
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_IDR_8
#define LED2_GPIO_Port GPIOB

#define  LED1_TOGGLE() LED1_GPIO_Port->ODR ^= LED1_Pin
#define  LED2_TOGGLE() LED2_GPIO_Port->ODR ^= LED2_Pin

// operation timeout milliseconds
#define Timeout 5

extern uint32_t sysTicks;
extern uint32_t Tickstart;

void _strcpy(uint8_t *dst, const uint8_t *src);
void _memcpy(uint8_t *dst, const uint8_t *src, uint16_t size);
void _memset(uint8_t *dst, const uint8_t src, uint16_t size);

void _Error_Handler(char *, int);

void Delay(uint32_t);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

#endif //F0_MAIN_H
