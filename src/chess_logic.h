#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include "chess_board.h"

#include <QPointer>
#include <QPair>
#include <QChar>

#define WHITE true  //!< White player value
#define BLACK false //!< Black player value

#define STRAIGHT 1            //!< Straight direction value
#define DIAGONAL 2            //!< Diagonal direction value
#define STRAIGHT_ROCKIROVKA 3 //!< Rokirovka value

/*!
 * Logic of ChessApp
 */
class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr,
	                    QPointer <ChessBoard> board = nullptr);

  /*!
   * \brief Set m_board to board
   * \param board
   */
  void setBoard (QPointer <ChessBoard> board) { m_board = board; }

  /*!
   * \brief Set m_hand to coordinates
   * \param coordinates
   */
  void setHand (QPoint coordinates)           { m_hand = coordinates; }

  /*!
   * \brief Set m_player to player
   * \param player
   */
  void setPlayer (bool player)                { m_player = player; }

  /*!
   * \brief Change player
   */
  void changePlayer()                         { m_player = not m_player; }

  /*!
   * \brief Set m_kings
   * \param color Color of King
   * \param coordinate New King coordinate
   */
  void setKing(bool color, QPoint coordinate);

  /*!
   * \brief Set m_king_was_moved
   * \param color Color of King
   * \param state New state
   */
  void setKingWasMoved(int color, bool state);

  /*!
   * \brief Concatenate conc and m_output
   * \param conc
   */
  void concOutput (QString conc)              { m_output += conc; }
  void concOutput (QChar conc)                { m_output += conc; }

  /*!
   * \brief Get board
   * \return m_board
   */
  QPointer <ChessBoard> board()   { return m_board; }

  /*!
   * \brief Get piece from coordinate
   * \param coordinates
   * \return piece
   */
  QChar piece(QPoint coordinates) { return m_board->piece(ChessBoard::index(coordinates)); }

  /*!
   * \brief Get hand
   * \return m_hand
   */
  QPoint hand()                   { return m_hand; }

  /*!
   * \brief Get color of current player
   * \return m_player
   */
  bool player()                   { return m_player; }

  /*!
   * \brief Get King
   * \param color Color of King
   * \return m_king
   */
  QPoint king(bool color);

  /*!
   * \brief Get state of King
   * \param color Color of King
   * \return m_king_was_moved
   */
  bool kingWasMoved(int color);

  /*!
   * \brief Get Chess notation
   * \return m_output
   */
  QString output()                { return m_output; }

  /*!
   * \brief Debug Method
   */
  void Debug();

  /*! @defgroup GetCells Static methods for getting cells
   * @{
   */
  /*!
   * \brief Get availible knight cells from coordinate
   * \param coordinate
   * \return cells
   */
  static QVector <QPoint> getKnightCells(QPoint coordinate);

  /*!
   * \brief Get availible straight cells from coordinate
   * \param coordinate
   * \return cells
   */
  static QVector <QPoint> getStraightCells(QPoint coordinate);

  /*!
   * \brief Get availible diagonal cells from coordinate
   * \param coordinate
   * \return cells
   */
  static QVector <QPoint> getDiagonalCells(QPoint coordinate);

  /*!
   * \brief Get availible King cells from coordinate
   * \param coordinate
   * \return cells
   */
  static QVector <QPoint> getKingCells(QPoint coordinate);

  /*!
   * \brief Get cells between cell and attacker
   * \param cell Cell coordinate
   * \param attacker Attacker coordinate
   * \return cells
   */
  static QVector <QPoint> getCellsToCoordinate(QPoint cell, QPoint attacker);

  /*!
   * @}
   */

  /*!
   * \brief Get attackers of cell
   * \param color Color of piece on cell
   * \param cell Coordinate
   * \return cells of attackers
   */
  QVector <QPoint> cellAttackers(bool color, QPoint cell);

  /*!
   * \brief Control of mat (Game over)
   * \param color Color of looser
   * \return true/false
   */
  bool isMat(bool color);

  /*!
   * \brief Check every cell to coordinate
   * \param from Begin coordinate
   * \param offset_x X offset
   * \param offset_y Y offset
   * \param direction Direction
   * \return cells
   */
  bool checkCellsToCoordinate(QPoint from, int offset_x, int offset_y, int direction);

  /*!
   * \brief Check if piece from coordinate can move to coordinate
   * \param from Coordinate
   * \param to Coordinate
   * \return true/false
   */
  bool canMove(QPoint from, QPoint to);

  /*!
   * \brief Try to move
   * \param from coordinate
   * \param to coordinate
   * \param color Color of mover
   * \return true/false
   */
  bool tryMove(QPoint from, QPoint to, bool color);

  /*!
   * \brief Check final cell of move
   * \param from coordinate
   * \param to coordinate
   * \param color Color of mover
   * \return true/false
   */
  bool checkFinalCell(QPoint from, QPoint to, bool color);

  /*!
   * \brief After move will register move in chess notation
   * \param from coordinate
   * \param to coordinate
   * \param sach isSach
   * \param mat isMat
   * \param attack isPiece on to
   * \param rokirovka_dlouha isRokirovkaDlouha
   * \param rokirovka_kratka isRokirovkaKratka
   * \param color Color of mover
   */
  void registerMove (QPoint from, QPoint to, bool sach, bool mat, bool attack,
                     bool rokirovka_dlouha, bool rokirovka_kratka, bool color);

  /*!
   * \brief Transfer our position to chess notation
   * \param coordinate
   * \return transfered coordinates
   */
  QPair <QChar,QChar> transferPos(QPoint coordinate);

  /*!
   * \brief Get piece from coordinate
   * \param coordinate
   * \return success/fail
   */
  bool getPiece(QPoint coordinate);

  /*!
   * \brief Put piece to coordinate
   * \param coordinate
   * \return success/fail
   */
  bool putPiece(QPoint coordinate);

signals:
  /*!
   * \brief If isMat returns true this signal will be emitted
   * \param color
   */
  void onMat(bool color);

private:
  QPointer <ChessBoard> m_board;  //!< Board
  QPoint                m_hand;   //!< Hand
  bool                  m_player; //!< Current player
  QPair <QPoint,QPoint> m_kings;  //!< Kings position
  QPair <bool,bool>     m_king_was_moved; //!< Kings states
  QString               m_output; //!< Output in chess notation
};

#endif // CHESS_LOGIC_H
