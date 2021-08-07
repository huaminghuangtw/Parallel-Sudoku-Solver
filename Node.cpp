#include "Node.hpp"


DancingNode::DancingNode()
{
	left = this;
	right = this;
	top = this;
	bottom = this;
}

DancingNode::DancingNode(ColumnNode* c)
	: DancingNode()
{
	column = c;
}

DancingNode* DancingNode::linkDown(DancingNode* node)
{
	node->bottom = bottom;
	node->bottom->top = node;
	node->top = this;
	bottom = node;
	return node;
}

DancingNode* DancingNode::linkRight(DancingNode* node)
{
	node->right = right;
	node->right->left = node;
	node->left = this;
	right = node;
	return node;
}

void DancingNode::removeLeftRight()
{
	left->right = right;
	right->left = left;
}

void DancingNode::reinsertLeftRight()
{
	left->right = this;
	right->left = this;
}

void DancingNode::removeTopBottom()
{
	top->bottom = bottom;
	bottom->top = top;
}

void DancingNode::reinsertTopBottom()
{
	top->bottom = this;
	bottom->top = this;
}

ColumnNode::ColumnNode(std::string n)
	: DancingNode()
{
	size = 0;
	name = n;
	column = this;
}

void ColumnNode::cover()
{
	removeLeftRight();
	for (DancingNode* i = bottom; i != this; i = i->bottom)
	{
		for (DancingNode* j = i->right; j != i; j = j->right)
		{
			j->removeTopBottom();
			j->column->size--;
		}
	}
}

void ColumnNode::uncover()
{
	for (DancingNode* i = top; i != this; i = i->top)
	{
		for (DancingNode* j = i->left; j != i; j = j->left)
		{
			j->column->size++;
			j->reinsertTopBottom();
		}
	}
	reinsertLeftRight();
}