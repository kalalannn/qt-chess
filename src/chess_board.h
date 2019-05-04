#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

//! Constants
#define SIZE 8
#define ROOK 'v'
#define KNIGHT 'j'
#define OFFICER 's'
#define QUEEN 'd'
#define KING 'k'
#define PAWN 'p'

//! QIncludes
#include <QObject>
#include <QVector>
#include <QPoint>

#include <iostream>

//! Chess Board abstraction
class ChessBoard : public QObject {
  Q_OBJECT

public:
  explicit ChessBoard(QObject *parent = nullptr);

  //--------GET_METHODS--------//
  QVector<QChar> board() { return m_board; }
  QChar piece(int index) { return m_board[index]; }

  void setCell(int index, QChar piece);

  //! Map function for QVector [0-7][0-7]
  static int index(QPoint coordinates){ return (coordinates.y() * SIZE) + coordinates.x(); }

  //--------LOGIC--------------//
  //! Create a new board and set default figures
  void new_board();

  //! Get/Move char from index/to index
  void move(int index_from, int index_to);

  //--------DEBUG--------------//
  //! Print a state of a board
  void print();


private:
	QVector <QChar> m_board;
};

#endif // CHESS_BOARD_H
