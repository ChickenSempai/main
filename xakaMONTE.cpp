#include <iostream>
#include <random>
#include <unordered_set>
#include "details/BeastGameClient.h"
#include "GameBoard.h"

const int TEST_COUNT = 150;
const int TEST_PATH_LENGHT =30;

inline bool deadly(const GameBoard& board, BoardPoint pt) {
	if (board.playerIsShadow())
		return false;
	return board.hasEnemyAt(pt)
		|| board.hasShadowEnemyAt(pt);
}
inline bool goodies(const GameBoard& board, BoardPoint pt) {
	return board.hasGoldAt(pt)
		|| board.getElementAt(pt) == BoardElement::THE_SHADOW_PILL
		|| (board.playerIsShadow() && (board.hasOtherHeroAt(pt) 
									|| board.hasShadowEnemyAt(pt)
									|| board.hasEnemyAt(pt)));
}

void printPath(std::vector<std::vector<bool>> table, const GameBoard& board){
	for (int i = 0; i < board.getBoardSize(); i++) {
		for (int j = 0; j < board.getBoardSize(); j++) {
			if (table[i][j]) {
				std::cout << 'X';
			}
			else std::cout << std::to_string(board.getElementAt({i,j}));
		}
		std::cout << '\n';
	}
}

bool walkable(const GameBoard& board, BoardPoint pt) {
	if (board.getElementAt(pt.shiftBottom()) == BoardElement::BRICK ||
		board.getElementAt(pt.shiftBottom()) == BoardElement::INDESTRUCTIBLE_WALL ||
		board.getElementAt(pt.shiftBottom()) == BoardElement::LADDER ||
		board.getElementAt(pt.shiftBottom()) == BoardElement::HERO_LADDER ||
		board.getElementAt(pt.shiftBottom()) == BoardElement::HERO_SHADOW_LADDER ||
		board.getElementAt(pt.shiftBottom()) == BoardElement::OTHER_HERO_LEFT ||
		board.getElementAt(pt.shiftBottom()) == BoardElement::OTHER_HERO_RIGHT ||
		board.getElementAt(pt) == BoardElement::HERO_LADDER ||
		board.getElementAt(pt) == BoardElement::HERO_SHADOW_LADDER ||
		board.getElementAt(pt) == BoardElement::LADDER ||
		board.getElementAt(pt) == BoardElement::PIPE ||
		board.getElementAt(pt) == BoardElement::HERO_PIPE_LEFT ||
		board.getElementAt(pt) == BoardElement::HERO_PIPE_RIGHT ||
		board.getElementAt(pt) == BoardElement::HERO_SHADOW_PIPE_RIGHT ||
		board.getElementAt(pt) == BoardElement::HERO_SHADOW_PIPE_LEFT ||
		board.getElementAt(pt) == BoardElement::PORTAL)
		return true;
	return false;
}

class pathPair {
	public:
		pathPair(BoardPoint *_pt, LodeRunnerAction move_):pt(*_pt),move(move_){}
		pathPair(pathPair *pair): pt((pair->pt)), move(pair->getMoveFromPath()) {}
		BoardPoint pt;
		
		LodeRunnerAction getMoveFromPath() const {
			return move;
		}
		void setMove(LodeRunnerAction move_) {
			move = move_;
		}
	private:

		LodeRunnerAction move;
};	

void drillLeftAndGo(const GameBoard& board, BoardPoint& currPt, std::vector<std::vector<bool>>& visited,
	LodeRunnerAction currMove, std::list<pathPair>& queue)
{
	if (board.getElementAt(currPt.shiftLeft().shiftBottom()) == BoardElement::BRICK &&
		!board.isNearToEnemy(board.getMyPosition()) &&
		walkable(board, currPt) &&
		walkable(board, currPt.shiftLeft()) &&
		board.hasElementAt(currPt.shiftLeft(), BoardElement::NONE)) {
		if (!visited[currPt.shiftLeft().shiftBottom().getY()][currPt.shiftLeft().shiftBottom().getX()]) {
			visited[currPt.shiftLeft().shiftBottom().getY()][currPt.shiftLeft().shiftBottom().getX()] = true;
			if (currMove == LodeRunnerAction::IDLE)
				queue.push_back({ &(currPt.shiftLeft().shiftBottom()), LodeRunnerAction::DRILL_LEFT });
			else
				queue.push_back({ &(currPt.shiftLeft().shiftBottom()), currMove });
		}
	}
}

