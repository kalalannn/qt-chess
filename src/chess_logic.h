#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include "chess_board.h"

//! QIncludes
#include <QPointer>
#include <QPair>
#include <QChar>

#define WHITE true
#define BLACK false

#define STRAIGHT 1
#define DIAGONAL 2
#define STRAIGHT_ROCKIROVKA 3

//! Chess Logic
class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr,
	                    QPointer <ChessBoard> board = nullptr);

  //--------SET_METHODS--------//
  void setBoard (QPointer <ChessBoard> board) { m_board = board ;     }
  void setHand (QPoint coordinates)           { m_hand = coordinates; }
  void setPlayer (bool player)                { m_player = player; }
  void changePlayer()                         { m_player = not m_player; }
  void setKing(bool color, QPoint coordinate);
  void setKingWasMoved(int color, bool state);

  //--------GET_METHODS--------//
  QPointer <ChessBoard> board()   { return m_board; }
  QChar piece(QPoint coordinates) { return m_board->piece(ChessBoard::index(coordinates)); }
  QPoint hand()                   { return m_hand; }
  bool player()                   { return m_player; }
  QPoint king(bool color);
  bool kingWasMoved(int color);

  //--------DEBUG--------------//

  //--------LOGIC--------------//

  //---------TESTING-----------//
  static QVector <QPoint> getKnightCells(QPoint coordinate);
  static QVector <QPoint> getStraightCells(QPoint coordinate);
  static QVector <QPoint> getDiagonalCells(QPoint coordinate);
  static QVector <QPoint> getAllCells(QPoint coordinate);
  static QVector <QPoint> getKingCells(QPoint coordinate);
  QVector <QPoint> cellAttackers(int color, QPoint cell);
  bool isMat(int color, QPoint cell);
  bool checkCellsToCoordinate(QPoint from, int offset_x, int offset_y, int direction);
  bool canMove(QPoint from, QPoint to);
  bool tryMove(QPoint from, QPoint to);
  //---------DEVEL-------------//


  bool checkFinalCell(QPoint from, QPoint to);


  bool getPiece(QPoint coordinate);
  bool putPiece(QPoint coordinate);


private:
	QPointer <ChessBoard> m_board;
	QPoint                m_hand;
	bool                  m_player;
  QPair <QPoint,QPoint> m_kings;
  QPair <bool,bool>     m_king_was_moved;
};

#endif // CHESS_LOGIC_H
