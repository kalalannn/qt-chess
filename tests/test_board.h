#ifndef TESTBOARD_H
#define TESTBOARD_H

#include <QtTest/QtTest>
#include <QString>
#include <chess_board.h>
#include <chess_logic.h>

class TestBoard : public QObject {
  Q_OBJECT

private slots:
  void init();
  void test_direction_offset();

private:
  ChessLogic     *logic;
  ChessBoard     *board;
};

#endif // TESTBOARD_H
