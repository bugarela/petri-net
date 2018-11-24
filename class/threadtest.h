#ifndef THREADTEST_H
#define THREADTEST_H

#include <iostream>
#include <vector>
#include "petri.h"
#include "threads/sema.h"
#include "threads/task.h"
#include "threads/thread.h"

using namespace std;

class ThreadTest : public Task {
 private:
  vector<Thread*> threads;
  sema sThreads;
  PetriNet net;

 public:
  ThreadTest(int qtdThreads, PetriNet pnet);
  ~ThreadTest();

  // Task
  virtual bool Exec();
};

#endif  // THREADTEST_H
