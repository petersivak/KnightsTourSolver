#ifndef NODE_HPP
#define NODE_HPP

#include "vector2b.hpp"

class Node
{
public:
	Node(const Vector2b &pos, const Node *parent);

	Vector2b pos() const;
	const Node *parent() const;

private:
	const Vector2b mPos;
	const Node *mParent;
};

#endif // NODE_HPP
