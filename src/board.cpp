#include "../headers/board.h"
#include "../headers/list_figures.h"

#define LINE 8

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

Board::Board() {
  for (int y = 0; y < LINE; y++) {
    for (int x = 0; x < LINE; x++) {
      board[y][x] = new Cell(y, x, nullptr);
    }
  }

  Figure::Rang rangs[] = {
    Figure::ROOK,
    Figure::KNIGHT,
    Figure::BISHOP,
    Figure::KING,
    Figure::QUEEN,
    Figure::BISHOP,
    Figure::KNIGHT,
    Figure::ROOK
  };

  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < LINE; x++) {
      if (y == 0) {
        this->white_list[y][x] = new Figure(Figure::WHITE, rangs[x]);
      }
      else {
        this->white_list[y][x] = new Figure(Figure::WHITE, Figure::PAWN);
      }
    }
  }

  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < LINE; x++) {
      if (y == 0) {
        this->black_list[y][x] = new Figure(Figure::BLACK, rangs[x]);
      }
      else {
        this->black_list[y][x] = new Figure(Figure::BLACK, Figure::PAWN);
      }
    }
  }
}

void Board::start() {
  //! \brief add white figures
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x< LINE; x++) {
      this->board[y][x]->change_figure(this->white_list[y][x]);
    }
  }

  //! \brief add black figures
  for (int y = LINE - 1, i = 0; y > 5; y--, i++) {
    for (int x = 0; x < LINE; x++) {
      this->board[y][x]->change_figure(this->black_list[i][x]);
    }
  }
}

void Board::print_board() {
  for (int y = 0; y < LINE; y++) {
    cout << "Line: " << y << endl;
    for (int x = 0; x < LINE; x++) {
      if (this->board[y][x]->get_figure() != nullptr) {
        cout << "x,y: "
             << this->board[y][x]->get_coordinates().first << ", "
             << this->board[y][x]->get_coordinates().second<< ", Color : "
             << this->board[y][x]->get_figure()->get_color()<< ", Rang : "
             << this->board[y][x]->get_figure()->get_rang()
             << endl;
      }
    }
  }

}

Board::~Board() {

}
