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

//! Chess Logic
class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr,
	                    QPointer <ChessBoard> board = nullptr);

  //--------SET_METHODS--------//
  void set_board (QPointer <ChessBoard> board) { m_board = board ;     }
  void set_hand (QPoint coordinates)           { m_hand = coordinates; }
  void set_player (bool player)                { m_player = player; }
  void change_player()                         { m_player = not m_player; }

  //--------GET_METHODS--------//
  QPointer <ChessBoard> board()   { return m_board; }
  QChar piece(QPoint coordinates) { return m_board->piece(ChessBoard::index(coordinates)); }
  QPoint hand()                   { return m_hand; }
  bool player()                   { return m_player; }

  //--------DEBUG--------------//

  //--------LOGIC--------------//

  //---------TESTING-----------//
  static QVector <QPoint> getKnightCells(QPoint coordinate);
  static QVector <QPoint> getStraightCells(QPoint coordinate);
  static QVector <QPoint> getDiagonalCells(QPoint coordinate);
  static QVector <QPoint> getAllCells(QPoint coordinate);
  bool isCellOnAttack(QPoint coordinate);
  bool checkCellsToCoordinate(QPoint from, int offset_x, int offset_y, int direction);
  bool canMove(QPoint from, QPoint to);
  //---------DEVEL-------------//


  bool checkFinalCell(QPoint to);


  bool getPiece(QPoint coordinate);
  bool putPiece(QPoint coordinate);


private:
	QPointer <ChessBoard> m_board;
	QPoint                m_hand;
	bool                  m_player;
};

#endif // CHESS_LOGIC_H
