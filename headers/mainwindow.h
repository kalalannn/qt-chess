#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//! .h files
#include "chess_logic.h"
#include "chess_view.h"

//! QIncludes
#include <QMainWindow>

//! C++11 includes


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
