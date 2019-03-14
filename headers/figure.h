#ifndef FIGURE_H
#define FIGURE_H

#include <cstdint>

/*! @brief White color */
//#define WHITE 0

/*! @brief Black color */
//#define BLACK 1

/*! @brief Пешка */
//#define PAWN 0

/*! @brief Тура */
//#define ROOK 1

/*! @brief Конь */
//#define KNIGHT 2

/*! @brief Офицер */
//#define BISHOP 3

/*! @brief Королева */
//#define QUEEN 4

/*! @brief Король */
//#define KING 5

/*!
 * Class Figure
 */
class Figure {
private:
  //! color of figure
  enum color {WHITE, BLACK};

  //! Rang of figure
  enum rang {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};

  //! x coordinate
  int8_t x;

  //! y coordinate
  int8_t y;

public:
  Figure();
};

#endif // FIGURE_H
