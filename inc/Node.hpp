#ifndef NODE_HPP
#define NODE_HPP


#include <string>


class ColumnNode;

// A DancingNode object is used to model a node in the quadruple-chained list for exact cover problem.
class DancingNode
{
public:
    DancingNode* left;
    DancingNode* right;
    DancingNode* top;
    DancingNode* bottom;
    ColumnNode* column;

public:
    DancingNode();
    DancingNode(ColumnNode* c);

    DancingNode* linkDown(DancingNode* node);
    DancingNode* linkRight(DancingNode* node);

    void removeLeftRight();
    void reinsertLeftRight();

    void removeTopBottom();
    void reinsertTopBottom();
};

// A ColumnNode object is used to link the current node to the belonging column in the cover matrix.
class ColumnNode : public DancingNode
{
public:
    int size;
    std::string name;

public:
    ColumnNode(std::string n);

    void cover();
    void uncover();
};


#endif   // NODE_HPP