/*
Implementa tarefa para programas multitheads
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
#include "task.h"


Task::Task()
{
	status = TaskStatusNotSubmitted;
	threads = 0;
}

Task::~Task()
{
}

void Task::StatusSet(TaskStatus_t status)
{
	statusSema.Lock();
	this->status = status;
	statusSema.Unlock();
}

TaskStatus_t Task::Status()
{
	TaskStatus_t state;

	statusSema.Lock();
	state = status;
	statusSema.Unlock();
	return state;
}

void Task::ThreadAdd()
{
	semaThreads.Lock();
	threads++;
	semaThreads.Unlock();
}

bool Task::ThreadRemove()
{
	bool retorno;
	
	semaThreads.Lock();
	if (threads > 0)
	{
		threads--;
		retorno = true;
	}
	else
		retorno = false;
	
	if (threads == 0)
		this->StatusSet(TaskStatusCompleted);
	semaThreads.Unlock();

	return retorno;
}

unsigned int Task::ThreadsQtdExec()
{
	unsigned int tam;
	
	semaThreads.Lock();
	tam = threads;
	semaThreads.Unlock();

	return tam;
}


bool Task::Exec()
{
	/*
	statusSema.Lock();
	//printf("Qtd threads %i\n", this->ThreadsQtdExec());
	if(this->ThreadsQtdExec() <= 1)
	this->status = TaskStatusCompleted;
	statusSema.Unlock();
	*/

	return false;
}
