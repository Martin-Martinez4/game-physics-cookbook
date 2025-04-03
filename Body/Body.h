
#ifndef BODY_BODY_H_
#define BODY_BODY_H_

#include "raylib.h"
#include <cstdint>
#include "Vector.h"
#include <vector>
class Body{
public:
  Body(vec2 position = vec2{0,0}, vec2 velocity = vec2{0,0}, vec2 acceleration = vec2{0,0}, float mass = 10.f, Color color = RED);
  Body(vec2 position = vec2{0,0},  float mass = 2.f, Color color = RED);
  
  void ApplyForce(vec2 force);
  void Update(double dt);
  void Draw();


  vec2 position;
  vec2 velocity;
  vec2 acceleration;
  
  float angle = 0.f;
  float anglularVelocity = 0.f;
  float angularAcceleration = 0.f;

  float mass = 1;
  float radius = mass * 16;
  float energyConservationRate = 0.75;

  Color color;

  std::vector<Body*> attractedBodies{};
};

#endif


