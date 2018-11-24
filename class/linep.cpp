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

#include "linep.h"

// using UnityEngine;
// using System.Collections;

// help http://geomalgorithms.com/a02-_lines.html

linep::linep(cv::Point3f start, cv::Point3f end) {
  this->start = start;
  velocity = (end - start);
  float dist = Distance(start, end);
  if (dist != 0)
    velocityN = velocity / dist;
  else {
    velocityN.x = 0;
    velocityN.y = 0;
    velocityN.z = 0;
  }
  Point3f p1, p2;
  p1.x = start.x;
  p1.y = start.y;
  p1.z = 0;
  p2.x = end.x;
  p2.y = end.y;
  p2.z = 0;
  dist = Distance(p1, p2);
  if (dist != 0)
    velocityNxy = velocity / dist;
  else {
    velocityNxy.x = 0;
    velocityNxy.y = 0;
    velocityNxy.z = 0;
  }
  p1.x = start.x;
  p1.y = 0;
  p1.z = start.z;
  p2.x = end.x;
  p2.y = 0;
  p2.z = end.z;
  dist = Distance(p1, p2);
  if (dist != 0)
    velocityNxz = velocity / dist;
  else {
    velocityNxz.x = 0;
    velocityNxz.y = 0;
    velocityNxz.z = 0;
  }
}

float linep::Distance(Point3f& pt1, Point3f& pt2) {
  Point3f diff = pt1 - pt2;

  if (diff.x == 0 && diff.y == 0 && diff.z == 0) return 0;

  return cv::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}

Point3f linep::Start() { return start; }

float linep::StartDistance(Point3f& point) { return Distance(start, point); }

float linep::StartDistanceXY(Point3f& point) {
  Point3f p1, p2;
  p1.x = start.x;
  p1.y = start.y;
  p1.z = 0;
  p2.x = point.x;
  p2.y = point.y;
  p2.z = 0;
  return Distance(p1, p2);
}

float linep::StartDistanceXZ(Point3f& point) {
  Point3f p1, p2;
  p1.x = start.x;
  p1.y = 0;
  p1.z = start.z;
  p2.x = point.x;
  p2.y = 0;
  p2.z = point.z;
  return Distance(p1, p2);
}

Point3f linep::End() { return GetPoint(1); }

float linep::EndDistance(Point3f& point) {
  Point3f end = End();
  return Distance(end, point);
}

float linep::EndDistanceXY(Point3f& point) {
  Point3f end = End();
  end.z = 0;
  Point3f pt = point;
  pt.z = 0;
  return Distance(end, pt);
}

float linep::EndDistanceXZ(Point3f& point) {
  Point3f end = End();
  end.y = 0;
  Point3f pt = point;
  pt.y = 0;
  return Distance(end, pt);
}

Point3f linep::GetPoint(float parameter) {
  return start + velocity * parameter;
}

Point3f linep::GetPointFromDistStart(float dist) {
  return start + velocityN * dist;
}

Point3f linep::GetPointFromDistStartXY(float dist) {
  return start + velocityNxy * dist;
}

Point3f linep::GetPointFromDistStartXZ(float dist) {
  return start + velocityNxz * dist;
}

Point3f linep::GetPointFromDistEnd(float dist) {
  return End() - velocityN * dist;
}

Point3f linep::GetPointPerpendicularXZ(float param, float dist) {
  Point3f pBase = GetPoint(param);
  int side = (int)((dist > 0) ? 1 : -1);
  dist = dist * side;

  float m1 = (start.z - pBase.z) / (start.x - pBase.x);
  float m2 = -1 / m1;
  float d = dist / cv::sqrt(1.0 + cv::pow(m2, 2));
  Point3f ret;

  // option 1
  ret.x = pBase.x + d;
  ret.z = m2 * (ret.x - pBase.x) + pBase.z;
  ret.y = pBase.y;

  if (Point2DPositionXZ(ret, 0.00001f) == side) return ret;

  // option 2
  ret.x = pBase.x - d;
  ret.z = m2 * (ret.x - pBase.x) + pBase.z;
  ret.y = pBase.y;

  return ret;
}

