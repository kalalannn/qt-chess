#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../headers/chess_algorithm.h"

namespace Ui {
  class MainWindow;
}

class ChessApp: public QMainWindow {
  Q_OBJECT

public:
  explicit ChessApp(QWidget *parent = nullptr);
  ~ChessApp();

private:
  Ui::MainWindow *ui;
  ChessAlgorithm *alg;
};

#endif // MAINWINDOW_H
