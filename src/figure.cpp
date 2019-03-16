#include "../headers/figure.h"

Figure::Figure(Color color, Rang rang) {
  this->color = color;
  this->rang = rang;
}

Figure::~Figure() {
}

Figure::Color Figure::get_color() {
  return this->color;
}

Figure::Rang Figure::get_rang() {
  return this->rang;
}
