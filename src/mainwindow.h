#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chess_board.h"
#include "chess_logic.h"
#include "chess_view.h"

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
  /*!
   * \brief New Game action
   */
  void on_actionNew_Game_triggered();

  /*!
   * \brief Mat action
   * \param color Color of looser
   */
  void on_actionMat(bool color);

  /*!
   * \brief tabClose action
   * \param index Index of tab
   */
  void on_tabWidget_tabCloseRequested(int index);

  /*!
   * \brief Save Game action
   */
  void on_actionSave_Game_triggered();

  /*!
   * \brief Load Game action
   */
  void on_actionLoad_Game_triggered();

  /*!
   * \brief About action
   */
  void on_actionAbout_triggered();

private:
  Ui::MainWindow *ui; //!< GUI
  QVector <ChessLogic *> v_logic; //!< Logic
  QVector <ChessView *> v_view;   //!< View
  QVector <ChessBoard *> v_board; //!< Board
  int maxIndex; //!< Max tab index
};

#endif // MAINWINDOW_H
