#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include "chess_board.h"

//! QIncludes
#include <QPointer>
#include <QPair>
#include <QChar>

#define WHITE true
#define BLACK false

#define BAD_DIRECTION -1
#define STRAIGHT 1
#define DIAGONAL 2
#define G 3



//! Chess Logic
class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr,
	                    QPointer <ChessBoard> board = nullptr);

  void set_board (QPointer <ChessBoard> board) { m_board = board ;     }
  void set_hand (QPoint coordinates)           { m_hand = coordinates; }
  void set_player (bool player)                { m_player = player; }

  QPointer <ChessBoard> board()   { return m_board; }
  QChar piece(QPoint coordinates) { return m_board->piece(ChessBoard::index(coordinates)); }
  QPoint hand()                   { return m_hand; }
  bool player()                   { return m_player; }

  void change_player() { m_player = not m_player; }

  //---------TESTED-------------//

  bool test_direction_offset(QPair <int,QPoint> direction_offset, QPoint to);
  QPair <int, QPoint> get_direction_offset(QPoint to);

  //-------------DEVEL-------------------//

  bool check_cell(QPoint coordinate);

  bool check_figure_direction(int direction);

  bool move(QPoint to);

  //----------НЕ_ДЕЛАТЬ__________________//
  bool get_piece(QPoint coordinate);
  bool put_piece(QPoint coordinate);


private:
	QPointer <ChessBoard> m_board;
	QPoint m_hand;
	bool m_player;
};

#endif // CHESS_LOGIC_H
