#include "./headers/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication Chess(argc, argv);
  ChessApp RootWidget;
  RootWidget.show();

  return Chess.exec();
}