void drillRightAndGo(const GameBoard& board, BoardPoint& currPt, std::vector<std::vector<bool>>& visited,
	LodeRunnerAction currMove, std::list<pathPair>& queue)
{
	if (board.getElementAt(currPt.shiftRight().shiftBottom()) == BoardElement::BRICK &&
		!board.isNearToEnemy(board.getMyPosition()) &&
		walkable(board, currPt) &&
		walkable(board, currPt.shiftRight()) &&
		board.hasElementAt(currPt.shiftRight(), BoardElement::NONE)) {
		if (!visited[currPt.shiftRight().shiftBottom().getY()][currPt.shiftRight().shiftBottom().getX()]) {
			visited[currPt.shiftRight().shiftBottom().getY()][currPt.shiftRight().shiftBottom().getX()] = true;
			if (currMove == LodeRunnerAction::IDLE)
				queue.push_back({ &(currPt.shiftRight().shiftBottom()), LodeRunnerAction::DRILL_RIGHT });
			else
				queue.push_back({ &(currPt.shiftRight().shiftBottom()), currMove });
		}
	}
}

void moveDown(const GameBoard& board, BoardPoint& currPt,
	std::vector<std::vector<bool>>& visited, LodeRunnerAction currMove,
	std::list<pathPair>& queue)
{
	if (board.getElementAt(currPt.shiftBottom()) == BoardElement::NONE ||
		board.hasElementAt(currPt.shiftBottom(), BoardElement::LADDER) ||
		board.hasElementAt(currPt.shiftBottom(), BoardElement::PIPE) ||
		board.hasElementAt(currPt.shiftBottom(), BoardElement::DRILL_PIT) ||
		goodies(board, currPt.shiftBottom())) {
		if (!visited[currPt.shiftBottom().getY()][currPt.shiftBottom().getX()]) {
			visited[currPt.shiftBottom().getY()][currPt.shiftBottom().getX()] = true;
			if (currMove == LodeRunnerAction::IDLE)
				queue.push_back({ &(currPt.shiftBottom()), LodeRunnerAction::GO_DOWN });
			else
				queue.push_back({ &(currPt.shiftBottom()), currMove });
		}
	}
}

void moveUp(const GameBoard& board, BoardPoint& currPt, std::vector<std::vector<bool>>& visited,
	LodeRunnerAction currMove, std::list<pathPair>& queue)
{
	if ((board.getElementAt(currPt) == BoardElement::HERO_LADDER ||
		board.getElementAt(currPt) == BoardElement::LADDER ||
		board.getElementAt(currPt) == BoardElement::HERO_SHADOW_LADDER)
		&&
		(board.getElementAt(currPt.shiftTop()) == BoardElement::NONE ||
			board.getElementAt(currPt.shiftTop()) == BoardElement::LADDER ||
			board.getElementAt(currPt.shiftTop()) == BoardElement::PIPE ||
			goodies(board, currPt.shiftTop()))) {
		if (!visited[currPt.shiftTop().getY()][currPt.shiftTop().getX()]) {
			visited[currPt.shiftTop().getY()][currPt.shiftTop().getX()] = true;
			if (currMove == LodeRunnerAction::IDLE)
				queue.push_back({ &(currPt.shiftTop()), LodeRunnerAction::GO_UP });
			else
				queue.push_back({ &(currPt.shiftTop()), currMove });
		}
	}
}

void moveRight(const GameBoard& board, BoardPoint& currPt, std::vector<std::vector<bool>>& visited,
	LodeRunnerAction currMove, std::list<pathPair>& queue)
{
	if (walkable(board, currPt) &&
		(board.getElementAt(currPt.shiftRight()) == BoardElement::NONE ||
			board.hasElementAt(currPt.shiftRight(), BoardElement::LADDER) ||
			board.hasElementAt(currPt.shiftRight(), BoardElement::PIPE) ||
			goodies(board, currPt.shiftRight()))) {
		if (!visited[currPt.shiftRight().getY()][currPt.shiftRight().getX()]) {
			visited[currPt.shiftRight().getY()][currPt.shiftRight().getX()] = true;
			if (currMove == LodeRunnerAction::IDLE)
				queue.push_back({ &(currPt.shiftRight()), LodeRunnerAction::GO_RIGHT });
			else
				queue.push_back({ &(currPt.shiftRight()), currMove });
		}
	}
}

