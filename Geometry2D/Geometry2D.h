#ifndef GEOMETRY2D_GEMOMETRY2D_H_
#define GEOMETRY2D_GEMOMETRY2D_H_

#include "Vector.h"

typedef vec2 Point2D;

typedef struct Line2D {
  Point2D start;
  Point2D end;

  inline Line2D(){}
  inline Line2D(const Point2D& s, const Point2D& e): start(s), end(e){}

} Line2D;

float Length(const Line2D& line);
float LengthSq(const Line2D& line);

typedef struct Circle{
  Point2D position;
  float radius;

  inline Circle(): radius(1.0f){}
  inline Circle(const Point2D& position, float radius): position(position), radius(radius){}

} Circle;

typedef struct Rectangle2D{
  Point2D origin;
  vec2 size;

  inline Rectangle2D(): size(1,1){}
  inline Rectangle2D(const Point2D& origin, const vec2& size): origin(origin), size(size){}
} Rectangle2D;

vec2 GetMin(const Rectangle2D& rect);
vec2 GetMax(const Rectangle2D& rect);

Rectangle2D FromMinMax(const vec2& min, const vec2& max);

typedef struct OrientedRectangle{
  Point2D position;
  vec2 halfExtents;
  float rotation;

  inline OrientedRectangle(): halfExtents(1.0f, 1.0f), rotation(0.0f){}
  inline OrientedRectangle(const Point2D& position, const vec2& halfExtents): position(position), halfExtents(halfExtents), rotation(0.0f){}
  inline OrientedRectangle(const Point2D& position, const vec2& halfExtent, float rotation): position(position), halfExtents(halfExtent), rotation(rotation){}

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

#endif