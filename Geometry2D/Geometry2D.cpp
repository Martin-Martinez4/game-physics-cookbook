#include "Geometry2D.h"
#include "Matrix.h"
#include "Vector.h"
#include <climits>
#include <cmath>
#include <cfloat>
#include <iostream>

std::vector<vec2> IShape::GetAxes(){
  std::vector<vec2> axes;

  for(int i = 0; i < vertices.size(); ++i){
    vec2 p1 = vertices[i];
    vec2 p2 = vertices[i + 1 == vertices.size() ? 0 : i +1];

    vec2 edge = p1 - p2;

    // switch the x and y and negate one to get the perpendicular 
    axes.push_back(vec2{-edge.y, edge.x});
  }

  return axes;
}
std::vector<vec2> IShape::GetVertices(){
  return vertices;
};
vec2 IShape::GetCentroid(){
  vec2 vecAcc = vec2(0,0);

  for(int i = 0; i < vertices.size(); ++i){
    vecAcc = vecAcc + vertices[i];
  }

  return vecAcc * (1.f/vertices.size());
};

float Length(const Line2D& line){
  return Magnitude(line.end - line.start);
}

float LengthSq(const Line2D &line){
  return MagnitudeSq(line.end - line.start);
}

// If rectangle is drawn from the middle out; origin at middle to be like
vec2 GetMin(const Rectangle2D& rect){
  vec2 p1 = rect.origin;
  vec2 p2 = rect.origin + rect.size;

  return vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
}
vec2 GetMax(const Rectangle2D& rect){
  vec2 p1 = rect.origin;
  vec2 p2 = rect.origin + rect.size;

  return vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
}

Rectangle2D FromMinMax(const vec2& min, const vec2& max){
  return Rectangle2D(min, min-max);
}

bool PointOnLine(const Point2D& point, const Line2D& line){
  float dy = (line.end.y - line.start.y);
  float dx = (line.end.x - line.start.x);
  float M = dy/dx;

  float B = line.start.y - M*line.start.x;
  return CMP(point.y, M*point.x + B);

}
bool PointInCircle(const Point2D& point, const Circle& circle){
  Line2D line(point, circle.position);
  if(LengthSq(line) < circle.radius*circle.radius){
    return true;
  }
  return false;
}
bool PointInRectangle(const Point2D& point, const Rectangle2D& rectangle){
  vec2 min = GetMin(rectangle);
  vec2 max = GetMax(rectangle);

  return (min.x <= point.x && 
          min.y <= point.y && 
          point.x <= max.x && 
          point.y <= max.y);
}
bool PointInOrientedRectangle(const Point2D& point, const OrientedRectangle& rectangle){
  vec2 rotVector = point - rectangle.position;
  float theta = -DEG2RAD(rectangle.rotation);
  float zRotation2x2[] = {
    cosf(theta), sinf(theta),
    -sinf(theta), cosf(theta)
  };

  Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zRotation2x2, 2, 2);

  Rectangle2D localRectangle(Point2D(), rectangle.halfExtents*2.0f);

  vec2 localPoint = rotVector + rectangle.halfExtents;
  return PointInRectangle(localPoint, localRectangle);
}

