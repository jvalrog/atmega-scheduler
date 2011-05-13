//      atmega-scheduler.h
//      
//      Copyright 2011 Javier Valencia <javiervalencia80@gmail.com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      

#ifndef atmega_scheduler_h
#define atmega_scheduler_h

#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>

// Change those parameters for frequencies different to 16Mhz

// timer1 prescaler (5 = 1024)
#define SCHEDULER_PRESCALER 5

// number of ticks for a specific number of seconds (64ns * 62500 = 4sec)
#define SCHEDULER_TICKS 62500

// number of seconds for each timer interrupt (result from above)
#define SCHEDULER_PERIOD 4

// maximun number of tasks to manage (save ram)
#define SCHEDULER_MAX_TASKS 5

void scheduler_init(uint8_t hour, uint8_t minutes);
void scheduler_set(uint8_t hour, uint8_t minutes);

int16_t task_add(uint8_t hour, uint8_t minutes, void (*f)());
void task_del(int16_t index);
void task_set(int16_t index, uint8_t hour, uint8_t minutes);

#endif
