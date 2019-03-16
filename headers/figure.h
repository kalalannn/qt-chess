#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>


using namespace std;

/*!
 * \brief Class Figure
 */
class Figure {
public:
  //! \brief Color of figure
  enum Color {WHITE, BLACK};

  //! \brief Rang of figure
  enum Rang {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};

  Figure(Color, Rang);
  ~Figure();
  Color get_color();
  Rang get_rang();

private:
  Color color;
  Rang rang;
};

#endif // FIGURE_H
