#include "raylib.h"
#include "Body.h"
#include "Geometry2D.h"
#include <iostream>

int main(){

  const int winWidth{920};
  const int winHeight{640};
  InitWindow(winWidth, winHeight, "Test");


  SetTargetFPS(60);

  Circle& c1 = Circle(vec2(0, winHeight/2), 100);
  Circle& c2 = Circle(vec2(winWidth, winHeight/2), 40);

  Body b1 = Body(c1, vec2(.5,0), vec2(.1,0), 10);
  Body b2 = Body(c2, vec2(-.5, .05), vec2(-.1,0), 4);

  while(!WindowShouldClose()){
    BeginDrawing();
    CollisionData cd = SATCollision(b1.shape, b2.shape);

    if(cd.collided){

      DrawCircle(b1.shape.GetCentroid().x, b1.shape.GetCentroid().y, b1.mass*10, YELLOW);
      DrawCircle(b2.shape.GetCentroid().x, b2.shape.GetCentroid().y, b2.mass*10, ORANGE);  

      float invMass = (1/b1.mass + 1/b2.mass);

      b1.ApplyForce((cd.axis * -2 * Dot(b1.velocity - b2.velocity, cd.axis)) * (1/invMass));
      b2.ApplyForce((cd.axis * 2 * Dot(b1.velocity - b2.velocity, cd.axis))* (1/invMass));

    }else{

      DrawCircle(b1.shape.GetCentroid().x, b1.shape.GetCentroid().y, b1.mass*10, GRAY);
      DrawCircle(b2.shape.GetCentroid().x, b2.shape.GetCentroid().y, b2.mass*10, BLACK);  
    }

    b1.Update(1);
    b2.Update(1);


    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
