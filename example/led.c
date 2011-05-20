#include <avr/io.h>
#include "atmega-scheduler.h"

void led_on() {
	PORTB = 0xff;
}

void led_off() {
	PORTB = 0;
}

void main() {
	// set PORTB as output
	DDRB = 0xff;
	PORTB = 0;
	
	// In this example you will see that PORTB turns ON after 1 minute
	// and will turn OFF after 2 minutes, repeating it every day.
	
	// You can synchronize your device by setting scheduler init time
	// to 10:00AM (for example) and then hitting your device's reset at 10:00AM.
	//
	// By wiring some 7-segment displays and some push buttons, you can set
	// the time using `scheduler_set` as a normal watch.
	
	// initialize scheduler time as 10:30
	scheduler_init(10, 30);
	
	// turn led on at 10:31
	task_add(10, 31, led_on);
	
	// turn led off at 10:32
	task_add(10, 32, led_off);
	
	// enable global interrupts
	sei();
	
	while(1) {
		// your code goes here
	}
}
