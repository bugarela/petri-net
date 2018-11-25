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

  int trem = filename == "net" ? 0 : 100;
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
      (*map).Gate(1);
      cout << "G=1" << endl;
      break;
    case 1:
      (*map).Gate(0);
      cout << "G=0" << endl;
      break;
    case 2:
      (*map).Gate(1);
      cout << "T1 entra na critica" << endl;
      break;
    case 3:
      *commands[1] = 2;
      cout << "T1 L" << endl;
      sThreads.Unlock();
      while ((*map).B1() == 0) Thread::SleepMS(10);
      sThreads.Lock();
      break;
    case 4:
      *commands[1] = 3;
      cout << "T1 R" << endl;
      sThreads.Unlock();
      while ((*map).C() == 0) Thread::SleepMS(10);
      sThreads.Lock();
      break;
    case 5:
      *commands[1] = 3;
      cout << "T2 R (inicio)" << endl;
      sThreads.Unlock();
      while ((*map).B1() == 0) Thread::SleepMS(10);
      sThreads.Lock();
      break;
    case 6:
      *commands[1] = 1;
      cout << "T1 S" << endl;
      sThreads.Unlock();
      (*map).Trem1Txt("Trem 1 Desembarcando.");
      Thread::SleepMS(10000);
      sThreads.Lock();
      break;
    case 7:
      cout << "T1 S (espera)" << endl;
      break;
    case 8:
      *commands[1] = 0;
      cout << "T1 S (final)" << endl;
      // m1
      break;
    case 9:
      cout << "T1 sai critica" << endl;
      sThreads.Unlock();
      while ((*map).A1() == 0) Thread::SleepMS(10);
      sThreads.Lock();
      break;
    case 10:
      (*map).Gate(0);
      cout << "T2 entra na critica" << endl;
      break;
    case 11:
      *commands[2] = 2;
      cout << "T2 L" << endl;
      sThreads.Unlock();
      while ((*map).B2() == 0) Thread::SleepMS(10);
      sThreads.Lock();
      break;
    case 12:
      *commands[2] = 3;
      cout << "T2 R" << endl;
      sThreads.Unlock();
      while ((*map).C() == 0) Thread::SleepMS(10);
      sThreads.Lock();
      break;
      break;
    case 13:
      *commands[2] = 3;
      cout << "T2 R (inicio)" << endl;
      sThreads.Unlock();
      while ((*map).C() == 0) Thread::SleepMS(10);
      sThreads.Lock();
      break;
      break;
    case 14:
      *commands[2] = 1;
      cout << "T2 S" << endl;
      sThreads.Unlock();
      (*map).Trem2Txt("Trem 2 Desembarcando.");
      Thread::SleepMS(10000);
      sThreads.Lock();
      break;
      break;
    case 15:
      cout << "T2 S (espera)" << endl;
      break;
    case 16:
      *commands[2] = 0;
      cout << "T2 S (final)" << endl;
      // m2
    case 17:
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
      *velocity = -0.1;
      break;

    case 103:
      cout << "Trem: R" << endl;
      *velocity = 0.1;
      break;
  }
}
