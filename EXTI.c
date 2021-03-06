#include "EXTI.h"
#include "LED.h"

// Joystick Center = PA0

void EXTI_Init(void){
	// GPIO Configuration
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOAEN;
	
	// GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOA->MODER &= ~3U << 0;

	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)	
	// We do not need to pull down PA.0 because it has already been pulled down externally. Take a look at the schematics.
	GPIOA->PUPDR &= ~3U << 0;
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
	
	// EXIT Interrupt Enable
	NVIC_EnableIRQ(EXTI0_IRQn); 
  NVIC_SetPriority(EXTI0_IRQn, 0);  
	
	// Connect External Line to the GPI
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;     // SYSCFG external interrupt configuration registers
	SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI0_PA; 
	
	// Interrupt Mask Register
	EXTI->IMR1   |= EXTI_IMR1_IM0;     // 0 = marked, 1 = not masked (i.e., enabled)
	
	// Software interrupt event register
	// EXTI->SWIER1 |= EXTI_SWIER1_SWI0;
	
	// Rising trigger selection
	// EXTI->RTSR1 |= EXTI_RTSR1_RT0;  // 0 = trigger disabled, 1 = trigger enabled
	EXTI->FTSR1 |= EXTI_FTSR1_FT0;     // 0 = trigger disabled, 1 = trigger enabled
}

void EXTI0_IRQHandler(void) {  
	if ((EXTI->PR1 & EXTI_PR1_PIF0) == EXTI_PR1_PIF0) {
		// cleared by writing a 1
		EXTI->PR1 |= EXTI_PR1_PIF0;
		//Red_LED_Toggle();
		Green_LED_Toggle();
	}
}
