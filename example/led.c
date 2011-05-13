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
	
	// initialize scheduler time as 9:59
	scheduler_init(9, 59);
	
	// turn led on at 10:00 every day
	task_add(10, 00, led_on);
	
	// turn led off at 10:01 every day
	task_add(10, 01, led_off);
	
	// enable global interrupts
	sei();
	
	while(1) {
		// do nothing
	}
}