void moveLeft(const GameBoard& board, BoardPoint& currPt, std::vector<std::vector<bool>>& visited,
	LodeRunnerAction currMove, std::list<pathPair>& queue)
{
	if (walkable(board, currPt) &&
		(board.getElementAt(currPt.shiftLeft()) == BoardElement::NONE ||
			board.hasElementAt(currPt.shiftLeft(), BoardElement::LADDER) ||
			board.hasElementAt(currPt.shiftLeft(), BoardElement::PIPE) ||
			goodies(board, currPt.shiftLeft()))) {
		if (!visited[currPt.shiftLeft().getY()][currPt.shiftLeft().getX()]) {
			visited[currPt.shiftLeft().getY()][currPt.shiftLeft().getX()] = true;
			if (currMove == LodeRunnerAction::IDLE)
				queue.push_back({ &(currPt.shiftLeft()), LodeRunnerAction::GO_LEFT });
			else
				queue.push_back({ &(currPt.shiftLeft()), currMove });

		}
	}
}

//teleports behavior || MAYBE implement monte for earning monke

BoardPoint randomWay(const GameBoard& board, BoardPoint pt, std::vector<std::vector<bool>> visited) {
	
	LodeRunnerAction tempMove = LodeRunnerAction::IDLE;
	std::list <pathPair> queue;
	std::vector <BoardPoint> possibleMoves;
	int QSize = 0;
	moveLeft(board, pt, visited, tempMove, queue);
	if (queue.size() > QSize) {
		possibleMoves.push_back(pt.shiftLeft());
		QSize = queue.size();
	}
	moveRight(board, pt, visited, tempMove, queue);
	if (queue.size() > QSize) {
		possibleMoves.push_back(pt.shiftRight());
		QSize = queue.size();
	}
	moveUp(board, pt, visited, tempMove, queue);
	if (queue.size() > QSize) {
		possibleMoves.push_back(pt.shiftTop());
		QSize = queue.size();
	}
	moveDown(board, pt, visited, tempMove, queue);
	if (queue.size() > QSize) {
		possibleMoves.push_back(pt.shiftBottom());
		QSize = queue.size();
	}
	drillRightAndGo(board, pt, visited, tempMove, queue);
	if (queue.size() > QSize) {
		possibleMoves.push_back(pt.shiftRight().shiftBottom());
		QSize = queue.size();
	}
	drillLeftAndGo(board, pt, visited, tempMove, queue);
	if (queue.size() > QSize) {
		possibleMoves.push_back(pt.shiftLeft().shiftBottom());
		QSize = queue.size();
	}
	queue.clear();
	if (QSize > 0) {
		int chosenMove = rand() % QSize;
		return possibleMoves[chosenMove];
	}
	else
		return pt.shiftTop();
	
}

int evalMove(const GameBoard& board, BoardPoint start, LodeRunnerAction move) {
	int bestVal = INT_MIN;
	int curVal = 0;
	std::vector <std::vector<bool>> visited(
		board.getBoardSize(),
		std::vector<bool>(board.getBoardSize(), false));
	BoardPoint position = start;
	visited[start.getY()][start.getX()] = true;
	switch (move) {
	case LodeRunnerAction::GO_LEFT:
		position = position.shiftLeft(); break;
	case LodeRunnerAction::GO_RIGHT:
		position = position.shiftRight(); break;
	case LodeRunnerAction::GO_DOWN:
		position = position.shiftBottom(); break;
	case LodeRunnerAction::GO_UP:
		position = position.shiftTop(); break;
	case LodeRunnerAction::DRILL_LEFT:
		position = position.shiftLeft().shiftBottom(); break;
	case LodeRunnerAction::DRILL_RIGHT:
		position = position.shiftRight().shiftBottom(); break;
	}
	visited[position.getY()][position.getX()] = true;
	for (int i = 0; i < TEST_COUNT; i++) {

		for (auto line : visited)
			std::fill(line.begin(), line.end(), false);
		visited[start.getY()][start.getX()] = true;
		visited[position.getY()][position.getX()] = true;
		BoardPoint currPt = position;
		for (int j = 0; j < TEST_PATH_LENGHT; j++)
		{
			curVal = 0;
			currPt = randomWay(board, currPt, visited);
			visited[currPt.getY()][currPt.getX()] = true;

			//if found gold then return move


			switch (board.getElementAt(currPt)) {
			case BoardElement::GREEN_GOLD:
				curVal += 1; break;
			case BoardElement::YELLOW_GOLD:
				curVal += 3; break;
			case BoardElement::RED_GOLD:
				curVal += 5; break;
			case BoardElement::THE_SHADOW_PILL:
				curVal += 10; break;
			case BoardElement::PORTAL:
				curVal += 1; break;
			}

			
		
			//if died return -1
			if (deadly(board, currPt))
			{
				curVal -= 1;
				break; // unable to continue path = dead
			}
			if (board.getElementAt(currPt) == BoardElement::INDESTRUCTIBLE_WALL)
				break;
		}
		bestVal = std::max(bestVal, curVal);
	}
	return bestVal;
}

