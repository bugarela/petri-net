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

#include <cstdlib>
#include "threadtest.h"

int random(int n, int m){
    return rand() % (m - n + 1) + n;
}

ThreadTest::ThreadTest(int qtdThreads)
{
    for(int i = 0; i < qtdThreads; i++)
    {
        Thread *th = new Thread();
        threads.push_back(th);
        th->Event((Task *) this); // inicia a thread
    }
}

ThreadTest::~ThreadTest()
{
    for(Thread *th : threads)
    {
        delete th;
    }
    threads.clear();
}

bool ThreadTest::Exec()
{
    // prendendo a thread na função
    while(1)
    {
        cout << "Me de trabalho! Sou a Thread " << Thread::ID() << endl;
        sThreads.Lock();
        PetriNet net = get_petrinet();
        vector <int> transitions = sensibilized_transitions(net);
        int transition_position = transitions[random(0, transitions.size()-1)];

        net = execute_pre(net, transition_position);
        //execute_action(net.action);
        net = execute_pos(net, transition_position);

        set_petrinet(net);
        sThreads.Unlock();

        Thread::SleepMS(1000); // espera 1 segundo
    }

    return true;
}
