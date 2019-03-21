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

  void init();
  char data(int x, int y);
  void set_data(int x, int y, char);
  void remove_data(int x, int y);
  void test();

  void print();

private:
  QVector < char > m_board;
};

#endif // CHESS_BOARD_H
