#ifndef BVH_H_
#define BVH_H_

#include "Geometry2D.h"
#include <vector>
#include <tuple>

// Credit: https://github.com/matthias-research/pages/blob/master/tenMinutePhysics/24-morton.html

uint64_t split(uint64_t x, int log_bits);

uint64_t encode(uint64_t x, uint64_t y, uint64_t z, int log_bits);

unsigned short int expandBits(int v);
float normalizeCoord(float val, int worldSize);
unsigned short int calculateMortonCode(float x, float y, float z, int worldSize);
int getSplitPos(int begin, int end);

class BVHNode{
public:
  BVHNode():boxId{-1}{};
  BVHNode(int boxId, Rectangle2D aabb):boxId{boxId}, aabb{aabb}{}; 

  bool IsLeaf(){
    return boxId != -1;
  }
  Rectangle2D aabb;
  int boxId;
  BVHNode* left;
  BVHNode* right;

};

BVHNode* createSubTree(std::vector<std::tuple<int, unsigned short int>> nodes, int begin, int end, std::vector<IShape> boxes);

// shape id are just an index
BVHNode* createTree(std::vector<IShape> shapes, int worldSize);

void findCollisions(int boxId, IShape& box, BVHNode* node, std::vector<IShape&> boxes, std::vector<CollisionData> &cd);

#endif