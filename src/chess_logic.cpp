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

//! проверит может ли фигура(кроме коня) походить на клетку
bool ChessLogic::check_cell(QPoint coordinate) {
  QChar piece = this->piece(coordinate);
  if (piece == QChar::Null) {
    // тут еще надо будет дописать
    // условия типо король под боем или
    // еще какие исключения

    return true;

  } else if (piece == 'P') {  // в скобках любой апперкейс
    // вот тут и ниже надо делать проверки юзера
    // акутуального

  } else if (piece == 'p') { // в скобках любой лоукейс

  }
  return true;
}

//! вот тут и в подобных функциях check_diag check_g
//! в цикле проходит все клетки от this->hand() до
//! coordinate_to при этом вызывая check_cell
//! это основная наша задача сейчас
//! эти функции проверяют возможность хода
//! и будут потом воланы
//!
int ChessLogic::check_straight(QPoint coordinate_to) {
  return 0;
}

int ChessLogic::check_diagonal(QPoint coordinate_to) {
  return 0;
}

int ChessLogic::check_g(QPoint coordinate_to) {
  return 0;
}

//! Возьмет фигуру из руки и вернет
//! true если может ходить на coordinate_to
//! false если не может
//! !!!!!!
//!
bool ChessLogic::check_move(QPoint coordinate_to) {
  Q_UNUSED(coordinate_to);

  QPoint coordinate_from = this->hand();
  if (coordinate_from == QPoint(-1,-1)) {
    return false;
  }
  QChar piece = this->piece(coordinate_from);

  switch(piece.unicode()) {
    case 'p':
      break;

  }

  return true;
}

//------/PRIOR

//------НЕ_ДЕЛАТЬ

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

//------/НЕ_ДЕЛАТЬ
