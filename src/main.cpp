#include "./headers/mainwindow.h"
#include "../headers/list_figures.h"
#include "../headers/board.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {
  /*!
  QApplication ChessApp(argc, argv);
  MainWindow RootWidget;
  RootWidget.show();
  */
  /*
  ListFigures *white_list = new ListFigures(Figure::WHITE);
  ListFigures *black_list = new ListFigures(Figure::BLACK);
  cout << "White" << endl;
  white_list->print_list();
  cout << "Black" << endl;
  black_list->print_list();
  */
  Board *b = new Board();
  b->print_board();



  return 0;
  //return ChessApp.exec();
}
