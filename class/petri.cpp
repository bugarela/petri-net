#include "petri.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

int random(int n, int m) { return rand() % (m - n + 1) + n; }

vector<vector<int>> read_matrix(string file, int n_places, int n_transitions) {
  vector<vector<int>> matrix;
  matrix.resize(n_places);
  for (int i = 0; i < n_places; i++) matrix[i].resize(n_transitions);

  ifstream in(file);

  if (!in.is_open()) {
    cout << file << " not found" << endl;
    exit(1);
  }
  for (int i = 0; i < n_places; i++)
    for (int j = 0; j < n_transitions; j++) in >> matrix[i][j];

  in.close();
  return matrix;
}

PetriNet::PetriNet() { cout << "Construtor vazio aaa" << endl; }

PetriNet::PetriNet(int id_net, string filename, int places, int transitions,
                   vector<int> initial_marking) {
  id = id_net;
  n_places = places;
  n_transitions = transitions;
  marking = initial_marking;

  pre = read_matrix(filename + "/pre.txt", n_places, n_transitions);
  pos = read_matrix(filename + "/pos.txt", n_places, n_transitions);
  actions.resize(n_transitions);

  int trem = id_net == 0 ? 0 : 100;
  for (int i = 0; i < n_transitions; i++) actions[i] = i + trem;
}

void PetriNet::setMarking(vector<int> marking) { marking = marking; }

vector<int> PetriNet::getMarking() { return marking; }

vector<int> PetriNet::sensibilized_transitions() {
  bool sensibilized;
  vector<int> transitions;
  transitions.resize(0);
  for (int j = 0; j < n_transitions; j++) {
    sensibilized = true;
    for (int i = 0; i < n_places; i++)
      if (marking[i] < pre[i][j]) sensibilized = false;
    if (sensibilized) transitions.push_back(j);
  }
  return transitions;
}

int PetriNet::choose_transition(vector<int> transitions, int command) {
  // cout << "ecolhendo - command = " << command << endl;
  if (transitions.size() == 0) return -1;
  if (command == ANY) return transitions[random(0, transitions.size() - 1)];

  for (int transition : transitions) {
    // cout << transition << " ";
    if (command == transition) return transition;
  }
  // cout << endl;
  return -1;
}

void PetriNet::execute_pre(int transition) {
  // cout << transition << endl;
  // for (int i = 0; i < n_places; i++) cout << marking[i] << " ";

  // cout << endl;

  // for (int i = 0; i < n_places; i++) cout << pre[i][transition] << " ";

  // cout << endl;

  for (int i = 0; i < n_places; i++) {
    marking[i] -= pre[i][transition];
    // cout << marking[i] << " ";
  }
  // cout << endl;
}

void PetriNet::execute_pos(int transition) {
  // for (int i = 0; i < n_places; i++) {
  //   cout << pos[i][transition] << " ";
  // }
  // cout << endl;
  for (int i = 0; i < n_places; i++) {
    marking[i] += pos[i][transition];
    // cout << marking[i] << " ";
  }
  // cout << endl;
}

