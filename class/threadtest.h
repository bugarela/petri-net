#ifndef THREADTEST_H
#define THREADTEST_H

#include <iostream>
#include <vector>
#include "mapatrem.h"
#include "petri.h"
#include "threads/sema.h"
#include "threads/task.h"
#include "threads/thread.h"

using namespace std;

class ThreadTest : public Task {
 private:
  vector<Thread *> threads;
  sema sThreads;
  PetriNet net;
  int (*commands)[3];
  double *velocity;
  MapaTrem *map;

 public:
  ThreadTest(int qtdThreads, PetriNet pnet, int (*commands)[3],
             double *velocity_address, MapaTrem *read_map);
  ~ThreadTest();

  // Task
  virtual bool Exec();
};

#endif  // THREADTEST_H
