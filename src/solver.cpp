#include "solver.hpp"

#include <QMap>

Solver::Solver() :
	mChessboardSize(8),
	mStartPos(0, 0),
	mMoves(),
	mVisitedPositions(),
	mSufficientDepth(mChessboardSize * mChessboardSize - 1),
	mIsSearchingForSolution(false),
	mSolution()
{
	mMoves.append(Vector2b(-1, -2));
	mMoves.append(Vector2b(1, -2));
	mMoves.append(Vector2b(-1, 2));
	mMoves.append(Vector2b(1, 2));
	mMoves.append(Vector2b(-2, -1));
	mMoves.append(Vector2b(-2, 1));
	mMoves.append(Vector2b(2, -1));
	mMoves.append(Vector2b(2, 1));
}

void Solver::searchForSolution()
{
	// Clear previous solution
	if (!mSolution.isEmpty())
		mSolution.clear();

	// Initialize visited positions matrix
	initializeVisitedPositions();

	// Create a stack of nodes and push there a head node
	QStack<Node *> nodes;
	nodes.push(new Node(mStartPos, 0));

	// Start searching for a solution
	mIsSearchingForSolution = true;
	qint16 currentDepth = 0;
	while (mIsSearchingForSolution)
	{
		// If we have not found any solution
		if (nodes.isEmpty())
		{
			mIsSearchingForSolution = false;
			continue;
		}

		// Get node from top of stack
		const Node *currentNode = nodes.top();

		// If we have returned from a child node, pop it
		if (mVisitedPositions[currentNode->pos().y()][currentNode->pos().x()] == true)
		{
			mVisitedPositions[currentNode->pos().y()][currentNode->pos().x()] = false;
			delete nodes.top();
			nodes.pop();
			if (!nodes.isEmpty() && mVisitedPositions[nodes.top()->pos().y()][nodes.top()->pos().x()] == true)
				--currentDepth;
			continue;
		}
		else
		{
			mVisitedPositions[currentNode->pos().y()][currentNode->pos().x()] = true;
		}

		// If we have found a solution
		if (currentDepth >= mSufficientDepth)
		{
			// Store solution
			for (int i = 0; i < mSufficientDepth + 1; ++i)
			{
				// Store and go to next
				mSolution.append(currentNode->pos());
				currentNode = currentNode->parent();
			}

			mIsSearchingForSolution = false;
			continue;
		}

		// Find possible moves from current position
		QList<Vector2b> possibleMoves = findPossibleMoves(currentNode->pos());

		// If this is not a leaf
		if (!possibleMoves.isEmpty())
		{
			expandNode(nodes.top(), nodes, possibleMoves);
			++currentDepth;
		}
		// Else if this is a leaf
		else
		{
			mVisitedPositions[currentNode->pos().y()][currentNode->pos().x()] = false;
			delete nodes.top();
			nodes.pop();
			if (!nodes.isEmpty() && mVisitedPositions[nodes.top()->pos().y()][nodes.top()->pos().x()] == true)
				--currentDepth;
		}
	}

	// Cleanup nodes in stack
	for (int i = 0; i < nodes.size(); ++i)
	{
		delete nodes[i];
	}

	// Cleanup visited positions matrix
	cleanupVisitedPositions();
}

void Solver::cancelOperation()
{
	mIsSearchingForSolution = false;
}

bool Solver::hasSolutionBeenFound() const
{
	if (!mSolution.isEmpty())
		return true;

	return false;
}

const QList<Vector2b> &Solver::solution() const { return mSolution; }

void Solver::setChessboardSize(int size)
{
	mChessboardSize = size;
	mSufficientDepth = mChessboardSize * mChessboardSize - 1;
}

void Solver::setStartPosition(const Vector2b &startPos) { mStartPos = startPos; }

void Solver::run()
{
	searchForSolution();
}

void Solver::initializeVisitedPositions()
{
	for (int i = 0; i < mChessboardSize; ++i)
	{
		QList<bool> innerList;
		for (int j = 0; j < mChessboardSize; ++j)
		{
			innerList.append(false);
		}
		mVisitedPositions.append(innerList);
	}
}

void Solver::cleanupVisitedPositions()
{
	mVisitedPositions.clear();
}

bool Solver::canMove(const Vector2b &pos) const
{
	if ( (pos.x() >= 0) && (pos.x() <= mChessboardSize - 1) &&
		 (pos.y() >= 0) && (pos.y() <= mChessboardSize - 1) &&
		 (mVisitedPositions[pos.y()][pos.x()]) == 0 )
	{
		return true;
	}
	return false;
}

QList<Vector2b> Solver::findPossibleMoves(const Vector2b &pos)
{
	QMap<int, Vector2b> possibleMoves;   // Map of moves which will be ordered by number of onward moves

	// Insert possible moves to the map
	for (int i = 0; i < mMoves.size(); ++i)
	{
		// If knight can move there, insert it to the map
		if (canMove(pos + mMoves[i]))
		{
			// Find number of onward moves
			int onwardMovesCount = 0;
			for (int j = 0; j < mMoves.size(); ++j)
			{
				if (canMove(pos + mMoves[i] + mMoves[j]))
					++onwardMovesCount;
			}

			possibleMoves.insertMulti(onwardMovesCount - 1, pos + mMoves[i]);   // Insert
		}
	}

	return possibleMoves.values();
}

void Solver::expandNode(const Node *parent, QStack<Node *> &nodes, const QList<Vector2b> &positions)
{
	// Push nodes to the stack in descending order
	for (int i = positions.size() - 1; i >= 0; --i)   // With heuristic
	//for (int i = 0; i < positions.size(); ++i)   // Without heuristic (much slower)
	{
		nodes.push(new Node(positions[i], parent));
	}
}

bool Solver::isSearchingForSolution() const { return mIsSearchingForSolution; }