float linep::GetDistEndFromParameter(float parameter) {
  if (parameter > 1.0)
    parameter = parameter - 1.0;
  else
    parameter = 1.0 - parameter;

  if (cv::abs(velocity.x) > cv::abs(velocity.y)) {
    if (cv::abs(velocity.x) > cv::abs(velocity.z)) {
      return parameter * velocity.x / velocityNxy.x;
    } else {
      return parameter * velocity.z / velocityNxz.z;
    }
  } else {
    if (cv::abs(velocity.y) > cv::abs(velocity.z)) {
      return parameter * velocity.y / velocityNxy.y;
    } else {
      return parameter * velocity.z / velocityNxz.z;
    }
  }
}

float linep::GetDistEndFromParameterXY(float parameter) {
  if (parameter > 1.0)
    parameter = parameter - 1.0;
  else
    parameter = 1.0 - parameter;

  if (cv::abs(velocity.x) > cv::abs(velocity.y)) {
    return parameter * velocity.x / velocityNxy.x;
  } else {
    return parameter * velocity.y / velocityNxy.y;
  }
}

float linep::GetDistEndFromParameterXz(float parameter) {
  if (parameter > 1.0)
    parameter = parameter - 1.0;
  else
    parameter = 1.0 - parameter;

  if (cv::abs(velocity.x) > cv::abs(velocity.z)) {
    return parameter * velocity.x / velocityNxz.x;
  } else {
    return parameter * velocity.z / velocityNxz.z;
  }
}

float linep::GetDistStartFromParameter(float parameter) {
  if (cv::abs(velocity.x) > cv::abs(velocity.y)) {
    if (cv::abs(velocity.x) > cv::abs(velocity.z)) {
      return parameter * velocity.x / velocityNxy.x;
    } else {
      return parameter * velocity.z / velocityNxz.z;
    }
  } else {
    if (cv::abs(velocity.y) > cv::abs(velocity.z)) {
      return parameter * velocity.y / velocityNxy.y;
    } else {
      return parameter * velocity.z / velocityNxz.z;
    }
  }
}

float linep::GetDistStartFromParameterXY(float parameter) {
  if (cv::abs(velocity.x) > cv::abs(velocity.y)) {
    return parameter * velocity.x / velocityNxy.x;
  } else {
    return parameter * velocity.y / velocityNxy.y;
  }
}

float linep::GetDistStartFromParameterXZ(float parameter) {
  if (cv::abs(velocity.x) > cv::abs(velocity.z)) {
    return parameter * velocity.x / velocityNxz.x;
  } else {
    return parameter * velocity.z / velocityNxz.z;
  }
}

float linep::GetParameterFromDistStart(float dist) {
  if (cv::abs(velocity.x) > cv::abs(velocity.y)) {
    if (cv::abs(velocity.x) > cv::abs(velocity.z)) {
      return dist * velocityNxy.x / velocity.x;
    } else {
      return dist * velocityNxz.z / velocity.z;
    }
  } else {
    if (cv::abs(velocity.y) > cv::abs(velocity.z)) {
      return dist * velocityNxy.y / velocity.y;
    } else {
      return dist * velocityNxz.z / velocity.z;
    }
  }
}

float linep::GetParameterFromX(float x) { return (x - start.x) / velocity.x; }

float linep::GetParameterFromY(float y) { return (y - start.y) / velocity.y; }

float linep::GetParameterFromZ(float z) { return (z - start.z) / velocity.z; }

float linep::GetRegionOfPointXY(Point3f& point) {
  float calc =
      (velocity.x * (point.y - start.y) - (velocity.y * (point.x - start.x)));
  if (calc < 0) return -1;
  return 1;
}

float linep::GetRegionOfPointXZ(Point3f& point) {
  float calc =
      (velocity.x * (point.z - start.z) - (velocity.z * (point.x - start.x)));
  if (calc < 0) return -1;
  return 1;
}

