#ifndef CHESS_ALGORITHM_H
#define CHESS_ALGORITHM_H

#include "../headers/chess_board.h"

#include <QObject>

class ChessAlgorithm  : public QObject {
  Q_OBJECT

public:
  explicit ChessAlgorithm(QObject *parent = nullptr);
  void createBoard();
  void print();

private:
  ChessBoard *board;
};

#endif // CHESS_ALGORITHM_H
