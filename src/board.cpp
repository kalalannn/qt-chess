#include "../headers/board.h"

#define LINE 8

Cell::Cell(int x, int y, Figure *figure) {
  this->x = x;
  this->y = y;
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

Board::Board() {
  for (int i = 0; i < LINE; i++) {
    for (int y = 0; y < LINE; y++) {
      board[i][y] = new Cell(i, y, nullptr);
    }
  }
}

void Board::print_board() {
  for (int i = 0; i < LINE; i++) {
    for (int y = 0; y< LINE; y++) {
      cout << "Coord x :" << this->board[y][i]->get_coordinates().first << endl;
      cout << "Coord y :" << this->board[y][i]->get_coordinates().second<< endl;
    }
    cout << "Next: " <<endl;
  }

}

Board::~Board() {

}
