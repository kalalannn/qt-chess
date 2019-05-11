#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

ChessApp::ChessApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->maxIndex = 0;
  ui->setupUi(this);
  on_actionNew_Game_triggered();
}

ChessApp::~ChessApp() {
  delete ui;
}

void ChessApp::on_actionNew_Game_triggered() {
  v_board.append(new ChessBoard(this));
  v_logic.append(new ChessLogic(this, v_board.last()));
  v_view.append(new ChessView(this, v_board.last(), v_logic.last()));

  maxIndex = 1 + ui->tabWidget->addTab(v_view.last(),QString("Game " + QString::number(maxIndex)));
}
