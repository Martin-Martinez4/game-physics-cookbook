#ifndef GEOMETRY2D_GEMOMETRY2D_H_
#define GEOMETRY2D_GEMOMETRY2D_H_

#include "Matrix.h"
#include <cmath>
#include <vector>

typedef vec2 Point2D;

//  point in any shape 
/*
rayEdgeIntersect(rayOrigin, rayDirection, edgePoint1, edgePoint2){
  edgeVector = (edgePoint1, edgePoint2);

  if(cross(ray, edgeVector).length is 0){
    means parallel no intersection
    return false
  }

  let t = dot(edgePoint1 - rayOrigin, cross(rayDirection, edgeVector)) / dot(rayDirection, cross(edgeVector, rayDirection));

   if (t < 0) {
        return false; // No intersection
    }

    // Calculate the intersection point
    let intersectionPoint = add(rayOrigin, multiply(rayDirection, t));

    // Check if the intersection point is on the edge segment
    let s = dot(intersectionPoint - edgePoint1, edgeVector) / dot(edgeVector, edgeVector);
    if (s < 0 || s > 1) {
        return false; // No intersection
    }

    return intersectionPoint; // Intersection point
}
*/


struct IShape{
public:
  IShape(){}
  IShape(std::vector<vec2> vertices): vertices{vertices}{}

  std::vector<vec2> GetVertices();
  vec2 GetCentroid() const;
  std::vector<vec2> GetAxes();

  std::vector<vec2> vertices;
};


bool PointInPolygon(std::vector<vec2> verts, Point2D point);
typedef struct Line2D: public IShape {
  Point2D start;
  Point2D end;

  inline Line2D(): IShape::IShape(std::vector<vec2>{vec2(0,0), vec2(0,0)}){}
  inline Line2D(const Point2D& s, const Point2D& e): IShape::IShape(std::vector<vec2>{s,e}), start(s), end(e){}

} Line2D;

float Length(const Line2D& line);
float LengthSq(const Line2D& line);

typedef struct Circle: public IShape{
  inline Circle(): IShape::IShape(std::vector<vec2>{vec2(0,0)}), radius(1.0f), position(0,0){}
  inline Circle(const Point2D& position, float radius): IShape::IShape(std::vector<vec2>{position}), position(position), radius(radius){}

  Point2D position;
  float radius;


} Circle;

typedef struct Rectangle2D: public IShape{
  Point2D origin;
  vec2 size;

  inline Rectangle2D(): IShape::IShape(), size(1,1){
     vertices = {
      origin,
      origin + vec2{0, size.y},
      origin + size,
      origin + vec2(size.x, 0),
    };
  }
  inline Rectangle2D(const Point2D& origin, const vec2& size): IShape::IShape(), origin(origin), size(size){
    vertices = {
      origin,
      origin + vec2{0, size.y},
      origin + size,
      origin + vec2(size.x, 0),
    };
  }
} Rectangle2D;

vec2 GetMin(const Rectangle2D& rect);
vec2 GetMax(const Rectangle2D& rect);

Rectangle2D FromMinMax(const vec2& min, const vec2& max);