float linep::GetParameterShorterPointInLineToPoint(Point3f& point) {
  Point3f w = point - start;

  float c1 = w.dot(velocity);         // Vector3.Dot(w, velocity);
  float c2 = velocity.dot(velocity);  // Vector3.Dot(velocity, velocity);
  return c1 / c2;
}

float linep::GetParameterShorterPointInLineToPointXY(Point3f& point) {
  Point3f pt = point;
  pt.z = 0;

  Point3f p0 = start;
  p0.z = 0;

  Point3f w = pt - p0;

  Point3f v = velocity;
  v.z = 0;

  float c1 = w.dot(v);  // Vector3.Dot(w, v);
  float c2 = v.dot(v);  // Vector3.Dot(v, v);
  return c1 / c2;
}

float linep::GetParameterShorterPointInLineToPointXZ(Point3f& point) {
  Point3f pt = point;
  pt.y = 0;

  Point3f p0 = start;
  p0.y = 0;

  Point3f w = point - p0;

  Point3f v = velocity;
  v.y = 0;

  float c1 = w.dot(v);  // Vector3.Dot(w, v);
  float c2 = v.dot(v);  // Vector3.Dot(v, v);
  return c1 / c2;
}

Point3f linep::GetShorterPointInLineToPoint(Point3f& point) {
  return GetPoint(GetParameterShorterPointInLineToPoint(point));
}

Point3f linep::GetShorterPointInLineToPointXY(Point3f& point) {
  return GetPoint(GetParameterShorterPointInLineToPointXY(point));
}

Point3f linep::GetShorterPointInLineToPointXZ(Point3f& point) {
  return GetPoint(GetParameterShorterPointInLineToPointXZ(point));
}

float linep::GetDistanceToPoint(Point3f& point) {
  Point3f s = GetShorterPointInLineToPoint(point);
  return Distance(point, s);
}

float linep::GetDistanceToPointXY(Point3f& point) {
  Point3f pt = point;
  pt.z = 0;

  Point3f pl = GetShorterPointInLineToPointXY(pt);
  pl.z = 0;

  return Distance(pt, pl);
}

float linep::GetDistanceToPointXZ(Point3f& point) {
  Point3f pt = point;
  pt.y = 0;

  Point3f pl = GetShorterPointInLineToPointXZ(pt);
  pl.y = 0;

  return Distance(pt, pl);
}

float linep::GetSegmentDistanceToPoint(Point3f& point) {
  float param = GetParameterShorterPointInLineToPoint(point);
  Point3f pointSegment;

  if (param < 0) {
    pointSegment = start;
  } else if (param > 1) {
    pointSegment = End();  // end line
  } else {
    pointSegment = GetPoint(param);
  }

  return Distance(point, pointSegment);
}

float linep::GetSegmentDistanceToPointXY(Point3f& point) {
  Point3f pt;
  pt.z = 0;

  float param = GetParameterShorterPointInLineToPointXY(pt);
  Point3f pointSegment;

  if (param < 0) {
    pointSegment = start;
  } else if (param > 1) {
    pointSegment = End();  // end line
  } else {
    pointSegment = GetPoint(param);
  }
  pointSegment.z = 0;

  return Distance(pt, pointSegment);
}

float linep::GetSegmentDistanceToPointXZ(Point3f& point) {
  Point3f pt;
  pt.y = 0;

  float param = GetParameterShorterPointInLineToPointXZ(pt);
  Point3f pointSegment;

  if (param < 0) {
    pointSegment = start;
  } else if (param > 1) {
    pointSegment = End();  // end line
  } else {
    pointSegment = GetPoint(param);
  }
  pointSegment.y = 0;

  return Distance(pt, pointSegment);
}

