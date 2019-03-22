#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chess_algorithm.h"
#include "chess_view.h"

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
  ChessView *view;
};

#endif // MAINWINDOW_H
