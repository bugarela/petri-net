//#include "stdafx.h"
/*
Implementa semaforo para programas multitheads
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


#include "sema.h"
#include "thread.h"
#include <iostream>

sema::sema()
{
	id = ++semaID; // começa em 1
#ifdef __unix__
  sem_init(&mutex, 0, 1);

#elif defined(_WIN32) || defined(WIN32)
	mutex = CreateSemaphore(
		NULL,           // default security attributes
		1,  // initial count --- count of threads that can be inside
		1,  // maximum count --- max threads inside
		NULL);          // unnamed semaphore
#endif
}

sema::~sema()
{
#ifdef __unix__
	sem_destroy(&mutex); /* destroy semaphore */
#elif defined(_WIN32) || defined(WIN32)
	CloseHandle(mutex);
#endif
}

unsigned int sema::ID()
{
	return id;
}

void sema::Lock()
{
#ifdef __unix__
  sem_wait(&mutex);
#elif defined(_WIN32) || defined(WIN32)
	while (1)
	{
		DWORD result = WaitForSingleObject(mutex,   // handle to semaphore
	   		                               99999999L);           // zero-second time-out interval

		// reservou para a thread
		if(result == WAIT_OBJECT_0)
			break;
		else
			Thread::SleepMS(SEMA_H_WAIT); // perder um tempo antes de tentar novamente
	}
#endif
	Thread::SleepMS(SEMA_H_WAIT); // perder um tempo antes de continuar
}

void sema::Unlock()
{
#ifdef __unix__
  sem_post(&mutex);
#elif defined(_WIN32) || defined(WIN32)
	ReleaseSemaphore(
		mutex,  // handle to semaphore
		1,            // increase count by one
		NULL);
#endif
}
