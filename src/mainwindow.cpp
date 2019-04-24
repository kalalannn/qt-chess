#include <iostream>
#include "./headers/mainwindow.h"
#include "ui_mainwindow.h"

ChessApp::ChessApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
	logic = new ChessLogic(this);
  view = new ChessView(this);
	logic->newGame();
	view->setBoard(logic->board());
  view->board()->print();

  logic->get_piece(QPoint(1,1));
  logic->put_piece(QPoint(1,2));
}

ChessApp::~ChessApp()
{
  delete ui;
}
