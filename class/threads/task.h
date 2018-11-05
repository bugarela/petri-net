#pragma once

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


#ifndef TASK_H
#define TASK_H

#include<vector>
#include<algorithm>

using namespace std;

#include "sema.h"

typedef enum {
	TaskStatusNotSubmitted,
	TaskStatusWaitingOnQueue,
	TaskStatusBeingProcessed,
	TaskStatusCompleted
} TaskStatus_t;

class Task
{
private:
	sema statusSema, semaThreads;
protected:
	sema semaphoro;
	TaskStatus_t status;
	unsigned int threads;
	Task();
	void ThreadAdd();
	bool ThreadRemove();
public:
	virtual void StatusSet(TaskStatus_t status);
	TaskStatus_t Status();
	~Task();
	unsigned int ThreadsQtdExec();
	virtual bool Exec();
};

#endif