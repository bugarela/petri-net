/*
 * Path of lines
 * Copyright (C) 2018  Rafael Alceste Berri rafaelberri@gmail.com
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

#include "path.h"


Path::Path()
{
    
}

Path::~Path()
{
    this->Empty();
}

bool Path::parameters()
{
    vector<float> lsize;
    float distTot = 0;
    
    lsize.clear();
    for(linep *ln: linhas)
    {
        Point3f start = ln->Start();
        lsize.push_back(ln->EndDistance(start));
        distTot += lsize[lsize.size() - 1];
    }
    
    lposini.clear();
    lposfim.clear();
    
    float pos = 0;
    
    for(unsigned int i = 0; i < linhas.size(); i++)
    {
        if(i == 0)
            lposini.push_back(0);
        else
            lposini.push_back(pos / distTot);
        
        pos += lsize[i];
        if(i == linhas.size() - 1)
            lposfim.push_back(1);
        else
            lposfim.push_back(pos / distTot);
    }
    
    return true;
}

bool Path::Empty()
{
    for(linep *ln: linhas)
        delete ln;
    linhas.clear();
    
    lposini.clear();
    lposfim.clear();
    
    empty = true;
    
    return true;
}

bool Path::AddPoint(Point3f pt)
{
    if(empty == true)
    {
        start = pt;
        empty = false;
    }
    else
    {
        linep *ln;

        if(linhas.size() == 0)
            ln = new linep(start, pt);
        else
            ln = new linep(linhas[linhas.size() - 1]->End(), pt);

        linhas.push_back(ln);
        
        parameters();
    }
    
    return true;
}

Point3f Path::GetPoint(float parameter)
{
    if(linhas.size() < 1)
        return Point3f();
    
    float p = 0;
    unsigned int sel = 0;
    
    for(sel = 0; sel < linhas.size(); sel++)
    {
        if(lposfim[sel] >= parameter)
        {
            break;
        }
    }
    
    if(sel >= linhas.size())
        sel =  linhas.size() - 1;
    
    p = (parameter - lposini[sel]) / (lposfim[sel] - lposini[sel]);
     
    return linhas[sel]->GetPoint(p);
}

void Path::DispPath()
{
    cout << "qtdLinhas " << linhas.size() << endl;
    for(unsigned int i = 0; i < linhas.size() ; i++)
    {
        cout << "linha[" << i << "] ";
        cout << linhas[i]->Start();
        cout << " " << linhas[i]->End();
        cout << "ini " << lposini[i];
        cout << " fim " << lposfim[i] << endl;
    }
}

