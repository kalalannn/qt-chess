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
  int x = 0;
  int y1, y2;

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

  // white color
  if (color == Figure::WHITE) {
    y1 = WHITE_FIGURES_Y;
    y2 = WHITE_PAWNS_Y;
  }
  // black color
  else {
    y1 = BLACK_FIGURES_Y;
    y2 = BLACK_PAWNS_Y;
  }

  // Generate Rangs figures
  for (Figure::Rang rang: rangs) {
    this->list_figures.push_back(new Figure(color, rang));
    x++;
  }
  x = 0;

  // Generate PAWNS figures
  for (; x < FIGURES_COUNT;) {
    this->list_figures.push_back(new Figure(color, Figure::PAWN));
    x++;
  }
}

void ListFigures::print_list() {
  cout << "Full List: " << endl;
  for (auto figure: this->list_figures) {
    cout << "============" << endl;
    cout << "Color: " << figure->get_color() << endl;
    cout << "Rang: " << figure->get_rang() << endl;
    cout << "============" << endl;
  }
}

/*!
 * \brief ListFigures::~ListFigures
 */
ListFigures::~ListFigures() {

}