/*
LodeRunnerAction makeTurn(const GameBoard& board) {
	BoardPoint position = board.getMyPosition();
	std::cout << "Hero position is (" << position.getX() << "," << position.getY() << ")\n";

	std::list <pathPair> queue;

	std::vector <std::vector<bool>> visited(
		board.getBoardSize(),
		std::vector<bool>(board.getBoardSize(), false));

	visited[position.getY()][position.getX()] = true;
	queue.push_back({ &position , LodeRunnerAction::IDLE });
	while (!queue.empty())
	{
		pathPair temp(queue.front());
		BoardPoint currPt = (temp.pt);
		LodeRunnerAction currMove = temp.getMoveFromPath();
		queue.pop_front();

		 //if found gold then return move
		if (goodies(board, currPt)){
			//КОСТЫЛЬ (с пилюлей все противники = goodies чтобы спокойно через них проходить
			// но стремится бегать за ними нет смысла
			if (!board.hasOtherHeroAt(currPt)
				&& !board.hasShadowEnemyAt(currPt)
				&& !board.hasEnemyAt(currPt)) {
				queue.clear();
				return currMove;
			}
		}
		 //if died return -1
		if (deadly(board, currPt))
		{
			continue; // unable to continue path = dead
		}


		moveLeft(board, currPt, visited, currMove, queue);

		moveRight(board, currPt, visited, currMove, queue);

		moveUp(board, currPt, visited, currMove, queue);

		moveDown(board, currPt, visited, currMove, queue);

		drillRightAndGo(board, currPt, visited, currMove, queue);

		drillLeftAndGo(board, currPt, visited, currMove, queue);

	}
	return LodeRunnerAction::GO_UP;
}
*/

LodeRunnerAction makeTurn(const GameBoard& board) {
	BoardPoint position = board.getMyPosition();
	std::cout << "Hero position is (" << position.getX() << "," << position.getY() << ")\n";
	LodeRunnerAction bestAction = LodeRunnerAction::GO_UP;
	int res;
	int bestResult = INT_MIN;

	LodeRunnerAction tempMove = LodeRunnerAction::IDLE;
	std::list <pathPair> queue;

	std::vector <std::vector<bool>> visited(
	board.getBoardSize(),
	std::vector<bool>(board.getBoardSize(), false));
	int QSize = 0;
	moveLeft(board, position, visited, tempMove, queue);
	if (queue.size() > QSize) {
		if (bestResult < (res = evalMove(board, position, LodeRunnerAction::GO_LEFT))) {
			bestResult = res;
			bestAction = LodeRunnerAction::GO_LEFT;
		}
		QSize = queue.size();
	}
	moveRight(board, position, visited, tempMove, queue);
	if (queue.size() > QSize) {
		if (bestResult < (res = evalMove(board, position, LodeRunnerAction::GO_RIGHT))) {
			bestResult = res;
			bestAction = LodeRunnerAction::GO_RIGHT;
		}
		QSize = queue.size();
	}
	moveUp(board, position, visited, tempMove, queue);
	if (queue.size() > QSize) {
		if (bestResult < (res = evalMove(board, position, LodeRunnerAction::GO_UP))) {
			bestResult = res;
			bestAction = LodeRunnerAction::GO_UP;
		}
		QSize = queue.size();
	}
	moveDown(board, position, visited, tempMove, queue);
	if (queue.size() > QSize) {
		if (bestResult < (res = evalMove(board, position, LodeRunnerAction::GO_DOWN))) {
			bestResult = res;
			bestAction = LodeRunnerAction::GO_DOWN;
		}
		QSize = queue.size();
	}
	drillRightAndGo(board, position, visited, tempMove, queue);
	if (queue.size() > QSize) {
		if (bestResult < (res = evalMove(board, position, LodeRunnerAction::DRILL_RIGHT))) {
			bestResult = res;
			bestAction = LodeRunnerAction::DRILL_RIGHT;
		}
		QSize = queue.size();
	}
	drillLeftAndGo(board, position, visited, tempMove, queue);
	if (queue.size() > QSize) {
		if (bestResult < (res = evalMove(board, position, LodeRunnerAction::DRILL_LEFT))) {
			bestResult = res;
			bestAction = LodeRunnerAction::DRILL_LEFT;
		}
	}

	return bestAction;
}

int main() {
	const std::string serverUrl = "https://dojorena.io/codenjoy-contest/board/player/dojorena427?code=1388849016264401508";

	while(1) {
		details::BeastGameClient gcb(serverUrl);
		gcb.Run(makeTurn);
	}

	return 0;
}
