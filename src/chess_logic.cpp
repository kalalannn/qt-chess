#include "chess_logic.h"

//------READY
ChessLogic::ChessLogic(QObject *parent,
                       QPointer <ChessBoard> board) : QObject (parent) {
  this->set_board(board);
  this->set_hand(QPoint(-1,-1));
}


//------/READY

//------NOT_TESTED

//-----/NOT_TESTED

//------PRIOR

//! Возьмет фигуру из руки и вернет
//! true если может ходить на coordinate_to
//! false если не может
//! !!!!!! ЭТА ФУНКЦИЯ ПРИОТРИТЕТНАЯ СЕЙЧАС
//!
bool ChessLogic::check_move(QPoint coordinate_to) {
  Q_UNUSED(coordinate_to);

  //! взять из руки
  if (this->hand() == QPoint(-1,-1)) {
    return false;
  } else {
    return true;
  }
}

//! Ход игрока начался
//! Игрок нажал на ЛЮБУЮ клетку
//!
//! Kontroly -> calculate_moves
//! Скопирует фигуру в руку void set_hand() ->
//! return 0
//!
int ChessLogic::get_piece(QPoint coordinates) {

  //! взять в руку
  this->set_hand(coordinates);

  return 0;
}

//! проверит coordinates (можно ли ходить)
//! и походит
int ChessLogic::put_piece(QPoint coordinates) {
  if (this->check_move(coordinates)) {
    std::cout << "moved" << std::endl;
  }

  return 0;
}

//------/PRIOR

//------НЕ_ДЕЛАТЬ
//------/НЕ_ДЕЛАТЬ
