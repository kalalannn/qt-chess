#ifndef LIST_FIGURES_H
#define LIST_FIGURES_H

#include "../headers/figure.h"

#include <list>
#include <vector>

using namespace std;

/*!
 * \brief The ListFigures class
 */
class ListFigures{
public:
  ListFigures(Figure::Color);
  ~ListFigures();
  void print_list();

private:
  list <Figure *> list_figures;
  vector <Figure::Rang> rangs = {
    Figure::ROOK,
    Figure::KNIGHT,
    Figure::BISHOP,
    Figure::KING,
    Figure::QUEEN,
    Figure::BISHOP,
    Figure::KNIGHT,
    Figure::ROOK
  };
};

#endif //ARRAY_FIGURES_H