void PetriNet::execute_action(int transition, int (*commands)[3],
                              double *velocity, MapaTrem *map, sema sThreads) {
  // cout << "action: " << actions[transition] << endl;
  switch (actions[transition]) {
    case 0:
      (*map).Gate(0);
      cout << "G=1" << endl;
      break;

    case 1:
      (*map).Gate(1);
      cout << "G=0" << endl;
      break;

    case 2:
      (*map).Gate(1);
      cout << "T1 entra na critica - G=1" << endl;
      while ((*map).C() == 0) Thread::SleepMS(1);
      cout << "T1 entra na critica - G=1" << endl;
      break;

    case 3:
      sThreads.Lock();
      *commands[1] = 2;
      sThreads.Unlock();
      cout << "T1 L" << endl;
      while ((*map).B1() == 0) Thread::SleepMS(1);
      cout << "T1 L" << endl;
      break;

    case 4:
      sThreads.Lock();
      *commands[1] = 3;
      sThreads.Unlock();
      cout << "T1 R" << endl;
      while ((*map).C() == 0) Thread::SleepMS(1);
      cout << "T1 R" << endl;
      break;

    case 5:
      sThreads.Lock();
      *commands[1] = 3;
      sThreads.Unlock();
      cout << "T1 R (inicio)" << endl;
      while ((*map).B1() == 0) Thread::SleepMS(1);
      cout << "T1 R (inicio)" << endl;
      break;

    case 6:
      sThreads.Lock();
      *commands[1] = 1;
      sThreads.Unlock();
      cout << "T1 S" << endl;
      (*map).Trem1Txt("Trem 1 Desembarcando.");
      Thread::SleepMS(4000);
      cout << "T1 S" << endl;
      break;

    case 7:
      sThreads.Lock();
      *commands[1] = 1;
      sThreads.Unlock();
      cout << "T1 S (espera)" << endl;
      break;

    case 8:
      sThreads.Lock();
      *commands[1] = 0;
      sThreads.Unlock();
      cout << "T1 S (final)" << endl;
      (*map).Trem1Txt("Esperando m1");
      while ((*map).GetLastKeyAndEmpty() != 49) Thread::SleepMS(10);
      cout << "T1 S (final)" << endl;
      break;

    case 9:
      cout << "T1 sai critica" << endl;
      while ((*map).A1() == 0) Thread::SleepMS(10);
      cout << "T1 sai critica" << endl;
      break;

    case 10:
      (*map).Gate(0);
      cout << "T2 entra na critica - G=0" << endl;
      while ((*map).C() == 0) Thread::SleepMS(10);
      cout << "T2 entra na critica - G=0" << endl;
      break;

    case 11:
      sThreads.Lock();
      *commands[2] = 2;
      sThreads.Unlock();
      cout << "T2 L" << endl;
      while ((*map).B2() == 0) Thread::SleepMS(10);
      cout << "T2 L" << endl;
      break;

    case 12:
      sThreads.Lock();
      *commands[2] = 3;
      sThreads.Unlock();
      cout << "T2 R" << endl;
      while ((*map).C() == 0) Thread::SleepMS(10);
      cout << "T2 R" << endl;
      break;

    case 13:
      sThreads.Lock();
      *commands[2] = 3;
      sThreads.Unlock();
      cout << "T2 R (inicio)" << endl;
      while ((*map).B2() == 0) Thread::SleepMS(10);
      cout << "T2 R (inicio)" << endl;
      break;

    case 14:
      sThreads.Lock();
      *commands[2] = 1;
      sThreads.Unlock();
      cout << "T2 S" << endl;
      (*map).Trem2Txt("Trem 2 Desembarcando.");
      Thread::SleepMS(4000);
      cout << "T2 S" << endl;
      break;

    case 15:
      sThreads.Lock();
      *commands[2] = 1;
      sThreads.Unlock();
      cout << "T2 S (espera)" << endl;
      break;

    case 16:
      sThreads.Lock();
      *commands[2] = 0;
      sThreads.Unlock();
      cout << "T2 S (final)" << endl;
      (*map).Trem2Txt("Esperando m2");
      while ((*map).GetLastKeyAndEmpty() != 50) Thread::SleepMS(10);
      cout << "T2 S (final)" << endl;
      break;

    case 17:
      cout << "T2 sai critica" << endl;
      while ((*map).A2() == 0) Thread::SleepMS(10);
      cout << "T2 sai critica" << endl;
      break;

      /* TRAIN ACTIONS: */

    case 100:
    case 101:
      cout << "Trem: S" << endl;
      *velocity = 0.0;
      break;

    case 102:
      cout << "Trem: L" << endl;
      *velocity = -0.01;
      break;

    case 103:
      cout << "Trem: R" << endl;
      *velocity = 0.01;
      break;
  }
}
