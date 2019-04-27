#include "chess_logic.h"

ChessLogic::ChessLogic(QObject *parent,
                       QPointer <ChessBoard> board) : QObject (parent) {
  this->set_board(board);
  this->set_hand(QPoint(-1,-1));
  this->set_player(WHITE);
}

//------DEVEL


//! check может ли фигура в руке ходить, куда ее послали
bool ChessLogic::check_moving_rules(QPoint offset, QChar piece) {
    if (offset.x() == 0 or offset.y() == 0) {   //Straight
      switch (piece.unicode()) {
        case QUEEN: case ROOK:  return true;

        case PAWN:
          if (offset.x() != 0) { return false; }

          if (abs(offset.y()) == 1) { }
          else if (abs(offset.y()) == 2 and
                  (this->hand().y() == 1 or this->hand().y() == 6)) { }
          else { return false; }
          return true;

        case KING:
          if (abs(offset.x()) == 1 or abs(offset.y()) == 1) { }
          else { return false; }
          return true;

        default:  return false;
      }
    }
    else if (abs(offset.x()) == abs(offset.y())) {  //DIAGONAL;
      switch (piece.unicode()) {
        case QUEEN: case OFFICER:  return true;

        case KING: case PAWN:
          if (abs(offset.x()) == 1 and abs(offset.y()) == 1) { return true; }
          else { return false; }

        default:  return false;
      }
    }
    else if ((abs(offset.x()) == 2 and abs(offset.y()) == 1) or
             (abs(offset.x()) == 1 and abs(offset.y()) == 2)) {  // G
      switch (piece.unicode()) {
        case KNIGHT:  return true;
        default:      return false;
      }
    }
    else { return false; }
}

//! взять piece в руку
bool ChessLogic::get_piece(QPoint from) {
  QChar piece = this->piece(from);
  if (this->player() == WHITE      and piece.isLower()) { }
  else if (this->player() == BLACK and piece.isUpper()) { }
  else { return false; }

  this->set_hand(from);
  return true;
}

//! походить piecom из руки
bool ChessLogic::put_piece(QPoint to) {
  QPoint from = this->hand();
  if (from == to) { return false; }
  QChar piece = this->piece(from);
  QPoint offset = QPoint(to.x() - from.x(), to.y() - from.y());
  bool res = false;

  if (not this->check_moving_rules(offset, piece.toLower())) { return false; }
  if (piece.toLower() != KNIGHT) {
    if (offset.x() == 0) { // STRAIGHT
      for (int inc = 1; inc != abs(offset.y()) + 1; inc++) {
        if (offset.y() < 0) {
          res = check_cell(QPoint(from.x(), from.y() - inc));
        } else {
          res = check_cell(QPoint(from.x(), from.y() + inc));
        }
        if (not res) { return res; }
      }
    } else if (offset.y() == 0) {
      for (int inc = 1; inc != abs(offset.x()) + 1; inc++) {
        if (offset.x() < 0) {
          res = check_cell(QPoint(from.x() - inc, from.y()));
        } else {
          res = check_cell(QPoint(from.x() + inc , from.y()));
        }
        if (not res) { return res; }
      }
    } else { // DIAGONAL
      for (int inc = 1; inc != abs(offset.x()) + 1; inc++) {
        if (offset.x() < 0 and offset.y() < 0) {
          res = check_cell(QPoint(from.x() - inc, from.y() - inc));
        } else if (offset.x() > 0 and offset.y() > 0){
          res = check_cell(QPoint(from.x() + inc , from.y() + inc));
        } else if (offset.x() > 0 and offset.y() < 0) {
          res = check_cell(QPoint(from.x() + inc , from.y() - inc));
        } else if (offset.x() < 0 and offset.y() > 0) {
          res = check_cell(QPoint(from.x() - inc , from.y() + inc));
        }
        if (not res) { return res; }
      }
    }
  } else {
    if (check_cell(to) == false) { return false; } // KNIGHT
  }
  this->board()->move(ChessBoard::index(from), ChessBoard::index(to));
  this->change_player();

  return true;
}

//! проверит клетку (для всеx кроме коня)
bool ChessLogic::check_cell(QPoint coordinate) {
  std::cout << "Checking cell: " << coordinate.x() << ", " << coordinate.y() << std::endl;

  return true;
}
