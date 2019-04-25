#include "test_board.h"

/*
 * initialize all values needed for tests
 */
void TestBoard::initTestCase() {
  test_b = new ChessBoard();
}

/*
 * check if initialization was good
 */
void TestBoard::testInit() {
  QVERIFY(test_b);
}

void TestBoard::testNewBoard() {
//  test_b->new_board();
//  QCOMPARE(test_b->board(), vec);
}

/*
 * clean up initialized values
 */
void TestBoard::cleanupTestCase() {

}

QTEST_MAIN(TestBoard);
