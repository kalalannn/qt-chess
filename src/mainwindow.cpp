#include <iostream>
#include "./headers/mainwindow.h"
#include "ui_mainwindow.h"

ChessApp::ChessApp(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

ChessApp::~ChessApp()
{
  delete ui;
}
