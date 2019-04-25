#include "chess_view.h"

ChessView::ChessView(QWidget *parent,
                     QPointer <ChessBoard> board) : QWidget (parent) {
  this->set_board(board);
}
