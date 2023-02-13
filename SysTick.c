#include "tm4c123gh6pm.h"
#include "ADCFunctions.h"

#define PD3 0x08

void (*ButtonTask)(void);   // user function

void SysTick_Init(void(*task)(void),unsigned long frequency){
	ButtonTask = task;
	
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 80000000/frequency-1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000;
	NVIC_ST_CTRL_R = 0x07;
}


//signed long ADCDiff = 0;		FOR DEBUGGING ONLY!

unsigned long data = 0;
unsigned int counter = 0;
signed long ADCdata1 = 0;
signed long ADCdata2 = 0;
signed int playerAdd = 0;

//Takes an ADC sample, busy-wait until it's done, return value read.
unsigned int previous = 0;

void SysTick_Handler(void){
	
	//Detects slide pot inputs
	ADCdata1 = ADC_Sample();
	
	//FOR DEBUGGING ONLY!
	//ADCDiff = (ADCdata2 - ADCdata1);	Shows the difference between the two ADC measurements (debugging purposes)
	
	if((ADCdata2 - ADCdata1) > 0 && (ADCdata2 - ADCdata1) > 3){
		playerAdd = 3;
	}
	
	else if((ADCdata2 - ADCdata1) < 0 && (ADCdata2 - ADCdata1) < -3){
		playerAdd = -3;
	}
		
	else{
		playerAdd = 0;
	}
	
	ADCdata2 = ADCdata1;
	
	
	//Detects button inputs
	data = (GPIO_PORTD_DATA_R & PD3);
	
	if(data == PD3 && previous == 0){
		(*ButtonTask)();
		previous = 1;
	}
	
	else if(data == 0){
		previous = 0;
	}
	
	else{}

}
