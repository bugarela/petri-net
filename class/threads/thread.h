#pragma once

/*
Implementa thread para programas multitheads
Copyright (C) 2013  Rafael Alceste Berri rafaelberri@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef THREAD_H
#define THREAD_H

#ifdef __unix__
#include <pthread.h>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#include "task.h"

class Thread
{
protected:
#ifdef __unix__
	pthread_t id;
#elif defined(_WIN32) || defined(WIN32)
	HANDLE id;
#endif
  bool Start(Task *eTask);
	virtual bool Stop();
public:
	Thread();
	~Thread();
	bool Event(Task *eTask);
	bool IsCurrentThread();
  long int GetID();
	static void SleepMS(unsigned int tempo);
	static long int ID();
};

#endif // THREAD_H

