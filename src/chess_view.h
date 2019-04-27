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
  class Highlight {
  public:
      Highlight() {}
      virtual ~Highlight() {}
      virtual int type() const { return 0; }
  };

  class FieldHighlight : public Highlight {
  public:
      enum { Type = 1 };
      FieldHighlight(int column, int rank, QColor color)
          : m_field(column, rank), m_color(color) {}
      inline int column() const { return m_field.x(); }
      inline int rank() const { return m_field.y(); }
      inline QColor color() const { return m_color; }
      int type() const { return Type; }
  private:
      QPoint m_field;
      QColor m_color;
  };

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

  QPoint fieldAt(const QPoint &pt) const;
  void mouseReleaseEvent(QMouseEvent *event);

  void addHighlight(Highlight *hl)             { m_highlights.append(hl); update(); }
  void removeHighlight(Highlight *hl)          { m_highlights.removeOne(hl); update(); }
  inline Highlight *highlight(int index) const { return m_highlights.at(index); }
  inline int highlightCount() const            { return m_highlights.size(); }

signals:
  void clicked(const QPoint &);


protected:
  void paintEvent(QPaintEvent *event);
  virtual void drawColumn(QPainter *painter, int column);
  virtual void drawRank(QPainter *painter, int rank);
  virtual void drawField(QPainter *painter, int column, int rank);
  virtual void drawPiece(QPainter *painter, int column, int rank);
  virtual void drawHighlights(QPainter *painter);


  //---------NOT_IMPLEMENTED-------------//

private:
  QPointer <ChessBoard> m_board;
  QMap <QChar, QIcon>    m_pieces;
  QSize                 m_fieldSize;
  QList<Highlight*> m_highlights;
};

#endif // CHESS_VIEW_H
