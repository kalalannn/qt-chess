#include "chess_logic.h"

ChessLogic::ChessLogic(QObject *parent,
                       QPointer <ChessBoard> board) : QObject (parent) {
  this->setBoard(board);
  this->setHand(QPoint(-1,-1));
  this->setPlayer(WHITE);
  this->setKing(WHITE, QPoint(0,4));
  this->setKing(BLACK, QPoint(7,4));
}

void ChessLogic::setKing(bool color, QPoint coordinate) {
  if(color == WHITE) {
    m_kings.first=coordinate;
  } else {
    m_kings.second = coordinate;
  }
}

QPoint ChessLogic::king(bool color) {
  if (color == WHITE) {
    return m_kings.first;
  } else {
    return m_kings.second;
  }
}
//------DEVEL


bool ChessLogic::checkCellsToCoordinate(QPoint from, int offset_x, int offset_y, int direction) {
  if (direction == STRAIGHT) {
    if (offset_x == 0) {
      if (offset_y > 0) {
        for(int i=1; i < abs(offset_y) ;i++) {
          if (not this->piece(QPoint(from.x(), from.y()+i)).isNull())  { return false; }
        }
      } else if (offset_y < 0) {
        for(int i=1; i < abs(offset_y) ;i++) {
          if (not this->piece(QPoint(from.x(), from.y()-i)).isNull())  { return false; }
        }
      }
    } else if (offset_y == 0) {
      if (offset_x > 0) {
        for(int i=1; i < abs(offset_x) ;i++) {
          if (not this->piece(QPoint(from.x()+i, from.y())).isNull())  { return false; }
        }
      } else if (offset_x < 0) {
        for(int i=1; i < abs(offset_x) ;i++) {
          if (not this->piece(QPoint(from.x()-i, from.y())).isNull())  { return false; }
        }
      }
    }
  } else if (direction == DIAGONAL) {
    if (offset_x > 0 and offset_y > 0) { // -> вверх
      for (int i=1; i<abs(offset_x) ;i++) {
        if (not this->piece(QPoint(from.x()+i, from.y()+i)).isNull())  { return false; }
      }
    } else if (offset_x > 0 and offset_y < 0) { // -> вниз
      for (int i=1; i<abs(offset_x) ;i++) {
        if (not this->piece(QPoint(from.x()+i, from.y()-i)).isNull())  { return false; }
      }
    } else if (offset_x < 0 and offset_y > 0) { // <- вверх
      for (int i=1; i<abs(offset_x) ;i++) {
        if (not this->piece(QPoint(from.x()-i, from.y()+i)).isNull())  { return false; }
      }
    } else if (offset_x < 0 and offset_y < 0) { // <- вниз
      for (int i=1; i<abs(offset_x) ;i++) {
        if (not this->piece(QPoint(from.x()-i, from.y()-i)).isNull())  { return false; }
      }
    }
  }
  return true;
}

bool ChessLogic::canMove(QPoint from, QPoint to) {
  int offset_x = to.x() - from.x();
  int offset_y = to.y() - from.y();
  if (offset_x == 0 or offset_y == 0) {   //Straight
    switch (this->piece(from).toLower().unicode()) {
        case QUEEN: case ROOK:
          if (not this->checkCellsToCoordinate(from, offset_x, offset_y, STRAIGHT)) { return false; }
          return true;

        case PAWN:
          if ((this->piece(from).isUpper() and offset_y > 0) or
              (this->piece(from).isLower() and offset_y < 0)) { return false; } // ход назад
          if (offset_x != 0) { return false; } // ход вбок
          else if (abs(offset_y) == 1) {
            if (not this->piece(to).isNull()) { return false; } //стоит фигура
          } else if (abs(offset_y) == 2) {
            if (not (from.y() == 1 or from.y() == 6)) { return false; } // не может ходить на 2 кл
            if (not this->checkCellsToCoordinate(from, offset_x, offset_y, STRAIGHT)) { return false; }
            if (not this->piece(to).isNull()) { return false; } //стоит фигура
          }
          else { return false; }
          return true;

        case KING:
          if (not (abs(offset_x) == 1 or abs(offset_y) == 1)) { return false; }
          return true;

        default:  return false;
      }
  } else if (abs(offset_x) == abs(offset_y)) {  //DIAGONAL;
      switch (this->piece(from).toLower().unicode()) {
        case QUEEN: case OFFICER:
          if (not this->checkCellsToCoordinate(from, offset_x, offset_y, DIAGONAL)) { return false; }
          return true;

        case KING:
          if (not (abs(offset_x) == 1 and abs(offset_y) == 1)) { return false; }
          return true;
        case PAWN:
          if (abs(offset_x) == 1 and abs(offset_y) == 1) {
            // атака пешки
            if (this->piece(QPoint(from.x()+offset_x, from.y()+offset_y)).isNull()) { return false; }
          }
          else { return false; }
          return true;

        default:  return false;
      }
    }
    else if ((abs(offset_x) == 2 and abs(offset_y) == 1) or
             (abs(offset_x) == 1 and abs(offset_y) == 2))
    {
      if (this->piece(from).toLower().unicode() == KNIGHT) { return true; }
      else { return false; }
    }
    else { return false; }
}

