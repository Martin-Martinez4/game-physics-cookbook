#include "BVH.h"
#include <tuple>

unsigned short int expandBits(int v){
    v = (v * 0x00010001) & 0xFF0000FF;
    v = (v * 0x00000101) & 0x0F00F00F;
    v = (v * 0x00000011) & 0xC30C30C3;
    v = (v * 0x00000005) & 0x49249249;
    return v;
}

// Only square world size?
// Matbe if it was a vec3 the world could be not square?
float normalizeCoord(float val, int worldSize){
  return (val + worldSize/2) / worldSize;
}

unsigned short int calculateMortonCode(float x, float y, float z, int worldSize){
  x = normalizeCoord(x, worldSize);
  y = normalizeCoord(y, worldSize);
  z = normalizeCoord(z, worldSize);

  x = fminf(fmaxf(x, 0.0f), 1.0f);
  y = fminf(fmaxf(y, 0.0f), 1.0f);
  z = fminf(fmaxf(z, 0.0f), 1.0f);

  x = fmin(floor(x * 1023), 1023);
  y = fmin(floor(y * 1023), 1023);
  z = fmin(floor(z * 1023), 1023);

  unsigned short int xx = expandBits(x);
  unsigned short int yy = expandBits(y);
  unsigned short int zz = expandBits(z);

  // Interleave the bits
  return xx | (yy << 1) | (zz << 2);
}

int getSplitPos(int begin, int end){
  return floor((begin + end) / 2);
}


BVHNode* createSubTree(std::vector<std::tuple<int, unsigned short int>> nodes, int begin, int end, std::vector<IShape> boxes){
  if(begin == end){
    return new BVHNode(std::get<0>(nodes[begin]), ContainingRectangle(boxes[std::get<0>(nodes[begin])]));
  }else{
    int m = getSplitPos(begin, end);

    BVHNode* node = new BVHNode();
    node->left = createSubTree(nodes, begin, m, boxes);
    node->right = createSubTree(nodes, m + 1, end, boxes);
    
    auto minX = fminf(node->left->aabb.origin.x, node->right->aabb.origin.x);
    auto minY = fminf(node->left->aabb.origin.y, node->right->aabb.origin.y);

    auto maxX = fmaxf(node->left->aabb.origin.x, node->right->aabb.origin.x);
    auto maxY = fmaxf(node->left->aabb.origin.y, node->right->aabb.origin.y);

    node->aabb = FromMinMax(vec2(minX, minY), vec2(maxX, maxY));

    return node;
  }
}

// shape id are just an index
BVHNode* createTree(std::vector<IShape> shapes, int worldSize){

  std::vector<std::tuple<int, unsigned short int>> list;

  for(int i = 0; i < shapes.size(); ++i){
    vec2 center = shapes[i].GetCentroid();
    unsigned short int mortonCode = calculateMortonCode(center.x, center.y, 0, worldSize);

    list.push_back(std::tuple<int, unsigned short int>(i, mortonCode));
  }

  return createSubTree(list, 0, list.size()-1, shapes);

}

void findCollisions(int boxId, IShape box, BVHNode* node, std::vector<IShape> boxes, std::vector<CollisionData> &cd){
  if (!RectangleRectangle(ContainingRectangle(box), node->aabb)) {
      return;
  }

  if(node->IsLeaf()){
    if(node->boxId != boxId){
        CollisionData sat = SATCollision(box, boxes[boxId]);
        if(sat.collided){
          cd.push_back(sat);
        }
    }
  }

  return;
}