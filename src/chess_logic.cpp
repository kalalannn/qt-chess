#include "../headers/chess_logic.h"

//------READY
ChessLogic::ChessLogic(QObject *parent) : QObject (parent) {
}

void ChessLogic::newGame() {
  m_board = new ChessBoard(this);
  m_board->newBoard();
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
  return true;
}

//! Ход игрока начался
//! Игрок нажал на ЛЮБУЮ клетку
//!
//! Kontroly -> calculate_moves
//! Скопирует фигуру в руку void set_hand() ->
//! return 0
//!
int ChessLogic::get_piece(QPoint coordinates) {
  QChar piece = m_board->piece(ChessBoard::index(coordinates));
  m_hand.first = piece;
  m_hand.second = coordinates;
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
