#ifndef TESTBOARD_H
#define TESTBOARD_H

#include <QtTest/QtTest>
#include <QString>
#include <chess_board.h>

class TestBoard : public QObject {
  Q_OBJECT

private slots:
  void initTestCase();
  void testInit();
  void testNewBoard();
  void cleanupTestCase();

private:
  QPointer<ChessBoard> test_b;
};

#endif // TESTBOARD_H
