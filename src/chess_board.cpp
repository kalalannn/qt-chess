#include "chess_board.h"


ChessBoard::ChessBoard(QObject *parent) : QObject (parent) {
  this->new_board();
}

void ChessBoard::new_board() {
  m_board.fill(QChar::Null, 64);
  int i = 0;
  for (QChar value : "vjsdksjvppppppppPPPPPPPPVJSDKSJV") {
    m_board[i++] = value;
    if(i == 16) {
      i = 48;
    } else if (i == 64) {
      break;
    }
  }
}

void ChessBoard::move(int index_from, int index_to) {
  m_board[index_to] = m_board[index_from];
  m_board[index_from] = QChar::Null;
}

void ChessBoard::print() {
  int ind = 0;
  for (QChar x : m_board) {
    std::cout << "ind : " << ind++ << ", x :'" << x.toLatin1() << "'" << std::endl;
  }
}
