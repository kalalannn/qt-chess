#include "./headers/mainwindow.h"
#include "../headers/chess_algorithm.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication Chess(argc, argv);
  ChessApp RootWidget;
  RootWidget.show();


  return Chess.exec();
}
