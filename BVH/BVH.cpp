#include "BVH.h"
#include <tuple>
#include <algorithm>

/* 
Start with a root node encompassing all objects.
If the number of objects in a node exceeds a threshold, split the node.
Calculate the AABB of the node's objects.
Choose a splitting axis (e.g., longest axis of the AABB).
Partition objects based on their position relative to the splitting plane/line.
Create two child nodes and recursively build the BVH for each child.
*/
void split(BVHNode& parent, int depth = 0, std::vector<IShape> &shapes) {

  if(depth >= MAXDEPTH || parent.shapeCount <= 1){
    return;
  }

  // Can use index becuase of the way the book created vectors, which is cool
  int splitAxis =  parent.aabb.size.x > parent.aabb.size.y ? 0 : 1;
  float splitPosition = parent.aabb.GetCentroid()[splitAxis];

  BVHNode* child1 = new BVHNode(parent.shapeIndex);
  BVHNode* child2 = new BVHNode(parent.shapeIndex);

  for(int i = parent.shapeIndex; i < parent.shapeIndex + parent.shapeCount; ++i){
    bool isOnSide1 = shapes[i].GetCentroid()[splitAxis] < splitPosition;

    if(isOnSide1){
      // grow child a aabb to include shape
      child1->shapeCount++;
    }else{
      // grow child b aabb to include shape 
      child2->shapeCount++;

    }

    if(isOnSide1){
      int swap = child1->shapeIndex + child1->shapeCount - 1;
      std::swap(shapes[swap], shapes[i]);
      child2->shapeCount++;
    }
  }


  split(*child1, depth + 1, shapes);
  split(*child2, depth + 1, shapes);

}



int getSplitPos(int begin, int end){
  return floor((begin + end) / 2);
}



BVHNode* createTree(std::vector<IShape> boxes, vec2 worldSize){
  // Create parent node with biggest aabb
  // call split
  // return created node
 
}

void findCollisions(int boxId, IShape box, BVHNode* node, std::vector<IShape> boxes, std::vector<CollisionData> &cd){
  
}