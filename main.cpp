#include <iostream>
#include <string>
#include <vector>
#include "class/mapatrem.h"
#include "class/threads/thread.h"
#include "class/threadtest.h"

using namespace std;

int main(int argc, char** argv) {
  int commands[] = {ANY, -1, -1};

  double velocities[] = {0, 0};

  vector<int> marking;
  marking.resize(17);
  marking[4] = 1;
  marking[5] = 1;
  marking[6] = 1;

  PetriNet station_net = PetriNet(0, "net", 17, 18, marking);

  vector<int> marking_train;
  marking_train.resize(3);
  marking_train[2] = 1;

  PetriNet train1_net = PetriNet(1, "train", 3, 4, marking_train);
  PetriNet train2_net = PetriNet(2, "train", 3, 4, marking_train);

  MapaTrem trens;
  trens.Trem1Pos(1, 1);
  trens.Trem1Txt("Mensagem trem 1.");
  trens.Trem2Pos(1, 2);
  trens.Trem2Txt("Mensagem trem 2.");

  trens.Gate(0);

  ThreadTest estacao(2, station_net, &commands, NULL, &trens);
  ThreadTest t1(1, train1_net, &commands, &velocities[0], NULL);
  ThreadTest t2(1, train2_net, &commands, &velocities[1], NULL);

  double v1 = 0, v2 = 0;
  float p1 = -1, p2 = -1;
  while (1) {
    // cout << velocities[0] << " " << velocities[1] << endl;
    if (v1 > velocities[0])
      v1 -= 0.001;
    else if (v1 < velocities[0])
      v1 += 0.001;

    if (v2 > velocities[1])
      v2 -= 0.001;
    else if (v2 < velocities[1])
      v2 += 0.001;

    p1 += v1;
    p2 += v2;

    if (p1 < 0)
      trens.Trem1Pos((-1) * p1, 1);
    else
      trens.Trem1Pos(p1, 0);

    trens.Trem1Txt("a1=" + to_string((int)trens.A1()) +
                   " a2=" + to_string((int)trens.A2()) +
                   " b1=" + to_string((int)trens.B1()) +
                   " b2=" + to_string((int)trens.B2()) +
                   " c=" + to_string((int)trens.C()));

    if (p2 < 0)
      trens.Trem2Pos((-1) * p2, 2);
    else
      trens.Trem2Pos(p2, 0);

    Thread::SleepMS(100);

    trens.Trem2Txt("a1=" + to_string((int)trens.A1()) +
                   " a2=" + to_string((int)trens.A2()) +
                   " b1=" + to_string((int)trens.B1()) +
                   " b2=" + to_string((int)trens.B2()) +
                   " c=" + to_string((int)trens.C()));

    int key = trens.GetLastKey();
    // cout << "LastKey = " << key << endl;
    if (key == 27) return 1;
  }

  trens.Trem1Txt("Mensagem trem 1.");

  trens.Trem2Txt("Mensagem trem 2.");

  while (1)
    ;
  return 0;
}
