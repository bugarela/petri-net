/*
 * It shows the map of the train problem (for petri nets)
 * Copyright (C) 2018  rafaelberri@gmail.com rafaelberri@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAPATREM_H
#define MAPATREM_H
#include "threads/sema.h"
#include "threads/thread.h"
#include "threads/task.h"
#include "linep.h"
#include <string>
#include <opencv2/opencv.hpp>
#include "draw.h"
#include "path.h"
#include <vector>

using namespace std;
using namespace cv;

class MapaTrem : public Task
{
protected:
    sema sMapa;
    Thread *thread = NULL;
    vector<Path *> trajetos;
    
    Mat fundoG0;
    Mat fundoG1;
    Mat trem1;
    Mat trem2;
    
    int lastKey = -1;
    
    float t1p = 0;
    int t1traj = 0;
    //int t1x = 0, t1y = 0;
    string t1msg = "";
    
    float t2p = 0;
    int t2traj = 0;
    //int t2x = 0, t2y = 0;
    string t2msg = "";
    
    int gate = 0;
    
    bool a1 = false, a2 = false, b1 = false, b2 = false, c = false;
    
    bool imgAdd(Mat &fundo, Mat &add, int x, int y, Vec3b transpColor);
    
    bool Sensores(Point3f p1, Point3f p2, bool &a1, bool &a2, bool &b1, bool &b2, bool &c);
    //bool Trem1Pos(int x, int y);
    //bool Trem2Pos(int x, int y);
public:
    MapaTrem();
    ~MapaTrem();
    int Width();
    int Height();
    
    bool Trem1Pos(float param, int trajeto);
    void GetTrem1Pos(float *param, int *trajeto);
    void GetTrem1Pos(int *x, int *y);
    void Trem1Txt(string mensagem);
    
    bool Trem2Pos(float param, int trajeto);
    void GetTrem2Pos(float *param, int *trajeto);
    void GetTrem2Pos(int *x, int *y);
    void Trem2Txt(string mensagem);
    
    void DistTrajetos();
    
    bool A1();
    bool A2();
    bool B1();
    bool B2();
    bool C();
    
    int GetLastKey();
    int GetLastKeyAndEmpty();
    
    int Gate();
    bool Gate(int position);
    
    // Task
    virtual bool Exec();
};

#endif // MAPATREM_H
