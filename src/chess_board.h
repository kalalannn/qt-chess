#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#define SIZE 8          //!< Size of a board
#define ROOK 'v'        //!< Rook value
#define KNIGHT 'j'      //!< Knight value
#define OFFICER 's'     //!< Officer value
#define QUEEN 'd'       //!< Queen value
#define KING 'k'        //!< King value
#define PAWN 'p'        //!< Pawn value

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QPair>

#include <iostream>

/*!
 * Chess Board abstraction
 */
class ChessBoard : public QObject {
  Q_OBJECT

public:
  explicit ChessBoard(QObject *parent = nullptr);
  /*!
   * \brief Get board
   * \return m_board
   */
  QVector<QChar> board() { return m_board; }

  /*!
   * \brief Get piece from index
   * \param index
   * \return piece
   */
  QChar piece(int index) { return m_board[index]; }

  /*!
   * \brief Set piece on index
   * \param index
   * \param piece
   */
  void setCell(int index, QChar piece);

  //! \defgroup MappingFunctions
  //! @{

  /*!
   * \brief Map function
   * \param coordinates
   * \return index on m_board
   */
  static int index(QPoint coordinates){ return (coordinates.y() * SIZE) + coordinates.x(); }

  /*!
   * \brief Map function
   * \param index
   * \return coordinate
   */
  static QPoint coord (int index) { return QPoint(index % SIZE, index/SIZE); }

  //! @}

  /*!
  * \brief Create a new board and set default figures
  */
  void new_board();

  /*!
   * \brief Move piece from to
   * \param index_from index
   * \param index_to index
   */
  void move(int index_from, int index_to);

  /*!
   * \brief Get current pieces on a board
   * \param color Color of pieces
   * \return Vector of pieces
   */
  QVector <QPoint> getActualPieces(int color);

  /*!
   * \brief Get equal piece on a board
   * \param coord_piece Coordinate and value of a piece
   * \return Another piece
   */
  QPoint getAnotherPiece(QPair <QPoint,QChar> coord_piece);

private:
  QVector <QChar> m_board; //!< Abstraction of Board
};

#endif // CHESS_BOARD_H
