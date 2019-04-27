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
  if (piece.toLower() != KNIGHT and piece.toLower() != PAWN) {
    if (offset.x() == 0) { // STRAIGHT
      for (int inc = 1; inc != abs(offset.y()) + 1; inc++) {
        if (inc == abs(offset.y())) {
          res = check_final_cell(to);
        } else if (offset.y() < 0) {
          res = check_cell(QPoint(from.x(), from.y() - inc));
        } else {
          res = check_cell(QPoint(from.x(), from.y() + inc));
        }
        if (not res) { return res; }
      }
    } else if (offset.y() == 0) {
      for (int inc = 1; inc != abs(offset.x()) + 1; inc++) {
        if (inc == abs(offset.x())) {
          res = check_final_cell(to);
        } else if (offset.x() < 0) {
          res = check_cell(QPoint(from.x() - inc, from.y()));
        } else {
          res = check_cell(QPoint(from.x() + inc , from.y()));
        }
        if (not res) { return res; }
      }
    } else { // DIAGONAL
      for (int inc = 1; inc != abs(offset.x()) + 1; inc++) {
        if (inc == abs(offset.x())) {
          res = check_final_cell(to);
        } else if (offset.x() < 0 and offset.y() < 0) {
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
  } else if (piece.toLower() == KNIGHT) {
    if (check_final_cell(to) == false) { return false; } // KNIGHT
  } else if (piece.toLower() == PAWN) {
    if (piece.isLower()) { //white
      if (offset.y() < 0) { return false; }
    } else { // Black
      if (offset.y() > 0) { return false; }
    }

    if (abs(offset.x()) == abs(offset.y())) { //diag
      if (this->player() == WHITE) {
        if (this->piece(to).isUpper()) { }
        else  { return false; }
      } else if (this->player() == BLACK) {
        if (this->piece(to).isLower()) { }
        else { return false; }
      }
    } else if (offset.y() == -2) { // black
      if (not check_cell(QPoint(from.x(), from.y() - 1))) { return false; }
      if (not check_cell(to)) { return false; }
    } else if (offset.y() == 2) {
      if (not check_cell(QPoint(from.x(), from.y() + 1))) { return false; }
      if (not check_cell(to)) { return false; }
    }
  }
  this->board()->move(ChessBoard::index(from), ChessBoard::index(to));
  this->change_player();

  return true;
}

//! проверит клетку (для всеx кроме коня)
bool ChessLogic::check_cell(QPoint coordinate) {
  if (this->piece(coordinate) == QChar::Null) {  }
  else { return false; }
  return true;
}

bool ChessLogic::check_final_cell (QPoint to) {
  if (this->player() == WHITE and
      (this->piece(to) == QChar::Null or this->piece(to).isUpper())) { }
  else if (this->player() == BLACK and
      (this->piece(to) == QChar::Null or this->piece(to).isLower())) { }
  else  { return false; }
  return true;
}
