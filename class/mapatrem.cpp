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

#include "mapatrem.h"

MapaTrem::MapaTrem()
{
    Path *trajeto;
    
    fundoG1 = imread("img/mapa1.png", CV_LOAD_IMAGE_COLOR);   // Read the file
    fundoG0 = imread("img/mapa2.png", CV_LOAD_IMAGE_COLOR);   // Read the file
    trem1 = imread("img/train1.png", CV_LOAD_IMAGE_COLOR);
    trem2 = imread("img/train2.png", CV_LOAD_IMAGE_COLOR);
    
    // secao critica
    trajeto = new Path();
    trajeto->AddPoint(Point3f(304, 242, 0));
    trajeto->AddPoint(Point3f(435, 242, 0));
    trajeto->AddPoint(Point3f(475, 242, 0));
    trajetos.push_back(trajeto);
    
    // T1
    trajeto = new Path();
    trajeto->AddPoint(Point3f(304, 242, 0));
    trajeto->AddPoint(Point3f(180, 158, 0));
    trajeto->AddPoint(Point3f(67, 158, 0));
    trajeto->AddPoint(Point3f(25, 158, 0));
    trajetos.push_back(trajeto);
        
     // T2
    trajeto = new Path();
    trajeto->AddPoint(Point3f(304, 242, 0));
    trajeto->AddPoint(Point3f(180, 326, 0));
    trajeto->AddPoint(Point3f(67, 326, 0));
    trajeto->AddPoint(Point3f(25, 326, 0));
    trajetos.push_back(trajeto);
      
    thread = new Thread();
    thread->Event((Task *) this);
}

MapaTrem::~MapaTrem()
{    
    for(Path *traj: trajetos)
        delete traj;
    
    if(thread != NULL)
        delete thread;
}

void MapaTrem::DistTrajetos()
{
    cout << " T0 " << endl;
    trajetos[0]->DispPath();
     
    cout << endl << " T1 " << endl;
    trajetos[1]->DispPath();
     
    cout << endl << " T2 " << endl;
    trajetos[2]->DispPath();
}


int MapaTrem::Gate()
{
    int g;
    sMapa.Lock();
    g = gate;
    sMapa.Unlock();
    
    return g;
}

bool MapaTrem::Gate(int position)
{
    if(position > 1 || position < 0)
        return false;
    
    sMapa.Lock();
    gate=position;
    sMapa.Unlock();
    
    return true;
}

bool MapaTrem::A1()
{
    bool r;
    sMapa.Lock();
    r = a1;
    sMapa.Unlock();
    
    return r;
}

bool MapaTrem::A2()
{
    bool r;
    sMapa.Lock();
    r = a2;
    sMapa.Unlock();
    
    return r;
}

bool MapaTrem::B1()
{
    bool r;
    sMapa.Lock();
    r = b1;
    sMapa.Unlock();
    
    return r;
}

bool MapaTrem::B2()
{
    bool r;
    sMapa.Lock();
    r = b2;
    sMapa.Unlock();
    
    return r;
}

bool MapaTrem::C()
{
    bool r;
    sMapa.Lock();
    r = c;
    sMapa.Unlock();
    
    return r;
}

bool MapaTrem::Sensores(Point3f p1, Point3f p2, bool& a1, bool& a2, bool& b1, bool& b2, bool& c)
{
    Point3f pa1(67, 158, 0), pb1(180, 158, 0), pa2(67, 326, 0), pb2(180, 326, 0), pc(435, 242, 0);
    
    if(linep::Distance(p1, pa1) < 5 || linep::Distance(p2, pa1) < 5)
        a1 = true;
    else
        a1 = false;
    
    if(linep::Distance(p1, pa2) < 5 || linep::Distance(p2, pa2) < 5)
        a2 = true;
    else
        a2 = false;
    
    if(linep::Distance(p1, pb1) < 5 || linep::Distance(p2, pb1) < 5)
        b1 = true;
    else
        b1 = false;
    
    if(linep::Distance(p1, pb2) < 5 || linep::Distance(p2, pb2) < 5)
        b2 = true;
    else
        b2 = false;
    
    if(linep::Distance(p1, pc) < 5 || linep::Distance(p2, pc) < 5)
        c = true;
    else
        c = false;
    
    return true;
}

int MapaTrem::GetLastKey()
{
    int l = 0;
    sMapa.Lock();
    l = lastKey;
    sMapa.Unlock();
    
    return l;
}

int MapaTrem::GetLastKeyAndEmpty()
{
    int l = 0;
    sMapa.Lock();
    l = lastKey;
    lastKey = -1;
    sMapa.Unlock();
    
    return l;
}

bool MapaTrem::Trem1Pos(float param, int trajeto)
{
    int w = this->Width();
    int h = this->Height();
    int x,y;
    Point3f pt;
    Point3f pt2;
    int trajSize = 0;

    sMapa.Lock();
    trajSize = trajetos.size();
    sMapa.Unlock();
    
    if(trajeto < 0 || trajeto >= trajSize)
        return false;
    
    sMapa.Lock();
    pt = trajetos[trajeto]->GetPoint(param);
    sMapa.Unlock();
    
    x = (int) (pt.x + 0.5);
    y = (int) (pt.y + 0.5);
    
    if(x < 0 || x >= w || y < 0 || y >= h)
    {
        return false;
    }
    
    sMapa.Lock();
    t1p = param;
    t1traj = trajeto;
    
    pt2 = trajetos[t2p]->GetPoint(t2traj);
    Sensores(pt, pt2, a1, a2, b1, b2, c);
    sMapa.Unlock();
    
    return true;
}

