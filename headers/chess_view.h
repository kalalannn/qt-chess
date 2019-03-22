#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include <QObject>
#include <QPointer>

#include "chess_board.h"

class ChessView : public QObject {
  Q_OBJECT

public:
  explicit ChessView(QObject *parent = nullptr);
  void setBoard(QPointer <ChessBoard> board) {m_board = board;}
  QPointer <ChessBoard> board() {return m_board;}

private:
  QPointer <ChessBoard> m_board;
};

#endif // CHESS_VIEW_H
