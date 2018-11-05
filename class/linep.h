/*
 * Parametric lines
 * Copyright (C) 2018  Rafael Alceste Berri  rafaelberri@gmail.com
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

#ifndef LINEP_H
#define LINEP_H

#include<opencv2/opencv.hpp>

using namespace cv;

class linep
{
protected:
    Point3f start;
	Point3f velocity;
	Point3f velocityN, velocityNxy, velocityNxz; // normalized in meters or units metrics it uses -- parameter is the distance to start
	
    //float AngleOfTreePointsXZ(Point3f &origin, Point3f &direction1, Point3f &direction2);
public:
    linep(Point3f start, Point3f end);
    Point3f Start();
	float StartDistance(Point3f &point);
	float StartDistanceXY(Point3f &point);
	float StartDistanceXZ(Point3f &point);
	Point3f End();
	float EndDistance(Point3f &point);
	float EndDistanceXY(Point3f &point);
    float EndDistanceXZ(Point3f &point);
	Point3f GetPoint(float parameter);
    Point3f GetPointFromDistStart(float dist);
	Point3f GetPointFromDistEnd(float dist);
	Point3f GetPointFromDistStartXY(float dist);
	Point3f GetPointFromDistStartXZ(float dist);
    Point3f GetPointPerpendicularXZ(float param, float dist);
    float GetDistEndFromParameter(float parameter);
    float GetDistEndFromParameterXY(float parameter);
    float GetDistEndFromParameterXz(float parameter);
    float GetParameterFromDistStart(float dist);
    float GetDistStartFromParameter(float parameter);
    float GetDistStartFromParameterXY(float parameter);
    float GetDistStartFromParameterXZ(float parameter);
    float GetParameterFromX(float x);
    float GetParameterFromY(float y);
    float GetParameterFromZ(float z);
    
    static float Distance(Point3f &pt1, Point3f &pt2);
    
	// Being: 0 - Inline; > 0 left; < 0 Right
	float GetRegionOfPointXY(Point3f &point);
    
	// Being: 0 - Inline; > 0 left; < 0 Right
	float GetRegionOfPointXZ(Point3f &point);
    float GetParameterShorterPointInLineToPoint(Point3f &point);
    float GetParameterShorterPointInLineToPointXY(Point3f &point);
    float GetParameterShorterPointInLineToPointXZ(Point3f & point);
    Point3f GetShorterPointInLineToPoint(Point3f &point);
	Point3f GetShorterPointInLineToPointXY(Point3f &point);
	Point3f GetShorterPointInLineToPointXZ(Point3f &point);
	float GetDistanceToPoint(Point3f &point);
    float GetDistanceToPointXY(Point3f &point);
    float GetDistanceToPointXZ(Point3f &point);
	float GetSegmentDistanceToPoint(Point3f &point);
    float GetSegmentDistanceToPointXY(Point3f &point);
    float GetSegmentDistanceToPointXZ(Point3f &point);
	//float AngleStartToPointXZ(Point3f &point);
    //float AngleEndToPointXZ(Point3f &point);
	//float AngleLinePointToPointXZ(float paramOfBase, Point3f &point);
	//float AngleLineToLine(linep *line);
	//float AngleLineToLineXZ(linep *line);
	//float AngleLineToLineXY(linep *line);

	// Intersection http://gamedev.stackexchange.com/questions/44720/line-intersection-from-parametric-equation
	bool Intersection(linep *line, float *parameter);
	bool IntersectionXY(linep *line, float *parameter);
	bool IntersectionXZ(linep *line, float *parameter);
	bool IntersectionSegment(linep *line, float *parameter);
	bool IntersectionSegmentXY(linep *line, float *parameter);
	bool IntersectionSegmentXZ(linep *line, float *parameter);

	// return: 0 inLine; -1 Left, 1: Right
	int Point2DPositionXZ(Point3f point, float precision = 0.01f);

	// return: 0 inLine; -1 Left, 1: Right
    int Point2DPositionXY(Point3f  &point, float precision = 0.01f);
	
    bool PointsFromDistance2ParamXZ(float parameterPoint, float dist, Point3f * pLeft, Point3f * pRight);
	bool PointsFromDistance2StartXZ(float dist, Point3f * pLeft, Point3f * pRight);
	bool PointsFromDistance2ParamXY(float parameterPoint, float dist, Point3f * pLeft, Point3f * pRight);
	bool PointsFromDistance2StartXY(float dist, Point3f *pLeft, Point3f *pRight);
	bool ParallelLinesXZ(float dist, linep *lineLeft, linep *lineRight);
};

#endif // LINEP_H
