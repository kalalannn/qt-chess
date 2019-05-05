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
void TestBoard::test_cells() {
  for (QPoint x: board->getActualPieces(WHITE)) {
     std::cout << x.x() << ", " << x.y() << std::endl;
  }
  for (QPoint x: board->getActualPieces(BLACK)) {
     std::cout << x.x() << ", " << x.y() << std::endl;
  }
  for (QPoint x: logic->getKingCells(QPoint(4,0))) {
     std::cout << x.x() << ", " << x.y() << std::endl;
  }

}

QTEST_MAIN(TestBoard);