/*
float linep::AngleOfTreePointsXZ(Point3f& origin, Point3f& direction1, Point3f&
direction2)
{
                float p0c = cv::sqrt(Mathf.Pow(origin.x-direction1.x,2)+
                                           cv::pow(origin.z-direction1.z,2)); //
p0->c (b) float p1c = cv::sqrt(Mathf.Pow(origin.x-direction2.x,2)+
                                           cv::pow(origin.z-direction2.z,2)); //
p1->c (a) float p0p1 = cv::sqrt(Mathf.Pow(direction2.x-direction1.x,2)+
                                            cv::pow(direction2.z-direction1.z,2));
// p0->p1 (c) return cv::acos((p1c*p1c+p0c*p0c-p0p1*p0p1)/(2*p1c*p0c)) *
Mathf.Rad2Deg;
}

public float AngleStartToPointXZ(Vector3 point)
        {
                return AngleOfTreePointsXZ (start, End (), point);
        }

        public float AngleEndToPointXZ(Vector3 point)
        {
                return AngleOfTreePointsXZ (End (), GetPoint(1.5f), point);
        }

        public float AngleLinePointToPointXZ(float paramOfBase, Vector3 point)
        {
                return AngleOfTreePointsXZ (GetPoint(paramOfBase),
GetPoint(paramOfBase + 0.5f), point);
        }

        public float AngleLineToLine(Linep line)
        {
                float ang = Mathf.Acos(Vector3.Dot (velocity, line.velocity) /
(velocity.magnitude * line.velocity.magnitude)) * Mathf.Rad2Deg; if (float.IsNaN
(ang)) ang = 0; return ang;
        }

        public float AngleLineToLineXZ(Linep line)
        {
                float ang = Mathf.Acos(Vector3.Dot (velocityNxz,
line.velocityNxz) / (velocityNxz.magnitude * line.velocityNxz.magnitude)) *
Mathf.Rad2Deg; if (float.IsNaN (ang)) ang = 0; return ang;
        }

        public float AngleLineToLineXY(Linep line)
        {
                float ang = Mathf.Acos(Vector3.Dot (velocityNxy,
line.velocityNxy) / (velocityNxy.magnitude * line.velocityNxy.magnitude)) *
Mathf.Rad2Deg; if (float.IsNaN (ang)) ang = 0; return ang;
        }
*/

// Intersection
// http://gamedev.stackexchange.com/questions/44720/line-intersection-from-parametric-equation
bool linep::Intersection(linep* line, float* parameter) {
  bool retorno = IntersectionSegmentXY(line, parameter);

  if (retorno == false) retorno = IntersectionSegmentXZ(line, parameter);

  if (retorno == false) return false;

  Point3f point = GetPoint(*parameter), pointL;
  float u;
  if (cv::abs(line->velocity.x) > cv::abs(line->velocity.y)) {
    if (cv::abs(line->velocity.x) > cv::abs(line->velocity.z)) {
      u = line->GetParameterFromX(point.x);
    } else {
      u = line->GetParameterFromZ(point.z);
    }
  } else {
    if (cv::abs(line->velocity.y) > cv::abs(line->velocity.z)) {
      u = line->GetParameterFromY(point.y);
    } else {
      u = line->GetParameterFromZ(point.z);
    }
  }

  pointL = GetPoint(u);

  Point3f diff = point - pointL;

  if (cv::abs(diff.x) > 0.00001 || cv::abs(diff.y) > 0.00001 ||
      cv::abs(diff.z) > 0.00001)
    return false;
  return true;
}

bool linep::IntersectionXY(linep* line, float* parameter) {
  try {
    Point3f velocityL = line->velocity;
    Point3f startL = line->start;

    *parameter = (velocityL.x * (start.y - startL.y) +
                  velocityL.y * (startL.x - start.x)) /
                 (velocity.x * velocityL.y - velocity.y * velocityL.x);
    return true;
  } catch (int e) {
    *parameter = -1;
    return false;
  }
}

bool linep::IntersectionXZ(linep* line, float* parameter) {
  try {
    Point3f velocityL = line->velocity;
    Point3f startL = line->start;

    *parameter = (velocityL.x * (start.z - startL.z) +
                  velocityL.z * (startL.x - start.x)) /
                 (velocity.x * velocityL.z - velocity.z * velocityL.x);
    return true;
  } catch (int e) {
    *parameter = -1;
    return false;
  }
}

