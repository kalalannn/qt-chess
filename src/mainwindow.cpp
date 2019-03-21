#include <iostream>
#include "./headers/mainwindow.h"
#include "ui_mainwindow.h"

ChessApp::ChessApp(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  alg = new ChessAlgorithm(this);
  alg->print();
}

ChessApp::~ChessApp()
{
  delete ui;
}