typedef struct OrientedRectangle: public IShape{
  Point2D position;
  vec2 halfExtents;
  float rotation;

  OrientedRectangle(): halfExtents(1.0f, 1.0f), rotation(0.0f){

    vertices = {
      position + vec2{-halfExtents.x, halfExtents.y},
      (position + halfExtents),
      position + vec2{halfExtents.x, -halfExtents.y},
      (position - halfExtents),
    };
  }

  OrientedRectangle(const Point2D& position, const vec2& halfExtents): IShape::IShape(), position(position), halfExtents(halfExtents), rotation(0.0f){

    vertices = {
      position + vec2{-halfExtents.x, halfExtents.y},
      (position + halfExtents),
      position + vec2{halfExtents.x, -halfExtents.y},
      (position - halfExtents),
    };
  }

  OrientedRectangle(const Point2D& position, const vec2& halfExtent, float rotation): IShape::IShape(), position(position), halfExtents(halfExtent), rotation(rotation){

    float rads = DEG2RAD(rotation);
    mat2 rotMat {
      cosf(rads), sinf(rads),
      -sinf(rads), cosf(rads)
    };
    mat2 negRotMat {
      cosf(-rads), sinf(-rads),
      -sinf(-rads), cosf(-rads)
    };

    vec2 pos; 
    Multiply(pos.asArray,position.asArray, 1,2,negRotMat.asArray, 2, 2);


    vec2 v1;
    Multiply(v1.asArray,( pos + vec2{-halfExtents.x, halfExtents.y}).asArray, 1,2,rotMat.asArray, 2, 2);
    vec2 v2;
    Multiply(v2.asArray, (pos + halfExtents).asArray, 1,2,rotMat.asArray, 2, 2);
    vec2 v3;
    Multiply(v3.asArray, ( pos + vec2{halfExtents.x, -halfExtents.y}).asArray, 1,2,rotMat.asArray, 2, 2);
    vec2 v4;
    Multiply(v4.asArray, (pos - halfExtents).asArray, 1,2,rotMat.asArray, 2, 2);

    vertices = {
      // MultiplyVector(rotMat,( position + vec2{-halfExtents.x, halfExtents.y})),
      v1,
      v2,
      v3,
      v4
      // MultiplyVector(rotMat, (position + halfExtents)),
      // MultiplyVector(rotMat,( position + vec2{halfExtents.x, -halfExtents.y})),
      // MultiplyVector(rotMat, (position - halfExtents)),
    };
  }

} OrientedRectangle;

typedef struct BoundingShape{

  BoundingShape(std::vector<IShape> shapes): shapes(shapes){};

  std::vector<IShape> shapes;


} BoundingShape;

bool PointOnLine(const Point2D& point, const Line2D& line);
bool PointInCircle(const Point2D& point, const Circle& circle);
bool PointInRectangle(const Point2D& point, const Rectangle2D& rectangle);
bool PointInOrientedRectangle(const Point2D& point, const OrientedRectangle& rectangle);

bool LineCircle(const Line2D& line, const Circle& circle);
bool LineRectangle(const Line2D& line, const Rectangle2D& rectangle);
bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle& rectangle);

bool CircleCircle(const Circle& circle1, const Circle& circle2);
bool CircleRectangle(const Circle& circle, const Rectangle2D& rectangle);
bool CircleOrientedRectangle(const Circle& circle, const OrientedRectangle& rectangle);

bool RectangleRectangle(const Rectangle2D& rectangle1, const Rectangle2D& rectangle2);

typedef struct Interval2D{
  float min;
  float max;
} Interval2D;

Interval2D GetInterval(const Rectangle2D& rectangle, const vec2& axis);
Interval2D GetInterval(const IShape& shape, const vec2& axis);
Interval2D GetInterval(const OrientedRectangle& rrectangle1, const vec2& axis);

bool OverlapOnAxis(const Rectangle2D& rectangle1, const Rectangle2D& rectangle2, const vec2& axis);
bool OverlapOnAxis(const Rectangle2D& rectangle1, const OrientedRectangle& rectangle2, const vec2& axis);

// bool RectangleRectangleSAT(const Rectangle2D& rectangle1, const Rectangle2D& rectangle2);
bool RectangleOrientedRectangle(const Rectangle2D& rectangle1, const OrientedRectangle& rectangle2);

bool OrientedRectangleOrientedRectangle(const OrientedRectangle& rectangle1, const OrientedRectangle& rectangle2);

bool SATCollision(IShape& shape1, IShape& shape2);

Circle ContainingCircle(const IShape& shape);

Rectangle2D ContainingRectangle(const IShape& shape);

bool PointInShape(const BoundingShape& boundingShape, const Point2D& point);

// boundingShape to shape; SATCollision between all shapes in boundingShape and the singular shape
// boundShape to boundingShape; SATCollision between all shapes in one then all shapes in the other.  

#endif