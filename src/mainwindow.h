#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chess_board.h"
#include "chess_logic.h"
#include "chess_view.h"

//! QIncludes
#include <QMainWindow>


namespace Ui {
  class MainWindow;
}

class ChessApp: public QMainWindow {
  Q_OBJECT

public:
  explicit ChessApp(QWidget *parent = nullptr);
  ~ChessApp();

public slots:
    void viewClicked(const QPoint &field);

private:
  Ui::MainWindow *ui;
  ChessLogic     *logic;
  ChessView      *view;
  ChessBoard     *board;
};

#endif // MAINWINDOW_H
