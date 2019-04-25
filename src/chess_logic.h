#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

//! .h files
#include "chess_board.h"

//! QIncludes
#include <QObject>
#include <QPointer>


//! Chess Logic
class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr,
	                    QPointer <ChessBoard> board = nullptr);

  void set_board(QPointer <ChessBoard> board) { m_board = board ;     }
  void set_hand(QPoint coordinates)           { m_hand = coordinates; }

  QPointer <ChessBoard> board()   { return m_board; }
  QChar piece(QPoint coordinates) { return m_board->piece(ChessBoard::index(coordinates)); }
  QPoint hand()                   { return m_hand; }

  //---------NOT_IMPLEMENTED-------------//

  //-------------PRIOR-------------------//


  bool check_move(QPoint coordinate_to);

  //! POZOR для playera придумать какую нибудь легкую структуру EX: bool
  void change_player(void);
  bool player(void);


  int get_piece(QPoint coordinates);
  int put_piece(QPoint coordinates);

  //----------НЕ_ДЕЛАТЬ__________________//

private:
	QPointer <ChessBoard> m_board;

	//! Когда нажмет на поле координаты фигуры
	//! сохранятся в руку m_hand
	//! это лучше чем делать QPair <QChar, QPoint>
	//! QChar легко получим
	QPoint m_hand;

};

#endif // CHESS_LOGIC_H
