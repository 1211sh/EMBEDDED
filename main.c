#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];

int main(void){
	char rxByte;
	int a, n, i;
	float b;
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
	
	
		
	while (1){
//		n = sprintf((char *)buffer, "a = %d\t", a);
//		n += sprintf((char *)buffer + n, "b = %f\r\n", b);
//		USART_Write(USART2, buffer, n);		
//		a = a + 1;
//		b = (float)a/100;
//		for (i = 0; i < 8000000; i++); // Delay
//		Red_LED_Toggle();
		
		printf("Give Red LED control input (Y = On, N = off):\r\n");
		scanf ("%c", &rxByte);
		if (rxByte == 'N' || rxByte == 'n'){
			Red_LED_Off();
			printf("LED is Off\r\n\r\n");
		}
		else if (rxByte == 'Y' || rxByte == 'y'){
			Red_LED_On();
			printf("LED is On\r\n\r\n");
		}
	}
}

