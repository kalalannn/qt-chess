#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

//! .h files
#include "chess_board.h"

//! QIncludes
#include <QObject>
#include <QPointer>

//! C++11 includes


//! Chess Logic
class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr);

	//! Create a new game
	void newGame();

	QPointer <ChessBoard> board() { return m_board; }

	//! Moves
	void move(int from_x, int from_y, int to_x, int to_y);
	void moveKing(int, int, int, int);
	void moveQueen(int, int, int, int);
	void moveRook(int, int, int, int);
	void moveKnight(int, int, int, int);
	void moveBishop(int, int, int, int);
	void movePawn(int, int, int, int);

private:
	//! Board
	QPointer<ChessBoard> m_board;
};

#endif // CHESS_LOGIC_H
