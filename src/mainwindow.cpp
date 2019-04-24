#include <iostream>
#include "./headers/mainwindow.h"
#include "ui_mainwindow.h"

ChessApp::ChessApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);

  board = new ChessBoard(this);
  logic = new ChessLogic(this, board);
  view = new ChessView(this, board);

  board->print();
  logic->get_piece(QPoint(1,1));
  logic->put_piece(QPoint(1,2));
}

ChessApp::~ChessApp()
{
  delete ui;
}
