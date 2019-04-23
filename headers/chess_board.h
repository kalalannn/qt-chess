#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

//! Constants
#define SIZE 8

//! QIncludes
#include <QObject>
#include <QVector>

//! C++11 includes
#include <iostream>

//! Chess Board abstraction
class ChessBoard : public QObject {
  Q_OBJECT

public:
  explicit ChessBoard(QObject *parent = nullptr);

  //! Create a new board and set default figures
  void newBoard();

  //! Map function for QVector [0-7][0-7]
  static int index(int x, int y){ return (y * SIZE) + x; }

  //! Get/Move char from index/to index
  QChar piece(int index) { return m_board[index]; }
  void move(int index_from, int index_to);

  //! Print a state of a board
  void print();

private:
	//! Board
	QVector <QChar> m_board;
};

#endif // CHESS_BOARD_H
