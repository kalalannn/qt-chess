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

//! Возьмет фигуру и вернет вектор поинтов всех возможных ходов
//! если нет возможных -> пустой вектор
//! !!!!!! ЭТА ФУНКЦИЯ ПРИОТРИТЕТНАЯ СЕЙЧАС
QVector <QPoint> ChessLogic::calculate_moves(QChar piece) {
  switch (piece.unicode()) {
    default:
      break;
  }
}

//-------/PRIOR

//-------НЕ_ДЕЛАТЬ


//! Ход игрока начался
//! Игрок нажал на ЛЮБУЮ клетку
//!
//! Kontroly -> calculate_moves
//! Скопирует фигуру в руку void set_hand() ->
//! return 0
//!
int ChessLogic::get_piece(QPoint coordinates) {
  QChar piece = m_board->piece(ChessBoard::index(coordinates));
  switch (piece.unicode()) {
    case 'k':
      break;
    default:
      break;
  }
  return 0;
}

//! Future
int ChessLogic::put_piece(QPoint coordinates) {
  Q_UNUSED(coordinates);
  return 0;
}

//------/НЕ_ДЕЛАТЬ
