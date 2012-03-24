#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QThread>

#include <QList>
#include <QStack>

#include "node.hpp"

/**
 * The class Solver is responsible to search for a solution of the knight's tour
 * problem.
 * @author Peter Sivak
 */
class Solver : public QThread
{
	Q_OBJECT

public:
	/**
	 * Constructs a Solver.
	 */
	Solver();

	/**
	 * Starts searching for a solution.
	 */
	void searchForSolution();

	/**
	 * Sends a request to cancel searching for a solution operation.
	 */
	void cancelOperation();

	/**
	 * Whether a solution has been found.
	 * @return whether a solution has been found
	 */
	bool hasSolutionBeenFound() const;

	/**
	 * Returns a solution.
	 * @return a solution
	 */
	const QList<Vector2b> &solution() const;

	/**
	 * Sets chessboard size.
	 * @param size the size
	 */
	void setChessboardSize(int size);

	/**
	 * Sets knight's start position.
	 * @param startPos start position
	 */
	void setStartPosition(const Vector2b &startPos);

private:
	void run();

	void initializeVisitedPositions();
	void cleanupVisitedPositions();

	/**
	 * Whether knight can move to the position pos.
	 * @param pos destination position
	 * @return whether knight can move to the position pos
	 */
	bool canMove(const Vector2b &pos) const;

	/**
	 * Finds possible knight's moves from position pos and returns them ordered
	 * using Warnsdorf's heuristic.
	 * @param pos current position
	 * @return ordered possible moves
	 */
	QList<Vector2b> findPossibleMoves(const Vector2b &pos);

	/**
	 * Expands a node. It creates new nodes from the specified positions and
	 * pushes them to the stack of nodes.
	 * @param parent node to expand
	 * @param nodes stack of nodes
	 * @param positions list of positions
	 */
	void expandNode(const Node *parent, QStack<Node *> &nodes, const QList<Vector2b> &positions);

	bool isSearchingForSolution() const;

	int mChessboardSize;
	Vector2b mStartPos;

	QList<Vector2b> mMoves;
	QList< QList<bool> > mVisitedPositions;
	qint16 mSufficientDepth;
	bool mIsSearchingForSolution;

	QList<Vector2b> mSolution;
};

#endif // SOLVER_HPP
