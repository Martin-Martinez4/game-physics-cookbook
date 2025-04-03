#ifndef BVH_H_
#define BVH_H_

#include "Geometry2D.h"
#include <vector>
#include <tuple>


const unsigned int MAXDEPTH = 10;

void split(BVHNode& parent, int depth = 0, std::vector<IShape> &shapes);

int getSplitPos(int begin, int end);

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

BVHNode* createTree(std::vector<IShape> boxes);

void findCollisions(int boxId, IShape& box, BVHNode* node, std::vector<IShape&> boxes, std::vector<CollisionData> &cd);

#endif