bool linep::IntersectionSegment(linep* line, float* parameter) {
  bool retorno = Intersection(line, parameter);

  if (retorno == false) return false;

  if (*parameter > 0 && *parameter < 1) {
    Point3f point = GetPoint(*parameter);
    float u;  // = line.GetParameterFromX (point.x);

    if (cv::abs(line->velocity.x) > cv::abs(line->velocity.y)) {
      if (cv::abs(line->velocity.x) > cv::abs(line->velocity.z)) {
        u = line->GetParameterFromX(point.x);
      } else {
        u = line->GetParameterFromZ(point.z);
      }
    } else {
      if (cv::abs(line->velocity.y) > cv::abs(line->velocity.z)) {
        u = line->GetParameterFromY(point.y);
      } else {
        u = line->GetParameterFromZ(point.z);
      }
    }

    if (u >= 0 && u <= 1)
      return true;
    else
      return false;
  } else
    return false;
}

bool linep::IntersectionSegmentXY(linep* line, float* parameter) {
  bool retorno = IntersectionXY(line, parameter);

  if (retorno == false) return false;

  if (*parameter > 0 && *parameter < 1) {
    Point3f point = GetPoint(*parameter);
    float u;  // = line.GetParameterFromX (point.x);

    if (cv::abs(line->velocity.x) > cv::abs(line->velocity.y)) {
      u = line->GetParameterFromX(point.x);
    } else {
      u = line->GetParameterFromY(point.y);
    }

    if (u >= 0 && u <= 1)
      return true;
    else
      return false;
  } else
    return false;
}

bool linep::IntersectionSegmentXZ(linep* line, float* parameter) {
  bool retorno = IntersectionXZ(line, parameter);

  if (retorno == false) return false;

  if (*parameter > 0 && *parameter < 1) {
    Point3f point = GetPoint(*parameter);
    float u;  // = line.GetParameterFromX (point.x);

    if (cv::abs(line->velocity.x) > cv::abs(line->velocity.z)) {
      u = line->GetParameterFromX(point.x);
    } else {
      u = line->GetParameterFromZ(point.z);
    }

    if (u >= 0 && u <= 1)
      return true;
    else
      return false;
  } else
    return false;
}

// return: 0 inLine; -1 Left, 1: Right
int linep::Point2DPositionXZ(Point3f point, float precision) {
  Point3f end = End();
  float factor = 1 / precision;

  int calcPos = (int)(factor * ((end.x - start.x) * (point.z - start.z) -
                                ((end.z - start.z) * (point.x - start.x))));

  if (calcPos > 0)  // left
    return -1;
  else if (calcPos < 0)  // Right
    return 1;
  else
    return 0;
}

// return: 0 inLine; -1 Left, 1: Right
int linep::Point2DPositionXY(Point3f& point, float precision) {
  Point3f end = End();
  float factor = 1 / precision;

  int calcPos = (int)(factor * ((end.x - start.x) * (point.y - start.y) -
                                ((end.y - start.y) * (point.x - start.x))));

  if (calcPos > 0)  // left
    return -1;
  else if (calcPos < 0)  // Right
    return 1;
  else
    return 0;
}

