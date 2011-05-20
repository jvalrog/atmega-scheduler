//      atmega-scheduler.c
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

#include "atmega-scheduler.h"

struct _sched_task_t {
	uint8_t hour;
	uint8_t minutes;
	void (*task)();
};

volatile uint8_t _sched_hours;
volatile uint8_t _sched_minutes;
volatile uint8_t _sched_seconds;
volatile struct _sched_task_t _sched_tasks[SCHEDULER_MAX_TASKS];

void scheduler_init(uint8_t hour, uint8_t minutes) {
	int16_t index;
	
	TIMSK1 &= ~(1<<OCIE1A);
	
	for(index=0; index<SCHEDULER_MAX_TASKS; index++)
		_sched_tasks[index].task = NULL;
	
	_sched_hours = hour;
	_sched_minutes = minutes;
	_sched_seconds = 0;
	
	OCR1A = SCHEDULER_TICKS;
	TCCR1A = 0;
	TCCR1B = SCHEDULER_PRESCALER | (1<<WGM12);
	TCNT1 = 0;
	TIMSK1 |= (1<<OCIE1A);
}

void scheduler_set(uint8_t hour, uint8_t minutes) {
	TIMSK1 &= ~(1<<OCIE1A);
	_sched_hours = hour;
	_sched_minutes = minutes;
	_sched_seconds = 0;
	TIMSK1 |= (1<<OCIE1A);
}

int16_t task_add(uint8_t hour, uint8_t minutes, void (*f)()) {
	int16_t index;
	volatile struct _sched_task_t *task;
	
	for(index=0; index<SCHEDULER_MAX_TASKS; index++) {
		task = &_sched_tasks[index];
		if (task->task == NULL) {
			TIMSK1 &= ~(1<<OCIE1A);
			task->hour = hour;
			task->minutes = minutes;
			task->task = f;
			TIMSK1 |= (1<<OCIE1A);
			return index;
		}
	}
	return -1;
}

void task_del(int16_t index) {
	_sched_tasks[index].task = NULL;
}

void task_set(int16_t index, uint8_t hour, uint8_t minutes) {
	TIMSK1 &= ~(1<<OCIE1A);
	_sched_tasks[index].hour = hour;
	_sched_tasks[index].minutes = minutes;
	TIMSK1 |= (1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
	int16_t index;
	volatile struct _sched_task_t *task;

	_sched_seconds += SCHEDULER_PERIOD;
	if (_sched_seconds >= 60) {
		_sched_seconds = _sched_seconds % 60;
		_sched_minutes++;
		if (_sched_minutes == 60) {
			_sched_minutes = 0;
			_sched_hours++;
			if (_sched_hours == 24)
				_sched_hours = 0;
		}
		for(index=0; index<SCHEDULER_MAX_TASKS; index++) {
			task = &_sched_tasks[index];
			if ((task->task != NULL) && (task->hour == _sched_hours) && (task->minutes == _sched_minutes))
				task->task();
		}
	}
}
