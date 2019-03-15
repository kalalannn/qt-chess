#include "../headers/list_figures.h"

//! \brief Count of figures in row
#define FIGURES_COUNT 8

//! \brief y for white rang figures
#define WHITE_FIGURES_Y 1

//! \brief y for white pawns figures
#define WHITE_PAWNS_Y 2

//! \brief y for black rang figures
#define BLACK_FIGURES_Y 7

//! \brief y for black pawns figures
#define BLACK_PAWNS_Y 8

/*!
 * \brief ListFigures::ListFigures
 * \param color
 */
ListFigures::ListFigures(Figure::Color color){
  int x = Figure::a;
  int y1, y2;

  // white color
  if(color == Figure::WHITE){
    y1 = WHITE_FIGURES_Y;
    y2 = WHITE_PAWNS_Y;
  }
  // black color
  else {
    y1 = BLACK_FIGURES_Y;
    y2 = BLACK_PAWNS_Y;
  }

  // Generate Rangs figures
  for (Figure::Rang rang: ListFigures::rangs){
    this->list_figures.push_back(new Figure(color, rang));
    this->list_figures.back()->set(x, y1);
    x++;
  }
  x = Figure::a;

  // Generate PAWNS figures
  for (; x < FIGURES_COUNT + 1;){
    this->list_figures.push_back(new Figure(color, Figure::PAWN));
    this->list_figures.back()->set(x, y2);
    x++;
  }
}

void ListFigures::print_list(){
  cout << "Full List: " << endl;
  for (auto figure: this->list_figures){
    cout << "============" << endl;
    cout << "Color: " << figure->get_color() << endl;
    cout << "Rang: " << figure->get_rang() << endl;
    cout << "Coordinates: \n" << "x: "<< figure->get_coordinates().first << endl;
    cout << "y: "<< figure->get_coordinates().second << endl;
    cout << "============" << endl;
  }
}

/*!
 * \brief ListFigures::~ListFigures
 */
ListFigures::~ListFigures(){

}
