#include<QPoint>

#include "../headers/chess_logic.h"

ChessLogic::ChessLogic(QObject *parent) : QObject (parent){

}

void ChessLogic::newGame() {
  m_board = new ChessBoard(this);
	m_board->newBoard();
}

void ChessLogic::move(int from_x, int from_y, int to_x, int to_y, QChar piece) {
	switch (piece.unicode()) {
	case 'k':
		moveKing(from_x, from_y, to_x, to_y);
		break;
	case 'q':
		moveQueen(from_x, from_y, to_x, to_y);
		break;
	case 'r':
		moveRook(from_x, from_y, to_x, to_y);
		break;
	case 'n':
		moveKnight(from_x, from_y, to_x, to_y);
		break;
	case 'b':
		moveBishop(from_x, from_y, to_x, to_y);
		break;
	case 'p':
		movePawn(from_x, from_y, to_x, to_y);
		break;
	}
}

void ChessLogic::moveKing(int from_x, int from_y, int to_x, int to_y) {
	Q_UNUSED(from_x);
	Q_UNUSED(from_y);
	Q_UNUSED(to_x);
	Q_UNUSED(to_y);
}

void ChessLogic::moveQueen(int from_x, int from_y, int to_x, int to_y) {
	Q_UNUSED(from_x);
	Q_UNUSED(from_y);
	Q_UNUSED(to_x);
	Q_UNUSED(to_y);

}

void ChessLogic::moveRook(int from_x, int from_y, int to_x, int to_y) {
	Q_UNUSED(from_x);
	Q_UNUSED(from_y);
	Q_UNUSED(to_x);
	Q_UNUSED(to_y);

}

void ChessLogic::moveKnight(int from_x, int from_y, int to_x, int to_y) {
	Q_UNUSED(from_x);
	Q_UNUSED(from_y);
	Q_UNUSED(to_x);
	Q_UNUSED(to_y);

}

void ChessLogic::moveBishop(int from_x, int from_y, int to_x, int to_y) {
	Q_UNUSED(from_x);
	Q_UNUSED(from_y);
	Q_UNUSED(to_x);
	Q_UNUSED(to_y);

}

void ChessLogic::movePawn(int from_x, int from_y, int to_x, int to_y) {

}

void ChessLogic::test() {
  m_board->test();
}

