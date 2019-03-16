#include "../headers/list_figures.h"

//! \brief Count of figures in row
#define FIGURES_COUNT 8

//! \brief y for white rang figures
#define WHITE_FIGURES_Y 0

//! \brief y for white pawns figures
#define WHITE_PAWNS_Y 1

//! \brief y for black rang figures
#define BLACK_FIGURES_Y 6

//! \brief y for black pawns figures
#define BLACK_PAWNS_Y 7

/*!
 * \brief ListFigures::ListFigures
 * \param color
 */
ListFigures::ListFigures(Figure::Color color) {
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

  // Generate Rangs figures
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 8; x++) {
      if (y == 0) {
        this->list_figures[y][x] = new Figure(color, rangs[x]);
      }
      else {
        this->list_figures[y][x] = new Figure(color, Figure::PAWN);
      }
    }
  }
}

void ListFigures::print_list() {
}

/*!
 * \brief ListFigures::~ListFigures
 */
ListFigures::~ListFigures() {

}
