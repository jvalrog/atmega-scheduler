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

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>

// Predefined Timer1 constants for 16MHz clock

// timer1 prescaler
#define SCHEDULER_PRESCALER 5

// number of ticks needed to define 1 second with timer1
#define SCHEDULER_TICKS 15625U

// maximun number of tasks to manage (save ram)
#define SCHEDULER_MAX_TASKS 5


void scheduler_init(uint8_t hour, uint8_t minutes);
void scheduler_set(uint8_t hour, uint8_t minutes);

int16_t task_add(uint8_t hour, uint8_t minutes, void (*f)());
void task_del(int16_t index);
void task_set(int16_t index, uint8_t hour, uint8_t minutes);

#ifdef __cplusplus
}
#endif

#endif
