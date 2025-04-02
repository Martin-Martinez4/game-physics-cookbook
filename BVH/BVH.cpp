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
uint64_t split(uint64_t x, int log_bits) {
    const int bit_count = 1 << log_bits;
    uint64_t mask = ((uint64_t)-1) >> (bit_count / 2);
    x &= mask;
    for (int i = log_bits - 1, n = 1 << i; i > 0; --i, n >>= 1) {
        mask = (mask | (mask << n)) & ~(mask << (n / 2));
        x = (x | (x << n)) & mask;
    }
    return x;
}

uint64_t encode(uint64_t x, uint64_t y, uint64_t z, int log_bits) {
    return split(x, log_bits) | (split(y, log_bits) << 1) | (split(z, log_bits) << 2);
}

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

  x = fmin(floor(int(x * 1023)), 1023);
  y = fmin(floor(int(y * 1023)), 1023);
  z = fmin(floor(int(z * 1023)), 1023);

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
    unsigned short int mortonCode = encode(center.x, center.y, 0, worldSize);

    list.push_back(std::tuple<int, unsigned short int>(i, mortonCode));
  }

  std::sort(list.begin(), list.end(), [](std::tuple<int, unsigned short int> a, std::tuple<int, unsigned short int> b){
    return std::get<1>(a) < std::get<1>(b); 
  });

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