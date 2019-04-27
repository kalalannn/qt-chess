#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include "chess_board.h"

//! QIncludes
#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QIcon>
#include <QMouseEvent>


//! Chess GUI
class ChessView : public QWidget {
  Q_OBJECT

public:
  explicit ChessView(QWidget *parent = nullptr,
                     QPointer <ChessBoard> board = nullptr);

  QPointer <ChessBoard> board() { return m_board; }
  QSize fieldSize() const       { return m_fieldSize; }
  QIcon piece(QChar type) const { return m_pieces.value(type, QIcon()); }

  //! Set/Get board
  void setBoard(QPointer <ChessBoard> board)  { m_board = board; }
  void setFieldSize(QSize fieldSize)          { m_fieldSize = fieldSize; updateGeometry(); }
  void setPiece(char type, const QIcon &icon) { m_pieces.insert(type, icon); update(); }

  QSize sizeHint() const;
  QRect fieldRect(int column, int rank) const;


protected:
  void paintEvent(QPaintEvent *event);
  virtual void drawColumn(QPainter *painter, int column);
  virtual void drawRank(QPainter *painter, int rank);
  virtual void drawField(QPainter *painter, int column, int rank);
  virtual void drawPiece(QPainter *painter, int column, int rank);


  //---------NOT_IMPLEMENTED-------------//

private:
  QPointer <ChessBoard> m_board;
  QMap <QChar, QIcon>    m_pieces;
  QSize                 m_fieldSize;
};

#endif // CHESS_VIEW_H
