#include "stm32f0xx.h"
#include "mh-z14a.h"
#include "usart.h"
#include "main.h"

#pragma clang diagnostic ignored "-Wmissing-noreturn"

void Configure_GPIO_LED(void);

void Configure_GPIO_Button(void);

uint32_t sysTicks = 0;


int main(void) {

    SysTick_Config(48000);
    Configure_GPIO_LED();
    Configure_GPIO_Button();
    Configure_USART();
    z14DisableAutoCalibration();

    LED1_TOGGLE();

#pragma ide diagnostic ignored "EndlessLoop"
    while (1) {
        LED1_TOGGLE();
        LED2_TOGGLE();

        printS("\n\rsystick: ");
        print16(sysTicks);

        z14GetCO2();

        uint32_t start = sysTicks;
        while (sysTicks - start < 1000) {
        }
    }
}

/**
  * @brief  This function :
             - Enables LEDs GPIO clock
             - Configures the Green LED pin on GPIO PA4
             - Configures the orange LED pin on GPIO PB8
  */
__INLINE void Configure_GPIO_LED(void) {
    // Enable the peripheral clock of GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // Select output mode (01) on PA4 and PB8
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER4)) | (GPIO_MODER_MODER4_0);
    GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODER8)) | (GPIO_MODER_MODER8_0);
}

/**
  * @brief  This function :
             - Enables GPIO clock
             - Configures the Push Button GPIO PA0
  */
__INLINE void Configure_GPIO_Button(void) {
    // Enable the peripheral clock of GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Select mode
    // Select input mode (00) on PA0
//    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER0));
}

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  */
void NMI_Handler(void) {
}

/**
  * @brief  This function handles Hard Fault exception.
  */
void HardFault_Handler(void) {
    // Go to infinite loop when Hard Fault exception occurs
    while (1) {
    }
}

/**
  * @brief  This function handles SysTick Handler.
  */
void SysTick_Handler(void) {
    sysTicks++;
}


/**
  * @brief  This function handles EXTI 0 1 interrupt request.
  */
void EXTI0_1_IRQHandler(void) {
    EXTI->PR |= 1U;
}

/**
 * @param delay in milliseconds
 */
void Delay(uint32_t delay) {
    uint32_t start = sysTicks;
    while (sysTicks - start < delay);
}

void _strcpy(uint8_t *dst, const uint8_t *src) {
    int i = 0;
    do {
        dst[i] = src[i];
    } while (src[i++] != 0);
}

void _memcpy(uint8_t *dst, const uint8_t *src, uint16_t size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

void _memset(uint8_t *dst, const uint8_t src, uint16_t size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src;
    }
}

#pragma clang diagnostic ignored "-Wunused-parameter"

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  */
void _Error_Handler(char *file, int line) {
    while (1) {
    }
}
