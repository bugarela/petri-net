#include "threadtest.h"
#include <cstdlib>

ThreadTest::ThreadTest(int qtdThreads, PetriNet pnet, int (*commands_addr)[3],
                       double *velocity_address, MapaTrem *read_map) {
  net = pnet;
  commands = commands_addr;
  velocity = velocity_address;
  map = read_map;

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
    sThreads.Lock();
    // cout << "Lock da " << Thread::ID() << endl;

    vector<int> transitions = net.sensibilized_transitions();

    int transition_position =
        net.choose_transition(transitions, *commands[net.id]);

    if (transition_position == -1) {
      // cout << "Unlock da " << Thread::ID() << endl;
      sThreads.Unlock();
      Thread::SleepMS(100);
      continue;
    }

    cout << net.n_transitions << endl;

    net.execute_pre(transition_position);

    net.execute_action(transition_position, commands, velocity, map,
                       ref(sThreads));

    net.execute_pos(transition_position);

    // cout << "Unlock da " << Thread::ID() << endl;
    sThreads.Unlock();
    Thread::SleepMS(100);
  }

  return true;
}
