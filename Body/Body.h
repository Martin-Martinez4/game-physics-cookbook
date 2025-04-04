
#ifndef BODY_BODY_H_
#define BODY_BODY_H_

#include "Vector.h"
#include "Geometry2D.h"
#include <cstdint>

class Body{
public:
  Body::Body(IShape& shape, vec2 velocity = vec2{0,0}, vec2 acceleration = vec2{0,0}, float mass = 10.f);
  Body::Body(IShape& shape, float mass);

  IShape& shape;

  void ApplyForce(vec2 force);
  void Update(double dt);

  vec2 position;
  vec2 velocity;
  vec2 acceleration;
  
  float angle = 0.f;
  float anglularVelocity = 0.f;
  float angularAcceleration = 0.f;

  float mass = 1;
  float radius = mass * 16;
  float energyConservationRate = 0.75;

};

#endif


