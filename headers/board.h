#ifndef BOARD_H
#define BOARD_H

#include "list_figures.h"
#include <iostream>

using namespace std;

class Cell {
public:
  Cell(int, int, Figure *);
  ~Cell();

  //! \brief return coordinates
  pair <int, int> get_coordinates();

  //! \brief return pointer to figure
  Figure *get_figure();

  //! \brief this->figure = <new_figure> || nullptr
  void change_figure(Figure *);

private:
  int x;
  int y;
  Figure *figure;
};

class Board {
public:
  Board();
  ~Board();

  void print_board();

  void start();

private:
  Cell *board[8][8];

  Figure *black_list[2][8];
  Figure *white_list[2][8];
};
#endif //BOARD_H
