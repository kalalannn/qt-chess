#include "../headers/figure.h"


Figure::Figure(Color color, Rang rang) {
  this->color = color;
  this->rang = rang;
}

Figure::~Figure(){
}

void Figure::set(int x, int y){
  this->coordinates.first = x;
  this->coordinates.second = y;
}

Figure::Coordinates Figure::get_coordinates(){
  return make_pair(this->coordinates.first, this->coordinates.second);
}

Figure::Color Figure::get_color(){
  return this->color;
}

Figure::Rang Figure::get_rang(){
  return this->rang;
}
