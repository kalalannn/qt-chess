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

  enum X {a=1, b, c, d, e, f, g};

  typedef pair<int, int> Coordinates;

  Figure(Color color, Rang rang);
  ~Figure();
  void set(int, int);
  Coordinates get_coordinates();
  Color get_color();
  Rang get_rang();

private:
  Color color;
  Rang rang;

  //! \brief Coordinates(x, y)
  Coordinates coordinates;
};

#endif // FIGURE_H
