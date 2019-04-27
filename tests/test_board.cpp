#include "test_board.h"

/* Y
 * ^
 * |
 * 7 |R|J|O|Q|K|O|J|R|
 * 6 |P|P|P|P|P|P|P|P|
 * 5 | | | | | | | | |
 * 4 | | | | | | | | |
 * 3 | | | | | | | | |
 * 2 | | | | | | | | |
 * 1 |p|p|p|p|p|p|p|p|
 * 0 |r|j|o|q|k|o|j|r|
 *    0 1 2 3 4 5 6 7 -> X
 */

/*
 * initialize all values needed for tests
 */
void TestBoard::init() {
  board = new ChessBoard(this);
  logic = new ChessLogic(this, board);
}

/*
 * check if initialization was good
 */
void TestBoard::test_direction_offset() {
  logic->set_hand(QPoint(0,0)); //тура 0 +
  logic->get_direction_offset(QPoint(0,7));

  logic->set_hand(QPoint(0,0)); //тура + 0
  logic->get_direction_offset(QPoint(7,0));

  logic->set_hand(QPoint(7,7)); //тура - 0
  logic->get_direction_offset(QPoint(0,7));

  logic->set_hand(QPoint(7,7)); //тура 0 -
  logic->get_direction_offset(QPoint(7,0));

  logic->set_hand(QPoint(2,0)); //офицер + +
  logic->get_direction_offset(QPoint(7,5));

  logic->set_hand(QPoint(2,0)); //офицер - +
  logic->get_direction_offset(QPoint(0,2));

  logic->set_hand(QPoint(2,7)); //офицер - -
  logic->get_direction_offset(QPoint(0,5));

  logic->set_hand(QPoint(2,7)); //офицер - +
  logic->get_direction_offset(QPoint(7,2));
}

QTEST_MAIN(TestBoard);