bool linep::PointsFromDistance2ParamXZ(float parameterPoint, float dist,
                                       Point3f* pLeft, Point3f* pRight) {
  Point3f end = End();
  Point3f pBase = GetPoint(parameterPoint);
  Point3f ret;

  pLeft->x = pLeft->y = pLeft->z = 0;
  pRight->x = pRight->y = pRight->z = 0;

  float m1 = 0;
  if ((start.x - pBase.x) != 0) m1 = (start.z - pBase.z) / (start.x - pBase.x);

  if (m1 == 0) m1 = 0.01f;

  float m2 = -1 / m1;
  float d = dist / cv::sqrt(1 + cv::pow(m2, 2));

  // option 1
  ret.x = pBase.x + d;
  ret.z = m2 * (ret.x - pBase.x) + pBase.z;
  ret.y = pBase.y;

  if (Point2DPositionXZ(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  // option 2
  ret.x = pBase.x - d;
  ret.z = m2 * (ret.x - pBase.x) + pBase.z;
  ret.y = pBase.y;

  if (Point2DPositionXZ(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  return true;
}

bool linep::PointsFromDistance2ParamXY(float parameterPoint, float dist,
                                       Point3f* pLeft, Point3f* pRight) {
  Point3f end = End();
  Point3f pBase = GetPoint(parameterPoint);
  Point3f ret;

  pLeft->x = pLeft->y = pLeft->z = 0;
  pRight->x = pRight->y = pRight->z = 0;

  float m1;

  if ((start.x - pBase.x) != 0) m1 = (end.y - start.y) / (end.x - start.x);

  if (m1 == 0) m1 = 0.01f;

  float m2 = -1 / m1;
  float d = dist / cv::sqrt(1 + cv::pow(m2, 2));

  // option 1
  ret.x = start.x + d;
  ret.y = m2 * (ret.x - start.x) + start.y;
  ret.y = start.z;

  if (Point2DPositionXY(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  // option 2
  ret.x = start.x - d;
  ret.y = m2 * (ret.x - start.x) + start.y;
  ret.z = start.z;

  if (Point2DPositionXY(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  return true;
}

bool linep::PointsFromDistance2StartXY(float dist, Point3f* pLeft,
                                       Point3f* pRight) {
  Point3f end = End();
  Point3f ret;

  pLeft->x = pLeft->y = pLeft->z = 0;
  pRight->x = pRight->y = pRight->z = 0;

  float m1;
  if ((end.x - start.x) != 0) m1 = (end.y - start.y) / (end.x - start.x);

  if (m1 == 0) m1 = 0.01f;

  float m2 = -1 / m1;
  float d = dist / cv::sqrt(1 + cv::pow(m2, 2));

  // option 1
  ret.x = start.x + d;
  ret.y = m2 * (ret.x - start.x) + start.y;
  ret.z = start.z;

  if (Point2DPositionXY(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  // option 2
  ret.x = start.x - d;
  ret.y = m2 * (ret.x - start.x) + start.y;
  ret.z = start.z;

  if (Point2DPositionXY(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  return true;
}

bool linep::PointsFromDistance2StartXZ(float dist, Point3f* pLeft,
                                       Point3f* pRight) {
  Point3f end = End();
  Point3f ret;

  pLeft->x = pLeft->y = pLeft->z = 0;
  pRight->x = pRight->y = pRight->z = 0;

  float m1;
  if ((end.x - start.x) != 0) m1 = (end.z - start.z) / (end.x - start.x);

  if (m1 == 0) m1 = 0.01f;

  float m2 = -1 / m1;
  float d = dist / cv::sqrt(1 + cv::pow(m2, 2));

  // option 1
  ret.x = start.x + d;
  ret.z = m2 * (ret.x - start.x) + start.z;
  ret.y = start.y;

  if (Point2DPositionXZ(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  // option 2
  ret.x = start.x - d;
  ret.z = m2 * (ret.x - start.x) + start.z;
  ret.y = start.y;

  if (Point2DPositionXZ(ret) == -1)  // left
    *pLeft = ret;
  else  // Right
    *pRight = ret;

  return true;
}

bool linep::ParallelLinesXZ(float dist, linep* lineLeft, linep* lineRight) {
  Point3f pl1, pl2, pr1, pr2;

  PointsFromDistance2StartXZ(dist, &pl1, &pr1);
  PointsFromDistance2ParamXZ(1.0, dist, &pl2, &pr2);

  lineLeft = new linep(pl1, pl2);
  lineRight = new linep(pr1, pr2);

  return true;
}

/*

        public bool ParallelLinesXZ(float dist, out Linep lineLeft, out Linep
   lineRight)
        {
        }
*/
