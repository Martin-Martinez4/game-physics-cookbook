#ifndef BVH_H_
#define BVH_H_

#include "Geometry2D.h"
#include <vector>
#include <tuple>


const unsigned int MAXDEPTH = 10;



class BVHNode{
public:

  BVHNode(){};
  BVHNode(int shapeIndex):shapeIndex(shapeIndex){};

  int shapeCount = 0;
  int shapeIndex = 0;
  Rectangle2D aabb;
  BVHNode* left = nullptr;
  BVHNode* right = nullptr;

};

void split(BVHNode& parent, int depth, std::vector<IShape> &shapes);

BVHNode* createTree(std::vector<IShape> boxes);

void findCollisions(int boxId, IShape& box, BVHNode* node, std::vector<IShape&> boxes, std::vector<CollisionData> &cd);

#endif