bool LineCircle(const Line2D& line, const Circle& circle){
  vec2 ab = line.end - line.start;
  float t = Dot(circle.position - line.start, ab) / Dot(ab, ab);
  
  if(t < 0.0f || t > 1.0f){
    return false;
  }

  Point2D closestPoint = line.start + ab * t;

  Line2D circleToClosest(circle.position, closestPoint);
  return LengthSq(circleToClosest) < circle.radius * circle.radius;
}
bool LineRectangle(const Line2D& line, const Rectangle2D& rectangle){
  // If either end is in the rectangle it intersects
  if(PointInRectangle(line.start, rectangle) || PointInRectangle(line.end, rectangle)){
    return true;
  }

  // raycast to check if line intersects
  vec2 norm = Normalized(line.end - line.start);
  norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;
  norm.y = (norm.y != 0) ? 1.0f / norm.y : 0;

  vec2 min = (GetMin(rectangle) - line.start) * norm;
  vec2 max = (GetMax(rectangle) - line.start) * norm;

  float tmin = fmaxf(
    fminf(min.x, max.x),
    fminf(min.y, max.y)
  );
  float tmax = fminf(
    fmaxf(min.x, max.x),
    fmaxf(min.y, max.y)
  );

  if(tmax < 0 || tmin > tmax){
    return false;
  }

  float t = (tmin < 0.0f) ? tmax : tmin;
  return t > 0.0f && t*t < LengthSq(line);
}
bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle& rectangle){
  float theta = -DEG2RAD(rectangle.rotation);
  float zRotation2x2[] = {
    cosf(theta), sinf(theta),
    -sinf(theta), cosf(theta)
  };
  Line2D localLine;

  vec2 rotVector = line.start - rectangle.position;

  Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zRotation2x2, 2, 2);
  localLine.start = rotVector + rectangle.halfExtents;

  rotVector = line.end - rectangle.position;
  Multiply(rotVector.asArray, vec2(rotVector.x, rotVector.y).asArray, 1, 2, zRotation2x2, 2, 2);
  localLine.end = rotVector + rectangle.halfExtents;

  Rectangle2D localRectangle(Point2D(), rectangle.halfExtents *2.0f);

  return LineRectangle(localLine, localRectangle);

}

bool CircleCircle(const Circle& circle1, const Circle& circle2){
  float radiiSum = circle1.radius + circle2.radius;

  return LengthSq(Line2D(circle1.position, circle2.position)) <= radiiSum*radiiSum;
}

bool CircleRectangle(const Circle& circle, const Rectangle2D& rectangle){
  vec2 min = GetMin(rectangle);
  vec2 max = GetMax(rectangle);

  
  Point2D closestPoint = circle.position;

  // CLAMP(closestPoint.x, min.x, max.x);
  // CLAMP(closestPoint.y, min.y, max.y);

  if(closestPoint.x < min.x){
    closestPoint.x = min.x;
  }else if(closestPoint.x > max.x){
    closestPoint.x = max.x;
  }

  if(closestPoint.y < min.y){
    closestPoint.y = min.y;
  }else if(closestPoint.y > max.y){
    closestPoint.y = max.y;
  }
  Line2D line(circle.position, closestPoint);

// std::cout << "==============\n";
//   std::cout << "min: " << min << "\n";
//   std::cout << "max: " << max << "\n";
//   std::cout << "closest point: " << closestPoint << "\n";

//   std::cout << "line.end: " <<  line.end << "\n";
//   std::cout << "line.start: " <<  line.start << "\n";
//   std::cout << "LengthSq: " <<  LengthSq(line) << "\n";
//   std::cout << "circle.radius: " <<  circle.radius << "\n";
//   std::cout << "circle.position: " <<  circle.position << "\n";

//    std::cout << "verts: " << "\n";
//   std::cout << rectangle.vertices[0] << "\n";
//   std::cout << rectangle.vertices[1] << "\n";
//   std::cout << rectangle.vertices[2] << "\n";
//   std::cout << rectangle.vertices[3] << "\n";
// std::cout << "==============\n";
  return LengthSq(line) <= (circle.radius*circle.radius);
}

bool CircleOrientedRectangle(const Circle& circle, const OrientedRectangle& rectangle){
 vec2 r = circle.position - rectangle.position;
 float theta = -DEG2RAD(rectangle.rotation);

 float zRotation2x2[] = {
  cosf(theta), -sinf(theta),
  sinf(theta), cosf(theta)
 };

 Multiply(r.asArray, vec2(r.x, r.y).asArray, 1, 2, zRotation2x2, 2, 2);

  // float rotatedX = (cosf(theta) * (circle.position.x - rectangle.position.x)) + (sinf(theta) * (circle.position.y - rectangle.position.y));
  // float rotatedY = (cosf(theta) * (circle.position.y - rectangle.position.y)) - (sinf(theta) * (circle.position.x - rectangle.position.x));

  // vec2 r{rotatedX, rotatedY};

  Circle localCircle(r+rectangle.halfExtents, circle.radius);
  Rectangle2D localRect(Point2D(), rectangle.halfExtents*2.0f);

  std::cout << "=========================\n";

  std::cout << "r: " << r << "\n";

  std::cout << "verts: " << "\n";
  std::cout << rectangle.vertices[0] << "\n";
  std::cout << rectangle.vertices[1] << "\n";
  std::cout << rectangle.vertices[2] << "\n";
  std::cout << rectangle.vertices[3] << "\n";

  std::cout << "\nlocal circle center: " << localCircle.position << "\n";
  
  std::cout << "\n";
  std::cout << "local verts: " << "\n";
  std::cout << localRect.vertices[0] << "\n";
  std::cout << localRect.vertices[1] << "\n";
  std::cout << localRect.vertices[2] << "\n";
  std::cout << localRect.vertices[3] << "\n";
  std::cout << "\n";

  std::cout << "=========================\n";


  return CircleRectangle(localCircle, localRect);

}

