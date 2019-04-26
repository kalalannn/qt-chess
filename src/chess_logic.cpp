#include "chess_logic.h"

ChessLogic::ChessLogic(QObject *parent,
                       QPointer <ChessBoard> board) : QObject (parent) {
  this->set_board(board);
  this->set_hand(QPoint(-1,-1));
  this->set_player(WHITE);
}

bool ChessLogic::test_direction_offset(QPair <int,QPoint> direction_offset, QPoint to) {
  QString direction;
  switch (direction_offset.first) {
    case STRAIGHT: direction = "straight"; break;
    case DIAGONAL: direction = "diagonal"; break;
    case G:        direction = "g";        break;
    default:       direction = "false";    break;
  }
  std::cout << "from (x,y): " << this->hand(). x() << ", " << this->hand().y() << std::endl;
  std::cout << "to (x,y): " << to.x() << ", " << to.y() << std::endl;
  std::cout << "direction : " << direction.toStdString() << std::endl;
  std::cout << "offset_x : " << direction_offset.second.x() << std::endl;
  std::cout << "offset_y : " << direction_offset.second.y() << std::endl;
  if (direction == "false") {
    return false;
  }
  return true;
}

//------DEVEL

//! проверит может ли фигура из руки ходить на клетку
bool ChessLogic::move(QPoint to) {
  QPair <int, QPoint> direction_offset = this->get_direction_offset(to);
  return this->test_direction_offset(direction_offset, to);
  //return true;
}

//! вернет направление и оффсет(куда сколько ходить)
QPair <int, QPoint> ChessLogic::get_direction_offset(QPoint to) {
  int direction = BAD_DIRECTION; //! default
  int offset_x = to.x() - this->hand().x();
  int offset_y = to.y() - this->hand().y();

  if (offset_x == 0 or offset_y == 0) {
    direction = STRAIGHT;
  } else if (abs(offset_x) == abs(offset_y)) {
    direction = DIAGONAL;
  } else if ((abs(offset_x) == 2 and abs(offset_y) == 1) or
             (abs(offset_x) == 1 and abs(offset_y) == 2)) {
    direction = G;
  }
  return QPair <int, QPoint> (direction, QPoint(offset_x, offset_y));
}

/*
bool ChessLogic::move_to_direction(int direction) {
  QChar piece = this->piece(this->hand()).toLower();
  switch (direction) {
    case STRAIGHT:
      switch (piece.unicode()) {
        case QUEEN:
        case ROOK:
          return true;
        case PAWN:
        case KING:
          return true;
        default:
          return false;
      }
    case DIAGONAL:
      switch (piece.unicode()) {
        case QUEEN:
        case OFFICER:
          return true;
        case KING:
        case PAWN:
          return true;
        default:
          return false;
      }
    case G:
      switch (piece.unicode()) {
        case KNIGHT:
          return true;
        default:
          return false;
      }
    default:
      return false;
  }
}
*/


//! взять piece в руку
bool ChessLogic::get_piece(QPoint coordinate) {
  if (this->player() == WHITE and
      this->piece(coordinate).isLower()) {
  } else if (this->player() == BLACK and
             this->piece(coordinate).isUpper()) {
  } else {
    return false;
  }

  this->set_hand(coordinate);
  return true;
}

//! походить piecom из руки
bool ChessLogic::put_piece(QPoint to) {
  if (this->move(to)) {
    std::cout << "moved" << std::endl;
  } else {
    std::cout << "NOT! moved" << std::endl;
  }
  this->set_hand(QPoint(-1,-1));
  return true;
}

//! проверит клетку (для всеx кроме коня)
bool ChessLogic::check_cell(QPoint coordinate) {
  Q_UNUSED(coordinate);
  return true;
}
