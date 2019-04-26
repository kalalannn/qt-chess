#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include "chess_board.h"

//! QIncludes
#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QIcon>
#include <QMouseEvent>

//! C++11 includes


//! Chess GUI
class ChessView : public QWidget {
  Q_OBJECT

public:
  explicit ChessView(QWidget *parent = nullptr,
                     QPointer <ChessBoard> board = nullptr);

  //! Set/Get board
  void set_board(QPointer <ChessBoard> board) { m_board = board; }
  QPointer <ChessBoard> board() { return m_board; }

  //---------NOT_IMPLEMENTED-------------//

private:
  //! Board
  QPointer <ChessBoard> m_board;
  //! figures
  QMap <char, QIcon> pieces;
};

#endif // CHESS_VIEW_H
