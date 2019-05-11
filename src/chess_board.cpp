#include "chess_board.h"
#include "chess_logic.h"

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

void ChessBoard::setCell(int index, QChar piece) {
  m_board[index] = piece;
}

QPoint ChessBoard::getAnotherPiece(QPair <QPoint,QChar> coord_piece) {
  QPoint ret_piece = QPoint(-1,-1);
  for (int i = 0; i < 64 ;i++) {
    if (m_board[i] == coord_piece.second and coord(i) != coord_piece.first) {
      return coord(i);
    }
  }
  return ret_piece;
}

QVector <QPoint> ChessBoard::getActualPieces(int color) {
  QVector <QPoint> coordinates;
  if (color == WHITE) {
    for (int i = 0; i < 64 ;i++) {
      if (m_board[i].isLower()) {
        coordinates.append(this->coord(i));
      }
    }
  } else {
    for (int i = 0; i < 64 ;i++) {
      if (m_board[i].isUpper()) {
        coordinates.append(this->coord(i));
      }
    }
  }
  return coordinates;
}
