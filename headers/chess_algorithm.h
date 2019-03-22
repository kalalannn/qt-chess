#ifndef CHESS_ALGORITHM_H
#define CHESS_ALGORITHM_H

#include "chess_board.h"

#include <QObject>
#include <QPointer>

class ChessAlgorithm  : public QObject {
  Q_OBJECT

public:
  explicit ChessAlgorithm(QObject *parent = nullptr);

  void newGame();
  QPointer <ChessBoard> board() {return m_board;}

  void test();

private:
  QPointer <ChessBoard> m_board;
};

#endif // CHESS_ALGORITHM_H
