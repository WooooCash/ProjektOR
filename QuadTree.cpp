//
// Created by woocash on 14/01/24.
//

#include "QuadTree.h"

bool QuadTree::inBoundary(const glm::vec2& _pos) const {
    return (_pos.x >= topLeft.x && _pos.x <= botRight.x
            && _pos.y >= topLeft.y && _pos.y <= botRight.y);
}

void QuadTree::insert(Node *node) {
    if (node == nullptr)
        return;

    if (!inBoundary(node->pos))
        return;

    if (fabs(topLeft.x - botRight.x) <= minSize
        && fabs(topLeft.y - botRight.y) <= minSize) {
        data.push_back(node);
        isLeaf = true;
        return;
    }

    if ((topLeft.x + botRight.x) / 2 >= node->pos.x) {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
            if (topLeftTree == nullptr)
                topLeftTree = new QuadTree(
                    glm::vec2(topLeft.x, topLeft.y),
                    glm::vec2((topLeft.x + botRight.x) / 2,
                              (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(node);
        }

        else {
            if (botLeftTree == nullptr)
                botLeftTree = new QuadTree(
                    glm::vec2(topLeft.x,
                              (topLeft.y + botRight.y) / 2),
                    glm::vec2((topLeft.x + botRight.x) / 2,
                              botRight.y));
            botLeftTree->insert(node);
        }
    } else {
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
            if (topRightTree == nullptr)
                topRightTree = new QuadTree(
                    glm::vec2((topLeft.x + botRight.x) / 2,
                              topLeft.y),
                    glm::vec2(botRight.x,
                              (topLeft.y + botRight.y) / 2));
            topRightTree->insert(node);
        }

        // Indicates botRightTree
        else {
            if (botRightTree == nullptr)
                botRightTree = new QuadTree(
                    glm::vec2((topLeft.x + botRight.x) / 2,
                              (topLeft.y + botRight.y) / 2),
                    glm::vec2(botRight.x, botRight.y));
            botRightTree->insert(node);
        }
    }
}

std::vector<Node*> QuadTree::search(const glm::vec2& p)
{

    if (!inBoundary(p))
        return {};

    if (isLeaf)
        return data;

    if ((topLeft.x + botRight.x) / 2 >= p.x) {
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topLeftTree == nullptr)
                return {};
            return topLeftTree->search(p);
        }
        else {
            if (botLeftTree == nullptr)
                return {};
            return botLeftTree->search(p);
        }
    }
    else {
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topRightTree == nullptr)
                return {};
            return topRightTree->search(p);
        }
        else {
            if (botRightTree == nullptr)
                return {};
            return botRightTree->search(p);
        }
    }
};
