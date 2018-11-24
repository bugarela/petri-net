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

#include "threadtest.h"
#include <cstdlib>

ThreadTest::ThreadTest(int qtdThreads, PetriNet *net) {
  for (int i = 0; i < qtdThreads; i++) {
    Thread *th = new Thread();
    threads.push_back(th);
    th->Event((Task *)this);  // inicia a thread
  }
}

ThreadTest::~ThreadTest() {
  for (Thread *th : threads) {
    delete th;
  }
  threads.clear();
}

bool ThreadTest::Exec() {
  while (1) {
    cout << net->n_transitions << endl;
    cout << "Me de trabalho! Sou a Thread " << Thread::ID() << endl;
    sThreads.Lock();
    cout << "aa";
    vector<int> transitions = net->sensibilized_transitions();

    int transition_position = -1;
    while (transition_position == -1) {
      transition_position = net->choose_transition(transitions);
      Thread::SleepMS(100);
    }

    net->execute_pre(transition_position);
    // execute_action(net->action);
    net->execute_pos(transition_position);

    sThreads.Unlock();

    Thread::SleepMS(1000);  // espera 1 segundo
  }

  return true;
}
