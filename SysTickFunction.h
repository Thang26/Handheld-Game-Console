//SysTick Function Declarations

// ***************** ADC_Init ****************
// Initialize SysTick to detect slide pot movements and button inputs
// Inputs: PBulletActivate function and rate of data collection (30Hz)
// Outputs: None
void SysTick_Init(void(*task)(void),unsigned long frequency);
