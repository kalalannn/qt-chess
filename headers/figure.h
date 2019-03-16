#ifndef FIGURE_H
#define FIGURE_H
/*!
 * Class Figure
 */
class Figure {
public:
  enum Color {WHITE, BLACK};                           //! Color of figure
  enum Rang {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING}; //! Rang of figure

  Figure(Color, Rang);
  ~Figure();
  Color get_color(); //! get color
  Rang get_rang();   //! get rang

private:
  Color color;
  Rang rang;
};

#endif // FIGURE_H
