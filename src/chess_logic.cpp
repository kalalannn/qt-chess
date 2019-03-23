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
	if (abs(to_x - from_x) > 1)
		return;

	if (abs(to_x - from_x) == 1) {
		if (currPlayer == whitePlayer && (to_y - from_y) == 1) {
			m_board->setData(to_x, to_y, 'P');
			m_board->setData(from_x, from_y, ' ');
			// еще надо удалить схаванную фигуру из массива
			return;
		}
		else if (currPlayer == blackPlayer && (to_y - from_y) == -1) {
			m_board->setData(to_x, to_y, 'p');
			m_board->setData(from_x, from_y, ' ');
			// еще надо удалить схаванную фигуру из массива
			return;
		}
		else
			return;
	}

	if (abs(to_y - from_y) > 2)
		return;

	if (currPlayer == whitePlayer && (to_y - to_y) == 1) {
		if (m_board->data(to_x, to_y) == ' ') {
			m_board->setData(to_x, to_y, 'P');
			m_board->setData(from_x, from_y, ' ');
			// еще надо удалить схаванную фигуру из массива
			return;
		}
	}
	else if (currPlayer == blackPlayer && (to_y - from_y) == -1) {
		if (m_board->data(to_x, to_y) == ' ') {
			m_board->setData(to_x, to_y, 'p');
			m_board->setData(from_x, from_y, ' ');
			// еще надо удалить схаванную фигуру из массива
			return;
		}
	}
	else
		return;

	if (currPlayer == whitePlayer && from_y == 2 & to_y == 4
			&& m_board->data(from_x, from_y + 1) == ' ' && m_board->data(from_x, from_y + 2) == ' ') {
		m_board->setData(to_x, to_y, 'P');
		m_board->setData(from_x, from_y, ' ');
		// еще надо удалить схаванную фигуру из массива
		return;
	}
	if (currPlayer == blackPlayer && from_y == 7 & to_y == 5
			&& m_board->data(from_x, from_y - 1) == ' ' && m_board->data(from_x, from_y - 2) == ' ') {
		m_board->setData(to_x, to_y, 'p');
		m_board->setData(from_x, from_y, ' ');
		// еще надо удалить схаванную фигуру из массива
		return;
	}

	return;
}

void ChessLogic::test() {
  m_board->test();
}

