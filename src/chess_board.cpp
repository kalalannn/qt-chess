#include "../headers/chess_board.h"

ChessBoard::ChessBoard(QObject *parent) : QObject (parent) {
}

void ChessBoard::newBoard() {
  m_board.fill(' ', 64);
  int i = 0;
  for (QChar value : "vjsdksjvpppppppp") {
    m_board[i] = value;
    i++;
    if(i == 16)
      break;
  }
  i = 48;
  for (QChar value : "PPPPPPPPVJSDKSJV") {
    m_board[i] = value;
    i++;
    if(i == 64)
      break;
  }
}

void ChessBoard::print() {
  int ind = 0;
  for (QChar x : m_board) {
		std::cout << "ind : " << ind << ", x :'" << x.toLatin1() << "'" << std::endl;
    ind++;
  }
}
