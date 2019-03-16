#include "../headers/board.h"
#define LINE 8

void Board::create_board() {
  for (int y = 0; y < LINE; y++) {
    for (int x = 0; x < LINE; x++) {
      this->board[y][x] = new Cell(y, x, nullptr);
    }
  }
}

void Board::create_figures() {
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
        this->white_array[y][x] = new Figure(Figure::WHITE, rangs[x]);
      }
      else {
        this->white_array[y][x] = new Figure(Figure::WHITE, Figure::PAWN);
      }
    }
  }

  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < LINE; x++) {
      if (y == 0) {
        this->black_array[y][x] = new Figure(Figure::BLACK, rangs[x]);
      }
      else {
        this->black_array[y][x] = new Figure(Figure::BLACK, Figure::PAWN);
      }
    }
  }
}

Board::Board() {
  this->create_board();
  this->create_figures();
}

void Board::give_figures_on_a_board() {
  //! give white figures
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x< LINE; x++) {
      this->board[y][x]->change_figure(this->white_array[y][x]);
    }
  }
  //! give black figures
  for (int y = LINE - 1, i = 0; y > 5; y--, i++) {
    for (int x = 0; x < LINE; x++) {
      this->board[y][x]->change_figure(this->black_array[i][x]);
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

void Board::start() {
  give_figures_on_a_board();


}

Board::~Board() {

}
