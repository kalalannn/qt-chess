#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include "chess_board.h"
#include "chess_logic.h"

#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QIcon>
#include <QMouseEvent>

/*!
 * Chess GUI
 */
class ChessView : public QWidget {
  Q_OBJECT

public:
  /*!
   * \brief The Highlight class
   */
  class Highlight {
  public:
      Highlight() {}
      virtual ~Highlight() {}
      virtual int type() const { return 0; }
  };

  /*!
   * \brief The FieldHighlight class
   */
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
      QPoint m_field; //!< Field coordinate
      QColor m_color; //!< Color of highlight
  };

  explicit ChessView(QWidget *parent = nullptr,
                     ChessBoard *board = nullptr,
                     ChessLogic *logic = nullptr);

  /*!
   * \brief Get board
   * \return m_board
   */
  ChessBoard* board()           { return m_board; }

  /*!
   * \brief Get logic
   * \return m_logic
   */
  ChessLogic* logic()           { return m_logic; }

  /*!
   * \brief Get size of field
   * \return m_fieldSize
   */
  QSize fieldSize() const       { return m_fieldSize; }

  /*!
   * \brief Get icon of a piece
   * \param type piece value
   * \return icon
   */
  QIcon piece(QChar type) const { return m_pieces.value(type, QIcon()); }

  /*!
   * \brief Set m_board to board
   * \param board
   */
  void setBoard(ChessBoard *board)  { m_board = board; }

  /*!
   * \brief Set m_logic to logic
   * \param logic
   */
  void setLogic(ChessLogic *logic)             { m_logic = logic; }

  /*!
   * \brief Set m_fieldSize to fieldSize
   * \param fieldSize
   */
  void setFieldSize(QSize fieldSize)          { m_fieldSize = fieldSize; updateGeometry(); }

  /*!
   * \brief Set icon for piece
   * \param type
   * \param icon
   */
  void setPiece(char type, const QIcon &icon) { m_pieces.insert(type, icon); update(); }

  /*!
   * \brief Set SizeHint
   * \return size
   */
  QSize sizeHint() const;

  /*!
   * \brief Create rectangle
   * \param column
   * \param rank
   * \return rectangle
   */
  QRect fieldRect(int column, int rank) const;

  /*!
   * \brief Transfer field from Widget coordinate to our
   * \param pt Widget coordinate
   * \return our coordinate
   */
  QPoint fieldAt(const QPoint &pt) const;

  /*!
   * \brief Catch mouse event and emit clicked
   * \param event
   */
  void mouseReleaseEvent(QMouseEvent *event);

  /*!
   * \brief Add Highlight
   * \param hl
   */
  void addHighlight(Highlight *hl)             { m_highlights.append(hl); update(); }

  /*!
   * \brief Remove Highlight
   * \param hl
   */
  void removeHighlight(Highlight *hl)          { m_highlights.removeOne(hl); update(); }

  /*!
   * \brief highlight
   * \param index
   * \return highlight at index
   */
  inline Highlight *highlight(int index) const { return m_highlights.at(index); }

  /*!
   * \brief highlightCount
   * \return count of highlights
   */
  inline int highlightCount() const            { return m_highlights.size(); }

signals:
  /*!
   * \brief Mouse was clicked
   */
  void clicked(const QPoint &);

public slots:
  /*!
   * \brief Mouse was clicked
   * \param field
   */
  void viewClicked(const QPoint &field);

protected:
  //! \defgroup PaintingMethods
  //! @{

  /*!
   * \brief paintEvent
   * \param event
   */
  void paintEvent(QPaintEvent *event);

  /*!
   * \brief drawColumn
   * \param painter
   * \param column
   */
  virtual void drawColumn(QPainter *painter, int column);

  /*!
   * \brief drawRank
   * \param painter
   * \param rank
   */
  virtual void drawRank(QPainter *painter, int rank);

  /*!
   * \brief drawField
   * \param painter
   * \param column
   * \param rank
   */
  virtual void drawField(QPainter *painter, int column, int rank);

  /*!
   * \brief drawPiece
   * \param painter
   * \param column
   * \param rank
   */
  virtual void drawPiece(QPainter *painter, int column, int rank);

  /*!
   * \brief drawHighlights
   * \param painter
   */
  virtual void drawHighlights(QPainter *painter);

  //! @}

private:
  QMap <QChar, QIcon> m_pieces;    //!< Mapping
  QSize m_fieldSize;               //!< Field Size
  QList <Highlight*> m_highlights; //!< Highlights
  FieldHighlight *m_selectedField; //!< Highlight field
  ChessBoard *m_board;             //!< Board
  ChessLogic *m_logic;             //!< Logic
};

#endif // CHESS_VIEW_H
