#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chess_board.h"
#include "chess_logic.h"
#include "chess_view.h"

//! QIncludes
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>


namespace Ui {
  class MainWindow;
}

class ChessApp: public QMainWindow {
  Q_OBJECT

public:
  explicit ChessApp(QWidget *parent = nullptr);
  ~ChessApp();


private slots:
    void on_actionNew_Game_triggered();

    void on_actionMat(bool color);

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionSave_Game_triggered();

    void on_actionLoad_Game_triggered();

    void on_actionAbout_triggered();

private:
  Ui::MainWindow *ui;
  QVector <ChessLogic *> v_logic;
  QVector <ChessView *> v_view;
  QVector <ChessBoard *> v_board;
  int maxIndex;

};

#endif // MAINWINDOW_H
