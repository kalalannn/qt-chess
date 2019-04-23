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

  //! Print a state of a board
  void print();

private:
	//! Board
	QVector <QChar> m_board;
};

#endif // CHESS_BOARD_H
