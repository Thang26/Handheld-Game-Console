#include "tm4c123gh6pm.h"

void ADC_Init(void){
	
	SYSCTL_RCGCADC_R |= 0x0001; 	//Enable ADC clock bit 0 to choose ADC0
	
	//PortE (PE4) ADC Initialization
	SYSCTL_RCGCGPIO_R |= 0x10;		//Activate clock for Port E
	while((SYSCTL_PRGPIO_R&0x10) != 0x10){}
		
	GPIO_PORTE_DIR_R &= ~0x10;		//PE4 is input
	GPIO_PORTE_AFSEL_R |= 0x10;		//PE4 has alternate function
	GPIO_PORTE_DEN_R &= ~0x10;		//PE4 is not digital
	GPIO_PORTE_AMSEL_R |= 0x10;		//PE4 is analog
		
	while((SYSCTL_PRADC_R & 0x0001) != 0x0001){}
	
	ADC0_PC_R &= ~0xF;
	ADC0_PC_R |= 0x1;					//Specifies max sampl. rate of ADC to be 125kHz
	ADC0_SSPRI_R |= 0x0123;		//Specifies seq. 3 to be of highest priority
	ADC0_ACTSS_R &= ~0x0008;	//Disables seq. 3
	ADC0_EMUX_R	&= ~0xF000;		//Configure trigger event for seq. 3
	ADC0_SSMUX3_R &= ~0x000F;
	ADC0_SSMUX3_R |= 0x9;			//Configure ADC to be channel 9, which is in PE4
	ADC0_SSCTL3_R &= ~0x0009;
	ADC0_SSCTL3_R |= 0x0006;	//No TS0 & D0, Yes IE0 & END0
	ADC0_IM_R &= ~0x0008;			//Disables IRQ for seq. 3
	ADC0_SAC_R = 7;						//64 point averaging
	ADC0_ACTSS_R |= 0x0008;		//Enables seq. 3
	
}

//Samples ADC Seq.3, returns value sampled
unsigned long ADC_Sample(void){
	
	unsigned long result;
	
	ADC0_PSSI_R = 0x0008;								//Writing a 1 initiates seq. 3
	
	while((ADC0_RIS_R&0x08) == 0){}			//RIS indicates if a seq. has completed its task
	
	result = (ADC0_SSFIFO3_R & 0xFFF);	//read data, SSFIFO3 is where the data from the seq. is stored
	
	ADC0_ISC_R = 0x0008;								//Clears flag, acknowledge
		
	return result;
	
}
