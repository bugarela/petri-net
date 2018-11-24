#include <vector>
#include <string>

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

#define N_TRANSITIONS 18
#define N_PLACES 17


class PetriNet{
  public:
      vector <vector <int>> pre;
      vector <vector <int>> pos;
      vector <int> actions;
      vector <int> marking;
};

void build_nets();
void set_petrinet(PetriNet new_net, int scope);
vector <int> sensibilized_transitions(PetriNet pnet);
PetriNet get_petrinet(int scope);
PetriNet execute_pre(PetriNet pnet, int transition);
PetriNet execute_pos(PetriNet pnet, int transition);
void execute_action(PetriNet pnet, int transition);
int choosed_transition(vector <int> transitions, int scope);
