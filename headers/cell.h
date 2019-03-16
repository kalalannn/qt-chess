#ifndef CELL_H
#define CELL_H

#include <iostream>
#include "figure.h"
using namespace std;
/*!
 * Cell клетка
 */
class Cell {
public:
  Cell(int, int, Figure *);
  ~Cell();
  pair <int, int> get_coordinates(); //! return coordinates
  Figure *get_figure();              //! return pointer to figure
  void change_figure(Figure *);      //! this->figure = <new_figure> || nullptr

private:
  int x; //! x coordinate
  int y; //! y coordinate
  Figure *figure; //! figure || nullptr
};

#endif // CELL_H
