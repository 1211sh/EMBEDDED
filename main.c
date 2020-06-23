#include "stm32l476xx.h"
#include "SysClock.h"
#include "EXTI.h"
#include "LED.h"

// Push joystick center and toggle RED LED
int main(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	Red_LED_Toggle();
	EXTI_Init();
	while(1);
}

