#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H
