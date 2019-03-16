#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "figure.h"
#include "cell.h"
using namespace std;
/*!
 * Board with cells(8*8=64)
 */
class Board {
public:
  Board(); //! Init function
  ~Board();
  void create_board();            //! Initialisation of (Cell *)board;
  void create_figures();          //! Initialisation of white and black arrays
  void give_figures_on_a_board(); //! Give figures from black and white arrays on a board
  void print_board();             //! Print the actual state of a board
  void start();                   //! Start a game

private:
  Cell *board[8][8];         //! board
  Figure *black_array[2][8]; //! array of black figures
  Figure *white_array[2][8]; //! array of white figures
};

#endif //BOARD_H
