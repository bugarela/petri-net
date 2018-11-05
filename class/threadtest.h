/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef THREADTEST_H
#define THREADTEST_H

#include "threads/thread.h"
#include "threads/sema.h"
#include "threads/task.h"
#include <vector>
#include <iostream>

using namespace std;

class ThreadTest : public Task
{
private:
    vector<Thread *> threads;
    sema sThreads;
public:
    ThreadTest(int qtdThreads);
    ~ThreadTest();
    
    // Task
    virtual bool Exec(); // primeiro método a ser executado por uma thread
};

#endif // THREADTEST_H