bool RectangleRectangle(const Rectangle2D& rectangle1, const Rectangle2D& rectangle2){
  vec2 aMin = GetMin(rectangle1);
  vec2 aMax = GetMax(rectangle1);

  vec2 bMin = GetMin(rectangle2);
  vec2 bMax = GetMax(rectangle2);

  bool overX = ((bMin.x <= aMax.x) && (aMin.x <= bMax.x));
  bool overY = ((bMin.y <= aMax.y) && (aMin.y <= bMax.y));

  return overX && overY;
}

// This gets the projection of the shape onto the axis
Interval2D GetInterval(const Rectangle2D& rectangle, const vec2& axis){
  Interval2D result;

  vec2 min = GetMin(rectangle);
  vec2 max = GetMax(rectangle);

  vec2 verts[] = {
    vec2(min.x, min.y), vec2(min.x, max.y),
    vec2(max.x, max.y), vec2(max.x, min.y)
  };

  result.min = result.max = Dot(axis, verts[0]);
  for(int i = 1; i < 4; ++i){
    float projection = Dot(axis, verts[i]);
    if(projection < result.min){
      result.min = projection;
    }
    if(projection > result.max){
      result.max = projection;
    }
  }

  return result;
}
Interval2D GetInterval(const IShape& shape, const vec2& axis){
  Interval2D result;


  result.min = result.max = Dot(axis, shape.vertices[0]);

  // handle circles
  if(shape.vertices.size() == 1){
    const Circle& c = static_cast <const Circle&> (shape);
    result.min= result.min - c.radius;
    result.max = result.max + c.radius;
    return result;
  }

  for(int i = 1; i < shape.vertices.size(); ++i){
    float projection = Dot(axis, shape.vertices[i]);
    if(projection < result.min){
      result.min = projection;
    }
    else if(projection > result.max){
      result.max = projection;
    }
  }

  return result;
}

Interval2D GetInterval(const OrientedRectangle& rectangle, const vec2& axis){
  Rectangle2D r = Rectangle2D{
    Point2D(rectangle.position - rectangle.halfExtents),
    rectangle.halfExtents * 2.0f
  };

  vec2 min = GetMin(r);
  vec2 max = GetMax(r);

  vec2 verts[] = {
    min, max, 
    vec2(min.x, max.y), vec2(max.x, min.y)
  };

  float t = DEG2RAD(rectangle.rotation);
  float zRot[] = {
    cosf(t), sinf(t),
    -sinf(t), cosf(t)
  };

  for(int i = 0; i < 4; ++i){
    vec2 r = verts[i] - rectangle.position;
    Multiply(r.asArray, vec2(r.x , r.y).asArray, 1, 2, zRot, 2, 2);
    verts[i] = r + rectangle.position;
  }

  Interval2D result;
  result.min = result.max = Dot(axis, verts[0]);
  for(int i = 1; i < 4; ++i){
    float proj = Dot(axis, verts[i]);
    if(proj < result.min){
      result.min = proj;
    }
    if(proj > result.max){
      result.max = proj;
    }
  }

  return result;
}

