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

private slots:
    void on_actionNew_Game_triggered();

private:
  Ui::MainWindow *ui;
  QVector <ChessLogic *> v_logic;
  QVector <ChessView *> v_view;
  QVector <ChessBoard *> v_board;
  int maxIndex;

  ChessView::FieldHighlight *m_selectedField;
};

#endif // MAINWINDOW_H
