#include "tm4c123gh6pm.h"
#define PD0 0x01
#define PD1 0x02
#define PD2 0x04
#define PD3 0x08

//Initialize Port D for LEDs and player button input
void PortD_Init(void){
	
	volatile unsigned long delay;
	
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOD;
	delay = SYSCTL_RCGCGPIO_R;
	
	//Initialize LEDs
	GPIO_PORTD_DIR_R |= (PD0 | PD1 | PD2);
	GPIO_PORTD_AFSEL_R &= ~(PD0 | PD1 | PD2);
	GPIO_PORTD_DEN_R |= (PD0 | PD1 | PD2);
	GPIO_PORTD_AMSEL_R &= ~(PD0 | PD1 | PD2);
	GPIO_PORTD_PCTL_R &= (~0x00000FFF);
	
	//Initialize Button
	GPIO_PORTD_DIR_R &= ~(PD3);
	GPIO_PORTD_AFSEL_R &= ~(PD3);
	GPIO_PORTD_DEN_R |= (PD3);
	GPIO_PORTD_AMSEL_R &= ~(PD3);
	GPIO_PORTD_PCTL_R &= (~0x0000F000);
}
