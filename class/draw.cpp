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


#include "draw.h"

bool draw::line ( Mat* img, Point start, Point end, Scalar color, int thickness, int lineType )
{ 
  cv::line(*img, start, end, color, thickness, lineType);
  
  return true;
}

bool draw::rectangle ( Mat* img, Point pIni, Point pFim, unsigned int borda, Scalar borderColor )
{
  Rect regiao(pIni, pFim);
  
  rectangle(img, regiao, borda, borderColor);
}

bool draw::rectangle(Mat* img, Point pIni, Point pFim, unsigned int borda, Scalar fillColor, Scalar borderColor )
{
  Rect regiao(pIni, pFim);
  
  rectangle(img, regiao, borda, fillColor, borderColor);
  
  /*
  // fundo
  cv::rectangle( *img,
                pIni,
                pFim,
                fillColor, 
                -borda,
                0 );
  
  if(borda > 0)
    cv::rectangle( *img,
	           pIni,
	           pFim,
	           borderColor,
	           borda,
	           0 );
  */
  
  return true;
}

bool draw::rectangle ( Mat* img, Rect regiao, unsigned int borda, Scalar borderColor )
{
  cv::rectangle( *img, 
	         regiao,
	         borderColor,
	         (int)borda,
	         0 );
}

bool draw::rectangle(Mat* img, Rect regiao, unsigned int borda, Scalar fillColor, Scalar borderColor )
{
  Rect regiaoFill = regiao;
  
  if(borda > 0)
  {
    rectangle( img, 
	       regiao,
	       borda,
	       borderColor);
    
    // tirar a borda do preenchimento
    regiaoFill.x += (int)borda; 
    regiaoFill.width -= 2 * (int)borda;
    regiaoFill.y += (int)borda;
    regiaoFill.height -= 2 * (int)borda;
  }
    
  // fundo
  cv::rectangle( *img,
                 regiaoFill,
                 fillColor, 
                 CV_FILLED, // faz preenchimento
                 0 );
  
  return true;
}

bool draw::triangle(Mat *img, Point p1, Point p2, Point p3, Scalar color, int lineType, int shift)
{
  Point pts[3];
  pts[0] = p1;
  pts[1] = p2;
  pts[2] = p3;

  cv::fillConvexPoly(*img, pts, 3, color, lineType, shift);
  
  return true;
}

bool draw::circle ( Mat* img, Point center, int radius, Scalar color, int thickness, int lineType, int shift )
{
  cv::circle(*img, center, radius, color, thickness, lineType, shift);
}


bool draw::text ( string text, Mat* img, Point posicao, Scalar color, double fontScale, int fontFace, int thickness, bool box, Scalar boxColor )
{ 
  if(box)
  { 
    int baseline=0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    
    Point ptBox1(posicao.x - thickness, posicao.y - thickness), ptBox2(posicao.x + textSize.width + thickness, posicao.y + textSize.height + thickness);

    // draw the box
    draw::rectangle(img, ptBox1, ptBox2, 0, boxColor, boxColor);
  }
  
  // then put the text itself
  putText(*img, text, posicao, fontFace, fontScale, color, thickness, 8);
}

bool draw::textCenter ( string text, Mat* img, Point center, Scalar color, double fontScale, int fontFace, int thickness, bool box, Scalar boxColor )
{
  int baseline=0;
  Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);

  // center the text
  Point textPos(center.x - textSize.width/2,
		center.y + textSize.height/2);
  
  draw::text( text, img, textPos, color, fontScale, fontFace, thickness, box, boxColor);
}


Mat draw::CutImgBySeg ( Mat* img, Mat* segmentation )
{
  Mat retorno = Mat::zeros(img->size(), img->type());
  img->copyTo(retorno, *segmentation);
  
  return retorno;
}

void dimnova(unsigned int *width, unsigned int *height, unsigned int dimMax)
{
  if(*width > *height)
  {
    *height = (unsigned int) ((float) dimMax * ((float)(*height) / (float)(*width)) + 0.5);
    *width = dimMax;
  }
  else
  {
    *width = (unsigned int) ((float) dimMax * ((float)(*width) / (float)(*height)) + 0.5);
    *height = dimMax;
  }
}

void draw::redim(Mat *img, double factor)
{
  unsigned int width, height;
  
  width = img->cols * factor;
  height = img->rows * factor;
  
  // nao redimensiona para tamanho maior
  if(width < img->cols && height < img->rows)
    redim(img, width, height);
}


void draw::redim(Mat *img, unsigned int dimMax)
{
  unsigned int width, height;
  
  width = img->cols;
  height = img->rows;

  dimnova(&width, &height, dimMax);
  
  // nao redimensiona para tamanho maior
  if(width < img->cols && height < img->rows)
    redim(img, width, height);
}

void draw::redim(Mat *img, unsigned int width, unsigned int height)
{ 
  if(width == 0 || height == 0)
    return;
  
  resize(*img, *img, Size(width, height), 0, 0, cv::INTER_LINEAR);
}
