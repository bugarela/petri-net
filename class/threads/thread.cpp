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


//#include "stdafx.h"
#include "thread.h"
#include <iostream>

#ifdef __unix__
#include <unistd.h>
#include <cxxabi.h>
//#include <thread>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

// Thread
Thread::Thread()
{
	this->id = 0;
}

Thread::~Thread()
{
	this->Stop();
}

#ifdef __unix__
void *exec(void *ptr)
{
	try
  {
    ((Task *)ptr)->Exec();
  }   
  catch (abi::__forced_unwind&)
  {  // handle pthread_cancel stack unwinding exception
      throw;
  }
  catch (exception &ex) 
  {
      throw ex;
  }

	return NULL;
}
#elif defined(_WIN32) || defined(WIN32)
DWORD WINAPI exec(LPVOID ptr)
{
	((Task *)ptr)->Exec();
	return 0;
}
#endif

bool Thread::Event(Task* eTask)
{
	this->Stop();
	this->Start(eTask);

	return true;
}

void Thread::SleepMS(unsigned int tempo)
{
#ifdef __unix__
	usleep(tempo * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#elif defined(_WIN32) || defined(WIN32)
	Sleep(tempo);
#endif
}

bool Thread::Start(Task *eTask)
{
#ifdef __unix__
	int ret;
	ret = pthread_create(&this->id, NULL, exec, (void*)eTask);
#elif defined(_WIN32) || defined(WIN32)
	this->id = CreateThread(0, 0, exec, (void*)eTask, 0, NULL);
#endif

	return true;
}

bool Thread::Stop()
{
	if (this->id != 0)
  {
#ifdef __unix__
    void *res;

    pthread_cancel(id);
    pthread_join(id, &res);
#elif defined(_WIN32) || defined(WIN32)
		CloseHandle(id);
#endif
  }
	this->id = 0;

	return true;
}

bool Thread::IsCurrentThread()
{
  if((long int) this->id == Thread::ID())
    return true;
  return false;
}

long int Thread::ID()
{
#ifdef __unix__
	return pthread_self();
#elif defined(_WIN32) || defined(WIN32)
	return (long int) GetCurrentThreadId();
#endif
}

long int Thread::GetID()
{
// implementar para linux
#ifdef __unix__
	return id;
#elif defined(_WIN32) || defined(WIN32)
	return (long int) id();
#endif
}

