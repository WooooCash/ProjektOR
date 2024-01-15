//
// Created by woocash on 14/01/24.
//
#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <glm/glm.hpp>

struct Node {
    glm::vec2 pos{};
    int vIdx;
    Node(const glm::vec2 _pos, const int _vIdx)
    {
        pos = _pos;
        vIdx = _vIdx;
    }
    Node() { vIdx = 0; }
};

class QuadTree {
    glm::vec2 topLeft{};
    glm::vec2 botRight{};
    float minSize;
    bool isLeaf;

    std::vector<Node*> data;

    QuadTree* topLeftTree;
    QuadTree* topRightTree;
    QuadTree* botLeftTree;
    QuadTree* botRightTree;

public:
    QuadTree(const glm::vec2 _tl, const glm::vec2 _br) {
        topLeft = _tl;
        botRight = _br;
        minSize = glm::min(_tl.y - _br.y, _br.x-_tl.x) / 100.f;
        isLeaf = false;

        topLeftTree = nullptr;
        topRightTree = nullptr;
        botLeftTree = nullptr;
        botRightTree = nullptr;
    }

    void insert(Node* node);
    [[nodiscard]] bool inBoundary(const glm::vec2& _pos) const;
    std::vector<Node*> search(const glm::vec2& p);
};



#endif //QUADTREE_H
