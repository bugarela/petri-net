#pragma once

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


#ifndef SEMA_H
#define SEMA_H

#define SEMA_H_WAIT 1
//#define SEMA_H_WAIT 5

#pragma once

//#include "thread.h"

#ifdef __unix__
#include <semaphore.h>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

static unsigned int semaID = 0;

class sema
{
private:
	unsigned int id;
#ifdef __unix__
	sem_t mutex;
#elif defined(_WIN32) || defined(WIN32)
	HANDLE mutex;
#endif

public:
	sema();
	~sema();
	unsigned int ID();
	void Lock();
	void Unlock();
};

#endif // SEMA_H

