#include "node.hpp"

Node::Node(const Vector2b &pos, const Node *parent) :
	mPos(pos),
	mParent(parent)
{
}

Vector2b Node::pos() const { return mPos; }
const Node *Node::parent() const { return mParent; }
