#include "mainwindow.h"
#include "chess_logic.h"

#include <QApplication>

/*!
 * \author Nikolaj Vorobiev
 * \version 1.0
 */

int main(int argc, char *argv[]) {
  QApplication Chess(argc, argv);
  ChessApp RootWidget;
  RootWidget.show();
  return Chess.exec();
}
