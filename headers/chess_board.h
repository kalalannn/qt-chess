#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#define SIZE 8

#include <QObject>
#include <QVector>
#include <iostream>

using namespace std;
class ChessBoard : public QObject {
  Q_OBJECT

public:
  explicit ChessBoard(QObject *parent = nullptr);

  void newBoard();
  QChar data(int x, int y) {return m_board[y * SIZE + x];}
  void setData(int x, int y, QChar value) {m_board[y * SIZE + x] = value;}
  void removeData(int x, int y) {m_board[y * SIZE + x] = ' ';}
  void test();

  void print();

private:
  QVector <QChar> m_board;
};

#endif // CHESS_BOARD_H
