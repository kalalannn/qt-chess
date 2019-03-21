#include "../headers/chess_board.h"

ChessBoard::ChessBoard(QObject *parent) : QObject (parent) {
  init();
}

void ChessBoard::init() {
  m_board.fill(' ', 64);
  int i = 0;
  for (char value : "vjsdksjvpppppppp") {
    m_board[i] = value;
    i++;
    if(i == 16)
      break;
  }
  i = 48;
  for (char value : "PPPPPPPPVJSDKSJV") {
    m_board[i] = value;
    i++;
    if(i == 64)
      break;
  }
}

char ChessBoard::data(int x, int y) {
  return m_board[y * SIZE + x];
}

void ChessBoard::set_data(int x, int y, char value) {
  m_board[y * SIZE + x] = value;
}

void ChessBoard::remove_data(int x, int y) {
  m_board[y * SIZE + x] = ' ';
}

void ChessBoard::test() {
  for (int i = 0; i < SIZE; i++) {
    for(int y = 0; y < SIZE; y++) {
      set_data(y,i, 'a');
    }
  }
  print();
  for (int i = 0; i < SIZE; i++) {
    for(int y = 0; y < SIZE; y++) {
      remove_data(y,i);
    }
  }
  print();
}

void ChessBoard::print() {
  int ind = 0;
  for (char x : m_board) {
    cout << "ind : " << ind << ", x :'" << x << "'" << endl;
    ind++;
  }
}