//! взять piece в руку
bool ChessLogic::getPiece(QPoint from) {
  if (this->player()      == WHITE and this->piece(from).isLower()) { }
  else if (this->player() == BLACK and this->piece(from).isUpper()) { }
  else { return false; }

  this->setHand(from);
  return true;
}

//! походить piecom из руки
bool ChessLogic::putPiece(QPoint to) {
  if (not this->canMove(this->hand(), to)) { return false; }
  if (not this->checkFinalCell(to)) { return false; }

  this->board()->move(ChessBoard::index(this->hand()), ChessBoard::index(to));

  //if (isCellOnAttack(this->))

  this->changePlayer();

  return true;
}

QVector <QPoint> ChessLogic::getKnightCells(QPoint coordinate) {
    QVector <QPoint> temp = QVector <QPoint> ();
    QVector <QPoint> ret = QVector <QPoint> ();
    temp.append(QPoint(coordinate.x() + 2, coordinate.y() + 1));
    temp.append(QPoint(coordinate.x() + 2, coordinate.y() - 1));
    temp.append(QPoint(coordinate.x() - 2, coordinate.y() + 1));
    temp.append(QPoint(coordinate.x() - 2, coordinate.y() - 1));

    temp.append(QPoint(coordinate.x() + 1, coordinate.y() + 2));
    temp.append(QPoint(coordinate.x() + 1, coordinate.y() - 2));
    temp.append(QPoint(coordinate.x() - 1, coordinate.y() + 2));
    temp.append(QPoint(coordinate.x() - 1, coordinate.y() - 2));
    for (QPoint coord : temp) {
        if (coord.x() >= 0 and coord.x() <= 7 and coord.y() >= 0 and coord.y() <= 7) {
            ret.append(coord);
        }
    }
    return ret;
}

QVector <QPoint> ChessLogic::getStraightCells(QPoint coordinate) {
    QVector <QPoint> ret = QVector <QPoint> ();
    for (int x=1; coordinate.x()+x <= 7; x++) { //вправо
        ret.append(QPoint(coordinate.x()+x, coordinate.y()));
    }
    for (int x=1; coordinate.x()-x >= 0; x++) { //влево
        ret.append(QPoint(coordinate.x()-x, coordinate.y()));
    }
    for (int y=1; coordinate.y()+y <= 7; y++) { //вверх
        ret.append(QPoint(coordinate.x(), coordinate.y()+y));
    }
    for (int y=1; coordinate.y()-y >= 0; y++) { //вниз
        ret.append(QPoint(coordinate.x(), coordinate.y()-y));
    }
    return ret;
}

QVector <QPoint> ChessLogic::getDiagonalCells(QPoint coordinate) {
    QVector <QPoint> ret = QVector <QPoint> ();
    for (int offset=1; coordinate.x()+offset <= 7 and coordinate.y()+offset <= 7;offset++) { //вв право
        ret.append(QPoint(coordinate.x()+offset,coordinate.y()+offset));
    }
    for (int offset=1; coordinate.x()-offset >= 0 and coordinate.y()+offset <= 7;offset++) { //вв лево
        ret.append(QPoint(coordinate.x()-offset,coordinate.y()+offset));
    }
    for (int offset=1; coordinate.x()+offset <= 7 and coordinate.y()-offset >= 0;offset++) { //вн право
        ret.append(QPoint(coordinate.x()+offset,coordinate.y()-offset));
    }
    for (int offset=1; coordinate.x()-offset >= 0 and coordinate.y()-offset >= 0;offset++) { //вн лево
        ret.append(QPoint(coordinate.x()-offset,coordinate.y()-offset));
    }
    return ret;
}

QVector <QPoint> ChessLogic::getAllCells(QPoint coordinate) {
    QVector <QPoint> all = QVector <QPoint> ();
    for (QPoint x: ChessLogic::getKnightCells(coordinate)) {
        all.append(x);
    }
    for (QPoint x: ChessLogic::getStraightCells(coordinate)) {
        all.append(x);
    }
    for (QPoint x: ChessLogic::getDiagonalCells(coordinate)) {
        all.append(x);
    }
    return all;
}

bool ChessLogic::isCellOnAttack(QPoint coordinate) {
    QVector <QPoint> all = ChessLogic::getAllCells(coordinate);
    for (auto x: all) {
        std::cout << "x: " << x.x() << " y: " << x.y() << std::endl;
    }
    return true;
}

bool ChessLogic::checkFinalCell (QPoint to) {
  if (this->player() == WHITE and
      (this->piece(to) == QChar::Null or this->piece(to).isUpper())) { }
  else if (this->player() == BLACK and
      (this->piece(to) == QChar::Null or this->piece(to).isLower())) { }
  else  { return false; }
  return true;
}
