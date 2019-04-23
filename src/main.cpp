#include "./headers/mainwindow.h"
#include "../headers/chess_logic.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication Chess(argc, argv);
  ChessApp RootWidget;
  RootWidget.show();
  return Chess.exec();
}
