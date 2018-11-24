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

vector<int> read_vector(string file, int n_transitions) {
  vector<int> actions;
  actions.resize(n_transitions);

  ifstream in(file);

  if (!in.is_open()) {
    cout << file << " not found" << endl;
    exit(1);
  }

  char ac;
  int trem;

  for (int i = 0; i < n_transitions; i++) {
    in >> ac >> trem;
    switch (ac) {
      case 'N':
        actions[i] = N;
        break;
      case 'R':
        actions[i] = R + (trem - 1);
        break;
      case 'L':
        actions[i] = L + (trem - 1);
        break;
      case 'S':
        actions[i] = S + (trem - 1);
        break;
      case 'G':
        actions[i] = G + (trem);
        break;
    }
  }

  in.close();
  return actions;
}

PetriNet::PetriNet(string filename, int n_places, int n_transitions,
                   vector<int> marking) {
  pre = read_matrix(filename + "/pre.txt", n_places, n_transitions);
  pos = read_matrix(filename + "/pos.txt", n_places, n_transitions);
  actions = read_vector(filename + "/actions.txt", n_transitions);
  marking = marking;

  n_places = n_places;
  n_transitions = n_transitions;
}

void PetriNet::setMarking(vector<int> marking) { marking = marking; }

vector<int> PetriNet::getMarking() { return marking; }

vector<int> PetriNet::sensibilized_transitions() {
  bool sensibilized;
  vector<int> transitions;
  transitions.resize(0);
  system("pause");
  for (int j = 0; j < n_transitions; j++) {
    sensibilized = true;
    for (int i = 0; i < n_places; i++)
      if (marking[i] < pre[i][j]) sensibilized = false;
    if (sensibilized) transitions.push_back(j);
  }

  return transitions;
}

void PetriNet::execute_pre(int transition) {
  cout << transition << endl;
  for (int i = 0; i < n_places; i++) cout << marking[i] << " ";

  cout << endl;

  for (int i = 0; i < n_places; i++) cout << pre[i][transition] << " ";

  cout << endl;

  for (int i = 0; i < n_places; i++) {
    marking[i] -= pre[i][transition];
    cout << marking[i] << " ";
  }
  cout << endl;
}

void PetriNet::execute_pos(int transition) {
  for (int i = 0; i < n_places; i++) {
    cout << pos[i][transition] << " ";
  }
  cout << endl;
  for (int i = 0; i < n_places; i++) {
    marking[i] += pos[i][transition];
    cout << marking[i] << " ";
  }
  cout << endl;
}

void PetriNet::execute_action(int transition) {
  switch (actions[transition]) {
    case N:
      break;

    case R1:
      // train_command[0] = R;
      // show("T " + transition + " Mandou Trem 1 para direita");
      break;

    case R2:

      break;

    case L1:

      break;

    case L2:

      break;

    case S1:

      break;

    case S2:

      break;

    case G0:

      break;

    case G1:

      break;
  }
}

void PetriTrain::execute_action(int transition) {
  switch (actions[transition]) {
    case R:
      break;

    case L:

      break;

    case S:

      break;
  }
}

int PetriNet::choose_transition(vector<int> transitions) {
  return transitions[random(0, transitions.size() - 1)];
}

int PetriTrain::choose_transition(vector<int> transitions) {
  for (int transition : transitions)
    if (command == transition) return transition;

  return -1;
}
