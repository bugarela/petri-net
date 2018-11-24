#include <iostream>
#include <string>
#include <vector>
#include "class/mapatrem.h"
#include "class/threads/thread.h"
#include "class/threadtest.h"

using namespace std;

int main(int argc, char** argv) {
  vector<int> marking;
  marking.resize(17);
  marking[4] = 1;
  marking[5] = 1;
  marking[6] = 1;

  PetriNet* station_net = new PetriNet("net", 17, 18, marking);

  vector<int> marking_train;
  marking_train.resize(3);
  marking_train[2] = 1;

  PetriNet train1_net = PetriNet("train", 3, 4, marking_train);
  PetriNet train2_net = PetriNet("train", 3, 4, marking_train);

  ThreadTest estacao(2, station_net);

  // Thread::SleepMS(4000);
  // ThreadTest trem1(1, TREM_1);
  // ThreadTest trem2(1, TREM_2);
  // vector <int> transitions = sensibilized_transitions(net);

  MapaTrem trens;

  trens.Trem1Pos(1, 1);
  trens.Trem1Txt("Mensagem trem 1.");
  trens.Trem2Pos(1, 2);
  trens.Trem2Txt("Mensagem trem 2.");

  trens.Gate(1);

  for (float p = -1; p <= 1; p += 0.01)  // velocidade = 0.01
  {
    if (p < 0)
      trens.Trem1Pos((-1) * p, 1);
    else
      trens.Trem1Pos(p, 0);
    // trens.Trem1Pos(p.x,p.y);
    Thread::SleepMS(10);

    trens.Trem1Txt("a1=" + to_string((int)trens.A1()) +
                   " a2=" + to_string((int)trens.A2()) +
                   " b1=" + to_string((int)trens.B1()) +
                   " b2=" + to_string((int)trens.B2()) +
                   " c=" + to_string((int)trens.C()));

    int key = trens.GetLastKey();
    // cout << "LastKey = " << key << endl;
    if (key == 27) return 1;
  }

  trens.Trem1Txt("Mensagem trem 1.");

  trens.Gate(0);
  for (float p = -1; p <= 1; p += 0.01) {
    if (p < 0)
      trens.Trem2Pos((-1) * p, 2);
    else
      trens.Trem2Pos(p, 0);
    // trens.Trem1Pos(p.x,p.y);
    Thread::SleepMS(10);

    trens.Trem2Txt("a1=" + to_string((int)trens.A1()) +
                   " a2=" + to_string((int)trens.A2()) +
                   " b1=" + to_string((int)trens.B1()) +
                   " b2=" + to_string((int)trens.B2()) +
                   " c=" + to_string((int)trens.C()));

    int key = trens.GetLastKey();
    // cout << "LastKey = " << key << endl;
    if (key == 27) return 1;
  }

  trens.Trem2Txt("Mensagem trem 2.");

  while (1)
    ;
  return 0;
}
