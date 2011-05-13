# atmega-scheduler

`atmega-scheduler` is an Arduino/Avr compatible 24-hour scheduler with 1 minute resolution.

## Description

With this scheduler you can run any function at any time, every day. It uses Timer1 available on most micros.

- Configuring the scheduler is done by defined constants in header file `atmega-scheduler.h`. By default it's
preconfigured for 16Mhz, like the Arduino:

	- Set the Timer1 prescaler
	
			#define SCHEDULER_PRESCALER 5
			
	- Set a fixed number of ticks for register OCR1A
	
			#define SCHEDULER_TICKS 62500U
		
	- Set number of seconds that represents OCR1A top value with current prescaler
	
			#define SCHEDULER_PERIOD 4

## Usage

- Initializing the scheduler:

		void scheduler_init(uint8_t hour, uint8_t minutes)
		void scheduler_set(uint8_t hour, uint8_t minutes)

	- `scheduler_init` is the initialization function that resets the internal array of tasks and sets initial time.
	You call this function only once.
	- `scheduler_set` allows you to set scheduler hours and minutes at any time (using wired buttons for example).
	
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

## Running it in Arduino

Just rename `atmega-scheduler.c` to `atmega-scheduler.cpp` and install it as a normal library.

## Atmel Model Support

It should work with a long range of devices, for example:

- atmega48, 88, 168, 328
- atmega164, 324, 644, 1284
- atmega640, 1280, 1281, 2560, 2561
- atmega325, 645
- ...
