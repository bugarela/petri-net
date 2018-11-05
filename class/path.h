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

#ifndef PATH_H
#define PATH_H

#include "linep.h"
#include <vector>

using namespace std;

// cria uma sequência de linhas como sendo um único caminho (entre 0 e 1)

class Path
{
protected:
   vector<linep *> linhas;
   vector<float> lposini, lposfim;
   Point3f start;
   bool empty = true;
   
   bool parameters();
public:
    Path();
    ~Path();
    
    bool Empty();
       
    bool AddPoint(Point3f pt);
    Point3f GetPoint(float parameter);
    void DispPath();
};

#endif // PATH_H
