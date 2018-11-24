#include <string>
#include <vector>

using namespace std;

// #ifndef PETRI_H
// #define PETRI_H

#define STATION 0
#define TREM_1 1
#define TREM_2 2

#define N 10
#define R1 11
#define R2 12
#define L1 13
#define L2 14
#define S1 15
#define S2 16
#define G0 17
#define G1 18

#define R 11
#define L 13
#define S 15
#define G 17

#define TR 101
#define TL 102
#define TS 103

class PetriNet {
 public:
  vector<vector<int>> pre;
  vector<vector<int>> pos;
  vector<int> actions;
  vector<int> marking;
  int n_places;
  int n_transitions;
  int command;

  PetriNet();

  PetriNet(string filename, int places, int transitions,
           vector<int> initial_marking);

  void setMarking(vector<int> marking);
  vector<int> getMarking();

  vector<int> sensibilized_transitions();
  void execute_pre(int transition);
  void execute_pos(int transition);
  void execute_action(int transition);
  int choose_transition(vector<int> transitions);
};