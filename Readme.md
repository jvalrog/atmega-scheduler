# atmega-scheduler

`atmega-scheduler` is an Arduino/Avr compatible 24-hour scheduler with 1 minute resolution.

## Description

With this scheduler you can run any function at any time, every day. It uses Timer1 available on most micros.

- Configuring the scheduler is done by predefined constants in header file `atmega-scheduler.h`. If you want to
use other frequencies, you need to change those values in order to get 1 second resolution. By default it's
preconfigured for 16Mhz, like the Arduino:

	- Set the Timer1 prescaler
	
			#define SCHEDULER_PRESCALER 5
			
	- Set a number of ticks on register OCR1A
	
			#define SCHEDULER_TICKS 15625U
		
## Usage

- Initializing the scheduler:

		void scheduler_init(uint8_t hour, uint8_t minutes)
		void scheduler_set(uint8_t hour, uint8_t minutes)

	- `scheduler_init` is the initialization function that resets the internal array of tasks and sets initial time.
	You call this function only once.
	- `scheduler_set` allows you to set scheduler hours and minutes at any time.
	
- Managing tasks:

		int16_t task_add(uint8_t hour, uint8_t minutes, void (*f)())
		void task_del(int16_t index)
		void task_set(int16_t index, uint8_t hour, uint8_t minutes)

	- With `task_add` you add tasks to the scheduler. Set the hour, minutes and function to execute. Return value
	is the task index for later usage.
	- With `task_del` you delete a task by using its index.
	- With `task_set` you set a new time for the task. Tasks can re-schedule using this method if they know their own index.

# Sample Code

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

## Running it in Arduino

Just rename `atmega-scheduler.c` to `atmega-scheduler.cpp` and install it as a normal library.

## Atmel Model Support

It should work with a long range of devices, for example:

- atmega48, 88, 168, 328
- atmega164, 324, 644, 1284
- atmega640, 1280, 1281, 2560, 2561
- atmega325, 645
- ...