void MapaTrem::GetTrem1Pos(float* param, int* trajeto)
{
    sMapa.Lock();
    *param = t1p;
    *trajeto = t1traj;
    sMapa.Unlock();
}

void MapaTrem::GetTrem1Pos(int* x, int* y)
{
    Point3f pt;
    sMapa.Lock();
    cout << " Trajeto " << t1traj << " Pos " << t1p << endl;
    pt = trajetos[t1traj]->GetPoint(t1p);
    sMapa.Unlock();
    
    *x = (int) (pt.x + 0.5);
    *y = (int) (pt.y + 0.5);
}

void MapaTrem::Trem1Txt(string mensagem)
{
    sMapa.Lock();
    t1msg = mensagem;
    sMapa.Unlock();
}

void MapaTrem::Trem2Txt(string mensagem)
{
    sMapa.Lock();
    t2msg = mensagem;
    sMapa.Unlock();
}

bool MapaTrem::Trem2Pos(float param, int trajeto)
{
    int w = this->Width();
    int h = this->Height();
    int x,y;
    Point3f pt, pt2;
    int trajSize = 0;
    
    sMapa.Lock();
    trajSize = trajetos.size();
    sMapa.Unlock();
    
    if(trajeto < 0 || trajeto >= trajSize)
        return false;
    
    sMapa.Lock();
    pt = trajetos[trajeto]->GetPoint(param);
    sMapa.Unlock();
    
    x = (int) (pt.x + 0.5);
    y = (int) (pt.y + 0.5);
    
    if(x < 0 || x >= w || y < 0 || y >= h)
    {
        return false;
    }
    
    sMapa.Lock();
    t2p = param;
    t2traj = trajeto;
    
    pt2 = trajetos[t1p]->GetPoint(t1traj);
    Sensores(pt, pt2, a1, a2, b1, b2, c);
    sMapa.Unlock();
    
    return true;
}

void MapaTrem::GetTrem2Pos(float* param, int* trajeto)
{
    sMapa.Lock();
    *param = t2p;
    *trajeto = t2traj;
    sMapa.Unlock();
}

void MapaTrem::GetTrem2Pos(int* x, int* y)
{
    Point3f pt;
    sMapa.Lock();
    pt = trajetos[t2traj]->GetPoint(t2p);
    sMapa.Unlock();
    
    *x = (int) (pt.x + 0.5);
    *y = (int) (pt.y + 0.5);
}

int MapaTrem::Height()
{
    int h;
    sMapa.Lock();
    h = fundoG0.rows;
    sMapa.Unlock();
    
    return h;
}

int MapaTrem::Width()
{
    int w;
    sMapa.Lock();
    w = fundoG0.cols;
    sMapa.Unlock();
    
    return w;
}

bool MapaTrem::imgAdd(cv::Mat &fundo, cv::Mat &add, int x, int y, Vec3b transpColor)
{
    Vec3b *pixel;
    Rect local;
    
    local.width = add.cols;
    local.height = add.rows;
    local.x = x - local.width / 2;
    local.y = y - local.height / 2;
    
    if(local.x < 0 ||
        local.y < 0 ||
        fundo.cols < local.x + local.width ||
        fundo.rows < local.y + local.height)
        return false;
    
    for (int i = 0; i < add.rows; i++)
    {
        for (int j = 0; j < add.cols; j++)
        {
            pixel = add.ptr<Vec3b>(j, i);
            
            if(*pixel != transpColor)
                fundo.at<Vec3b>(Point(i + local.x, j + local.y)) = *pixel;
        }
    }
    
    return true;
}



// Task
bool MapaTrem::Exec()
{
    while(1)
    {
        Mat img;
        
        if(this->Gate() == 0)
        {
            sMapa.Lock();
            img = fundoG0.clone();
            sMapa.Unlock();
        }
        else
            img = fundoG1.clone();
        
        Point3f pt;
        string msg;
    
        // trem 1
        sMapa.Lock();
        pt = trajetos[t1traj]->GetPoint(t1p);
        msg = t1msg;
        sMapa.Unlock();
        imgAdd(img, trem1, (int) (pt.x + 0.5), (int) (pt.y + 0.5), Vec3b(255,255,255));
        
        if(msg != "")
            draw::text(msg, &img, Point(10,50), Scalar::all(0), 1);
        
        // trem 2
        sMapa.Lock();
        pt = trajetos[t2traj]->GetPoint(t2p);
        msg = t2msg;
        sMapa.Unlock();
        imgAdd(img, trem2, (int) (pt.x + 0.5), (int) (pt.y + 0.5), Vec3b(255,255,255));
        
        if(msg != "")
            draw::text(msg, &img, Point(10,450), Scalar::all(0), 1);
        
        imshow( "Trens", img);
        int key = waitKey(1);
        
        if(key != -1)
        {
            sMapa.Lock();
            lastKey = key;
            sMapa.Unlock();
        }
    }
    
    return true;
}

