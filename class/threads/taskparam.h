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


#ifndef TASKPARAM_H
#define TASKPARAM_H

#include<vector>
#include<algorithm>

using namespace std;

#include "task.h"
#include "sema.h"
#include "thread.h"

class TaskParam;
class ThreadParam;

class ThreadParamNode
{
public:
  ThreadParamNode() {}
  ~ThreadParamNode() {}
  
  ThreadParam *thread = NULL;
  TaskParam *task = NULL;
  vector<void *> *jobs = NULL;
  sema *semaJobs = NULL;
};

class ThreadParam //: public Thread
{
protected:
  ThreadParamNode *node = NULL;
#ifdef __unix__
	pthread_t id;
#elif defined(_WIN32) || defined(WIN32)
	HANDLE id;
#endif
  bool concluded = false;
  sema semaConcluded;
  vector<void *> jobs;
  sema semaJobs;
  
  bool Start(Task *eTask);
public:
	ThreadParam(TaskParam *eTask);
	~ThreadParam();
	bool IsCurrentThread();
  long int GetID();
	static void SleepMS(unsigned int tempo);
	static long int ID();
  bool NewJob(void *data);
  unsigned int QtdJobs();
  void ConcludeProcess();
  void RestartProcess();
  bool Concluded();
};


class TaskParam : Task
{
protected:
	TaskParam();
public:
	~TaskParam();
  
  virtual bool Exec(ThreadParam *thread, void *data);
};

#endif
