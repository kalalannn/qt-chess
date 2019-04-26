#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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

ChessApp::ChessApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

  //ui->setupUi(this);

  board = new ChessBoard(this);
  logic = new ChessLogic(this, board);
  view = new ChessView(this, board);

  logic->get_piece(QPoint(0,0)); //тура 0 +
  logic->put_piece(QPoint(0,7));

  logic->get_piece(QPoint(0,0)); //тура + 0
  logic->put_piece(QPoint(7,0));

  logic->change_player();
  logic->get_piece(QPoint(7,7)); //тура - 0
  logic->put_piece(QPoint(0,7));

  logic->get_piece(QPoint(7,7)); //тура 0 -
  logic->put_piece(QPoint(7,0));

  logic->change_player();
  logic->get_piece(QPoint(2,0)); //офицер + +
  logic->put_piece(QPoint(7,5));

  logic->get_piece(QPoint(2,0)); //офицер - +
  logic->put_piece(QPoint(0,2));

  logic->change_player();
  logic->get_piece(QPoint(2,7)); //офицер - -
  logic->put_piece(QPoint(0,5));

  logic->get_piece(QPoint(2,7)); //офицер - +
  logic->put_piece(QPoint(7,2));


  exit (0);
}

ChessApp::~ChessApp()
{
  delete ui;
}
