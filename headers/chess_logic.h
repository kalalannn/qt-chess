#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include "chess_board.h"

#include <QObject>
#include <QPointer>

class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr);
	enum Player { whitePlayer, blackPlayer };
	Q_ENUM(Player)

	void newGame();
	QPointer<ChessBoard> board() { return m_board; }

	// мувим писы
	void move(int from_x, int from_y, int to_x, int to_y, QChar piece);
	void moveKing(int, int, int, int);
	void moveQueen(int, int, int, int);
	void moveRook(int, int, int, int);
	void moveKnight(int, int, int, int);
	void moveBishop(int, int, int, int);
	void movePawn(int, int, int, int);

  void test();

private:
	QPointer<ChessBoard> m_board;
	Player currPlayer;
};

#endif // CHESS_LOGIC_H
