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

class PetriNet {
 public:
  vector<vector<int>> pre;
  vector<vector<int>> pos;
  vector<int> actions;
  vector<int> marking;
  int n_places;
  int n_transitions;

  PetriNet(string filename, int n_places, int n_transitions,
           vector<int> marking);

  void setMarking(vector<int> marking);
  vector<int> getMarking();

  vector<int> sensibilized_transitions();
  void execute_pre(int transition);
  void execute_pos(int transition);
  virtual void execute_action(int transition);
  virtual int choose_transition(vector<int> transitions);
};

class PetriTrain : public PetriNet {
 public:
  int command;
  void execute_action(int transition) override;
  int choose_transition(vector<int> transitions) override;
};
