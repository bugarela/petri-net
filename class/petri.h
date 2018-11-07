#include <vector>
#include <string>

using namespace std;

// #ifndef PETRI_H
// #define PETRI_H

#define N 0
#define R1 1
#define R2 2
#define L1 3
#define L2 4
#define S1 5
#define S2 6
#define G0 7
#define G1 8

#define R 1
#define L 3
#define S 5
#define G 7

class PetriNet{
public:
    vector <vector <int>> pre;
    vector <vector <int>> pos;
    vector <int> actions;
};
