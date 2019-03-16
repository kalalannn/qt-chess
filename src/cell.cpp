#include "../headers/cell.h"

Cell::Cell(int y, int x, Figure *figure) {
  this->y = y;
  this->x = x;
  this->figure = figure;
}

pair <int, int> Cell::get_coordinates() {
  return make_pair(this->x, this->y);
}

Figure* Cell::get_figure() {
  return this->figure;
}

void Cell::change_figure(Figure *figure) {
  this->figure = figure;
}

Cell::~Cell() {

}
