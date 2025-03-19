#ifndef GEOMETRY2D_GEMOMETRY2D_H_
#define GEOMETRY2D_GEMOMETRY2D_H_

#include "Matrix.h"
#include <cmath>
#include <vector>

typedef vec2 Point2D;

struct IShape{
public:
  IShape(){}
  IShape(std::vector<vec2> vertices): vertices{vertices}{}

  std::vector<vec2> GetVertices();
  vec2 GetCentroid();
  std::vector<vec2> GetAxes();

  std::vector<vec2> vertices;
};

typedef struct Line2D: public IShape {
  Point2D start;
  Point2D end;

  inline Line2D(): IShape::IShape(std::vector<vec2>{vec2(0,0), vec2(0,0)}){}
  inline Line2D(const Point2D& s, const Point2D& e): IShape::IShape(std::vector<vec2>{s,e}), start(s), end(e){}

} Line2D;

float Length(const Line2D& line);
float LengthSq(const Line2D& line);

typedef struct Circle: public IShape{
  Point2D position;
  float radius;

  inline Circle(): IShape::IShape(std::vector<vec2>{vec2(0,0)}), radius(1.0f){}
  inline Circle(const Point2D& position, float radius): IShape::IShape(std::vector<vec2>{position}), position(position), radius(radius){}

} Circle;

typedef struct Rectangle2D: public IShape{
  Point2D origin;
  vec2 size;

  inline Rectangle2D(): IShape::IShape(), size(1,1){
    vertices = {
      origin + vec2{-size.x * .5f, size.y *.5f},
      origin + (size * .5f),
      origin + vec2{size.x * .5f, -size.y *.5f},
      origin - (size * .5f),
    };
  }
  inline Rectangle2D(const Point2D& origin, const vec2& size): IShape::IShape(), origin(origin), size(size){
    vertices = {
        origin + vec2{-size.x * .5f, size.y *.5f},
      origin + (size * .5f),
      origin + vec2{size.x * .5f, -size.y *.5f},
      origin - (size * .5f),
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
      cosf(rads), -sinf(rads),
      sinf(rads), cosf(rads)
    };

    vertices = {
      MultiplyVector(rotMat, position + vec2{-halfExtents.x, halfExtents.y}),
      MultiplyVector(rotMat, (position + halfExtents)),
      MultiplyVector(rotMat, position + vec2{halfExtents.x, -halfExtents.y}),
      MultiplyVector(rotMat, (position - halfExtents)),
    };
  }

} OrientedRectangle;

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

bool RectangleRectangleSAT(const Rectangle2D& rectangle1, const Rectangle2D& rectangle2);
bool RectangleOrientedRectangle(const Rectangle2D& rectangle1, const OrientedRectangle& rectangle2);

bool OrientedRectangleOrientedRectangle(const OrientedRectangle& rectangle1, const OrientedRectangle& rectangle2);

bool SATCollision(IShape& shape1, IShape& shape2);

#endif