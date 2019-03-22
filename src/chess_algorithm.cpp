#include "../headers/chess_algorithm.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent) : QObject (parent){

}

void ChessAlgorithm::newGame() {
  m_board = new ChessBoard(this);
  m_board->newBoard();
}

void ChessAlgorithm::test() {
  m_board->test();
}

