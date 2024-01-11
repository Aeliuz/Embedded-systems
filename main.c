/* Inkluderingsdirektiv: */
#include "header.h"

/******************************************************************************
* Funktionen main utg�r programmets start- och slutpunkt. Programmets globala
* variabler initieras via anrop av funktionen setup. En goto-sats anv�nds f�r
* att h�lla ig�ng programmet s� l�nge matningssp�nning tillf�rs. Resterande
* del av programmet �r avbrottsgenererat, s� hopp sker kontinuerligt till
* adressen d�pt loop.
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

