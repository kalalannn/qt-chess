#include "../headers/chess_algorithm.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent) : QObject (parent){
  createBoard();
}

void ChessAlgorithm::createBoard() {
  board = new ChessBoard(this);
}

void ChessAlgorithm::print() {
  board->test();
}

