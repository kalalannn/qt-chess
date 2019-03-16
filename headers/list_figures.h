#ifndef LIST_FIGURES_H
#define LIST_FIGURES_H

#include "../headers/figure.h"

#include <list>
#include <vector>

using namespace std;

/*!
 * \brief The ListFigures class
 */
class ListFigures {
public:
  ListFigures(Figure::Color);
  ~ListFigures();
  void print_list();
  Figure *list_figures[2][8];

private:
};

#endif //ARRAY_FIGURES_H
