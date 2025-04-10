#ifndef QUADTREE_H_
#define QUADTREE_H_

#include "Geometry2D.h"
#include <vector>

// ugly code from book
struct QuadTreeData{
  void* object;
  Rectangle2D bounds;
  bool flag;
  inline QuadTreeData(void* o, const Rectangle2D& b): object(0), bounds(b), flag(false) {}
};

class QuadTreeNode{
protected:
  std::vector<QuadTreeNode> childern;
  std::vector<QuadTreeData*> contents;
  int currentDepth;
  static int maxDepth;
  static int maxObjectsPerNode;
  Rectangle2D nodeBounds;

public:
  inline QuadTreeNode(const Rectangle2D& bounds): nodeBounds(bounds), currentDepth(0){}
  bool IsLeaf();
  int NumObjects();
  void Insert(QuadTreeData& data);
  void Remove(QuadTreeData& data);
  void Update(QuadTreeData& data);
  void Shake();
  void Split();
  void Reset();

  std::vector<QuadTreeData*>Query(const Rectangle2D& area);
};

typedef QuadTreeNode QuadTree;

#endif