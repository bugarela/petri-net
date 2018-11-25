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
  marking[0] = 1;
  marking[1] = 1;
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

  ThreadTest estacao(3, station_net, &commands, NULL, &trens);
  ThreadTest t1(1, train1_net, &commands, &velocities[0], NULL);
  ThreadTest t2(1, train2_net, &commands, &velocities[1], NULL);

  double v1 = 0, v2 = 0, acceleration;
  float p1 = -1, p2 = -1;
  while (1) {
    // Thread::SleepMS(100);

    if (velocities[0] == 0)
      acceleration = 0.001;
    else
      acceleration = 0.0001;

    if (v1 > velocities[0])
      v1 -= acceleration;
    else if (v1 < velocities[0])
      v1 += acceleration;

    if (abs(v1) < 0.001) v1 = 0;

    p1 += velocities[0];

    if (p1 < 0)
      trens.Trem1Pos((-1) * p1, 1);
    else
      trens.Trem1Pos(p1, 0);

    trens.Trem1Txt("a1=" + to_string((int)trens.A1()) +
                   " a2=" + to_string((int)trens.A2()) +
                   " b1=" + to_string((int)trens.B1()) +
                   " b2=" + to_string((int)trens.B2()) +
                   " c=" + to_string((int)trens.C()));

    // Thread::SleepMS(100);
    if (velocities[1] == 0)
      acceleration = 0.001;
    else
      acceleration = 0.0001;

    if (v2 > velocities[1])
      v2 -= acceleration;
    else if (v2 < velocities[1])
      v2 += acceleration;

    if (abs(v2) < 0.0001) v2 = 0;

    p2 += velocities[1];

    if (p2 < 0)
      trens.Trem2Pos((-1) * p2, 2);
    else
      trens.Trem2Pos(p2, 0);

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
