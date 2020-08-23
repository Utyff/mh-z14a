#include "stm32f0xx.h"
#include "timer.h"

//void ConfigureGPIO() {
//    /* (1) Enable the peripheral clock of GPIOC */
//    /* (2) Select output mode (01) on GPIOC pin 8 and 9 */
//    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; /* (1) */
//    GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER8|GPIO_MODER_MODER9)) \
//               | (GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0); /* (2) */
//}

void initTimer() {
    /* (1) Enable the peripheral clock of Timer x */
    /* (2) Enable the peripheral clock of GPIOA */
    /* (3) Select alternate function mode on GPIOA pin 9 */
    /* (4) Select AF2 on PA9 in AFRH for TIM1_CH2 */

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; /* (1) */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (2) */
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9)) | (GPIO_MODER_MODER9_1); /* (3) */
    GPIOA->AFR[1] |= (0x02u  << (2u * 4)); /* (4) */

    /* (1) Set prescaler to 47, so APBCLK/48 i.e 1MHz */
    /* (2) Set ARR = 8, as timer clock is 1MHz the period is 9 us */
    /* (3) Set CCRx = 4, , the signal will be high during 4 us */
    /* (4) Select PWM mode 1 on OC1  (OC1M = 110),
           enable preload register on OC1 (OC1PE = 1) */
    /* (5) Select active high polarity on OC1 (CC1P = 0, reset value),
           enable the output on OC1 (CC1E = 1)*/
    /* (6) Enable output (MOE = 1)*/
    /* (7) Enable counter (CEN = 1)
           select edge aligned mode (CMS = 00, reset value)
           select direction as upcounter (DIR = 0, reset value) */
    /* (8) Force update generation (UG = 1) */

    TIM1->PSC = 47; /* (1) */
    TIM1->ARR = 8; /* (2) */
    TIM1->CCR2 = 4; /* (3) */
    TIM1->CCMR2 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE; /* (4) */
    TIM1->CCER |= TIM_CCER_CC2E; /* (5) */
    TIM1->BDTR |= TIM_BDTR_MOE; /* (6) */
    TIM1->CR1 |= TIM_CR1_CEN; /* (7) */
    TIM1->EGR |= TIM_EGR_UG; /* (8) */
}


void initTimer2() {
    /* (1) Enable the peripheral clock of Timer x */
    /* (2) Enable the peripheral clock of GPIOA */
    /* (3) Select alternate function mode on GPIOA pin 0 */
    /* (4) Select AF2 on PA0 in AFRH for TIM1_CH1 */

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; /* (1) */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (2) */
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER0)) | (GPIO_MODER_MODER0_1); /* (3) */
    GPIOA->AFR[0] |= 0x02; /* (4) */

    /* (1) Set prescaler to 47, so APBCLK/48 i.e 1MHz */
    /* (2) Set ARR = 8, as timer clock is 1MHz the period is 9 us */
    /* (3) Set CCRx = 4, , the signal will be high during 4 us */
    /* (4) Select PWM mode 1 on OC1  (OC1M = 110),
           enable preload register on OC1 (OC1PE = 1) */
    /* (5) Select active high polarity on OC1 (CC1P = 0, reset value),
           enable the output on OC1 (CC1E = 1)*/
    /* (6) Enable output (MOE = 1)*/
    /* (7) Enable counter (CEN = 1)
           select edge aligned mode (CMS = 00, reset value)
           select direction as upcounter (DIR = 0, reset value) */
    /* (8) Force update generation (UG = 1) */

    TIM2->PSC = 0; /* (1) */
    TIM2->ARR = 1; /* (2) */
    TIM2->CCR1 = 1; /* (3) */
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; /* (4) */
    TIM2->CCER |= TIM_CCER_CC1E; /* (5) */
    TIM2->BDTR |= TIM_BDTR_MOE; /* (6) */
    TIM2->CR1 |= TIM_CR1_CEN; /* (7) */
    TIM2->EGR |= TIM_EGR_UG; /* (8) */
}
