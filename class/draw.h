/*
    Funções para auxiliar o desenho em OPENCV
    Copyright (C) 2013  Rafael Alceste Berri rafaelberri@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef DRAW_H
#define DRAW_H

#include<opencv2/opencv.hpp>
#include<string>

using namespace cv;
using namespace std;

class draw
{
public:
  static bool line(Mat *img, Point start, Point end, Scalar color = Scalar::all(255), int thickness = 2, int lineType = 8);
  
  static bool rectangle(Mat *img, Point pIni, Point pFim, unsigned int borda, Scalar borderColor);
  static bool rectangle(Mat *img, Point pIni, Point pFim, unsigned int borda, Scalar fillColor, Scalar borderColor);
  static bool rectangle(Mat* img, Rect regiao, unsigned int borda, Scalar borderColor);
  static bool rectangle(Mat* img, Rect regiao, unsigned int borda, Scalar fillColor, Scalar color);
  static bool triangle(Mat *img, Point p1, Point p2, Point p3, Scalar color, int lineType=8, int shift=0);
  
  static bool circle(Mat* img, Point center, int radius = 10, Scalar color = Scalar::all(255), int thickness=-1, int lineType=8, int shift=0);
  
  static bool text(string text, Mat* img, Point posicao, Scalar color = Scalar::all(255), double fontScale = 2, int fontFace = FONT_HERSHEY_COMPLEX_SMALL, int thickness = 0, bool box = false, Scalar boxColor = Scalar::all(0));
  static bool textCenter(string text, Mat* img, Point center, Scalar color = Scalar::all(255), double fontScale = 2, int fontFace = FONT_HERSHEY_COMPLEX_SMALL, int thickness = 0, bool box = false, Scalar boxColor = Scalar::all(0));
  
  static Mat CutImgBySeg(Mat *img, Mat *segmentation);

  // Mat
  static void redim(Mat *img, double factor);
  static void redim(Mat *img, unsigned int dimMax);
  static void redim(Mat *img, unsigned int width, unsigned int height);
};

#endif // DRAW_H