bool OverlapOnAxis(const Rectangle2D& rectangle1, const Rectangle2D& rectangle2, const vec2& axis){
  Interval2D a = GetInterval(rectangle1, axis);
  Interval2D b = GetInterval(rectangle2, axis);

  return ((b.min <= a.max) && (a.min <= b.max));
}
bool OverlapOnAxis(const Rectangle2D& rectangle1, const OrientedRectangle& rectangle2, const vec2& axis){
  Interval2D a = GetInterval(rectangle1, axis);
  Interval2D b = GetInterval(rectangle2, axis);

  return ((b.min <= a.max) && (a.min <= b.max));
}

// bool RectangleRectangleSAT(const Rectangle2D& rectangle1, const Rectangle2D& rectangle2){
//   // x and y axis
//   vec2 axisToTest[] = { vec2(1,0), vec2(0,1) };
//   for(int i = 0; i < 2; ++i){
//     if(!OverlapOnAxis(rectangle1, rectangle2, axisToTest[i])){
//       return false;
//     }

//   }
//   // All intervals overlapped, seperating axis not found
//   return true;
// }
bool RectangleOrientedRectangle(const Rectangle2D& rectangle1, const OrientedRectangle& rectangle2){
  vec2 axisToTest[]{
    vec2(1,0), vec2(0,1),
    vec2(), vec2()
  };

  float t = DEG2RAD(rectangle2.rotation);
  float zRot[] = {
    cosf(t), sinf(t), 
    -sinf(t), cosf(t)
  };

  vec2 axis = Normalized(vec2(rectangle2.halfExtents.x, 0));
  Multiply(axisToTest[2].asArray, axis.asArray, 1, 2, zRot, 2,2);

  axis = Normalized(vec2(0, rectangle2.halfExtents.y));
  Multiply(axisToTest[3].asArray, axis.asArray, 1, 2, zRot, 2,2);

  for(int i = 0; i < 4; ++i){
    if(!OverlapOnAxis(rectangle1, rectangle2, axisToTest[i])){
      return false;
    }
  }

  return true;
}

bool OrientedRectangleOrientedRectangle(const OrientedRectangle& rectangle1, const OrientedRectangle& rectangle2){
  Rectangle2D local1(Point2D(), rectangle1.halfExtents * 2.0f);

  vec2 r = rectangle2.position - rectangle1.position;

  OrientedRectangle local2(rectangle2.position, rectangle2.halfExtents, rectangle2.rotation);
  local2.rotation = rectangle2.rotation - rectangle1.rotation;

  float t = -DEG2RAD(rectangle1.rotation);
  float z[] = {
    cosf(t), sinf(t),
    -sinf(t), cosf(t)
  };

  Multiply(r.asArray, vec2(r.x, r.y).asArray, 1, 2, z, 2, 2);
  local2.position = r + rectangle1.halfExtents;

  return RectangleOrientedRectangle(local1, local2);
}


// not tested might or might not work
bool SATCollision(IShape& shape1, IShape& shape2){
  std::vector<vec2> axes1 = shape1.GetAxes();
  std::vector<vec2> axes2 = shape2.GetAxes();

  if(axes1.size() == 1 || axes2.size() == 1){
    // one is a circle
    if(axes1.size() == 1){
      // There is only one axis for a circle the center point - the other center point.  
      axes1 = {shape1.GetCentroid() - shape2.GetCentroid()};
    }
    if(axes2.size() == 1){
      axes2 = {shape2.GetCentroid() - shape1.GetCentroid()};
    }
  }

  for(int i = 0; i < axes1.size(); ++i){
    Interval2D p1 = GetInterval(shape1, axes1[i]);
    Interval2D p2 = GetInterval(shape2, axes1[i]);

    // ((p2.min <= p1.max) && (p1.min <= p2.max)) looks for overlap
    if(!((p2.min <= p1.max) && (p1.min <= p2.max))){
      return false;
    }
  }

  for(int i = 0; i < axes2.size(); ++i){
    Interval2D p1 = GetInterval(shape1, axes2[i]);
    Interval2D p2 = GetInterval(shape2, axes2[i]);

    // ((p2.min <= p1.max) && (p1.min <= p2.max)) looks for overlap
    if(!((p2.min <= p1.max) && (p1.min <= p2.max))){
      return false;
    }
  }

  return true;
}



