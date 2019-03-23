#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chess_logic.h"
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
	ChessLogic *logic;
  ChessView *view;
};

#endif // MAINWINDOW_H
