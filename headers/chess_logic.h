#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

//! .h files
#include "chess_board.h"

//! QIncludes
#include <QObject>
#include <QPointer>

//! C++11 includes


//! Chess Logic
class ChessLogic : public QObject {
  Q_OBJECT

public:
	explicit ChessLogic(QObject *parent = nullptr);

	//! Create a new game
	void newGame();

	QPointer <ChessBoard> board() { return m_board; }


  //---------NOT_IMPLEMENTED-------------//

  //-------------PRIOR-------------------//
  void set_hand(QChar piece); //! default hand == QChar::NULL;
  QChar hand();               //! заберет и наставит на default

  bool check_move(QPoint coordinate_to);

  //! POZOR для playera придумать какую нибудь легкую структуру EX: bool
  void change_player(void);
  bool player(void);


  //----------НЕ_ДЕЛАТЬ__________________//
  int get_piece(QPoint coordinates);
  int put_piece(QPoint coordinates);


private:
	//! Board
	QPointer<ChessBoard> m_board;

	//! hand
	QPair <QChar, QPoint> m_hand;


};

#endif // CHESS_LOGIC_H
