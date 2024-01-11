/* Inkluderingsdirektiv: */
#include "header.h"

/******************************************************************************
* Funktionen main utgör programmets start- och slutpunkt. Programmets globala
* variabler initieras via anrop av funktionen setup. En goto-sats används för
* att hålla igång programmet så länge matningsspänning tillförs. Resterande
* del av programmet är avbrottsgenererat, så hopp sker kontinuerligt till
* adressen döpt loop.
******************************************************************************/
int main(void)
{	
	init_serial();
	led1 = new_Led(9);
	button = new_Button(13);
	Button_enable_interrupt(&button);
	
	timer0 = new_Timer(TIMER0, 300);
	timer1 = new_Timer(TIMER1, 500);
	Timer_on(&timer1);
	
	while(true)
	{
		
	}
	
	return 0;
}

