#include "chess_logic.h"

ChessLogic::ChessLogic(QObject *parent,
                       QPointer <ChessBoard> board) : QObject (parent) {
  setBoard(board);
  setHand(QPoint(-1,-1));
  setPlayer(WHITE);
  setKing(WHITE, QPoint(4,0));
  setKing(BLACK, QPoint(4,7));
  setKingWasMoved(WHITE, false);
  setKingWasMoved(BLACK, false);
}


void ChessLogic::Debug() {
  std::cout << "Hand:  x: " << this->hand().x() << ", y: " << this->hand().y() << std::endl;
  std::cout << "WhiteK: x: " << this->king(WHITE).x() << ", y: " << this->king(WHITE).y() << std::endl;
  for (auto x: this->cellAttackers(WHITE, this->king(WHITE))) {
    std::cout << "WAttacker:  x: " << x.x() << ", y: " << x.y() << std::endl;
  }
  std::cout << "BlackK: x: " << this->king(BLACK).x() << ", y: " << this->king(BLACK).y() << std::endl;
  for (auto x: this->cellAttackers(BLACK, this->king(BLACK))) {
    std::cout << "BAttacker:  x: " << x.x() << ", y: " << x.y() << std::endl;
  }
  std::cout << "========================================" << std::endl;

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

void ChessLogic::setKingWasMoved(int color, bool state) {
  if (color == WHITE) {
    m_king_was_moved.first = state;
  } else {
    m_king_was_moved.second = state;
  }
}

bool ChessLogic::kingWasMoved(int color) {
  if (color == WHITE) {
    return m_king_was_moved.first;
  } else {
    return m_king_was_moved.second;
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
  } else if (direction == STRAIGHT_ROCKIROVKA) {
    if (offset_x == -4) {
      for (int i=1; i < abs(offset_x); i++) {
        if (not this->piece(QPoint(from.x()-i, from.y())).isNull())  { return false; }
        if (not cellAttackers(this->player(), QPoint(from.x()-i, from.y())).isEmpty()) { return false; }
      }
    } else if (offset_x == 3) {
      for (int i=1; i < abs(offset_x); i++) {
        if (not this->piece(QPoint(from.x()+i, from.y())).isNull())  { return false; }
        if (not cellAttackers(this->player(), QPoint(from.x()+i, from.y())).isEmpty()) { return false; }
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
          if (offset_x == -4 or offset_x == 3) {
            if (not this->checkCellsToCoordinate(from, offset_x, offset_y, STRAIGHT_ROCKIROVKA)) { return false; }
          } else if (not (abs(offset_x) == 1 or abs(offset_y) == 1)) { return false; }
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
          if ((this->piece(from).isUpper() and offset_y > 0) or
              (this->piece(from).isLower() and offset_y < 0)) { return false; } // ход назад
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

QString ChessLogic::transferPos(QPoint coordinate) {
  QString str = "";
  str += QChar(coordinate.x() + int ('a'));
  str += QChar(coordinate.y() + int('1'));
  return str;
}

void ChessLogic::registerMove (QPair <QPoint,QChar> from, QPair <QPoint,QChar> to, bool sach) {
  QString output = "";
  QString fr =  this->transferPos(from.first).toLatin1().constData();
  QString t =  this->transferPos(to.first).toLatin1().constData();
  //QPoint another_piece = this->board()->getAnotherPiece(from.second);
  switch (from.second.toLower().unicode()) {
    case PAWN:
      output += t;
      if (to.second != QChar::Null) {
        output += 'x';
      }
      break;
  }
  if (sach) {
    output += '+';
  }
  std::cout << output.toLatin1().constData() << std::endl;

}

bool ChessLogic::tryMove(QPoint from, QPoint to, bool color) {
  QChar was_on_to = this->piece(to);

  if (this->piece(from).toLower().unicode() == KING) {
    if (not this->kingWasMoved(color)) { // rokirovka
      if (to.x() == 0 or to.x() == 7) {
        if (cellAttackers(color, this->king(color)).isEmpty()) {
          return true;
        } else { return false; }
      }
    }
    this->setKing(color, to); //ставим короля
  }

  // эммитация хода, проверка будет ли после хода шах
  this->board()->move(ChessBoard::index(from), ChessBoard::index(to));
  bool retval = cellAttackers(color, this->king(color)).isEmpty();
  // шаг обратно
  this->board()->move(ChessBoard::index(to), ChessBoard::index(from));
  // возвращаем фигуру, если она там была
  this->board()->setCell(ChessBoard::index(to), was_on_to);

  if (this->piece(from).toLower().unicode() == KING) {
    this->setKing(color, from); // возвращаем короля
  }
  return retval;
}

//! походить piecom из руки
bool ChessLogic::putPiece(QPoint to) {
  QPair <QPoint,QChar> was_on_from = QPair <QPoint,QChar> (this->hand(), this->piece(this->hand()));
  QPair <QPoint,QChar> was_on_to = QPair <QPoint,QChar> (to, this->piece(to));
  bool sach = false;
  if (not this->canMove(this->hand(), to)) { return false; }
  if (not this->checkFinalCell(this->hand(), to, this->player())) { return false; }

  if (this->tryMove(this->hand(), to, this->player())) {
    if (this->piece(this->hand()).toLower().unicode() == KING) {
      if (not this->kingWasMoved(this->player()) and to.x() == 0) { // rokirovka
          this->board()->move(ChessBoard::index(this->hand()), ChessBoard::index(QPoint(2,this->hand().y())));
          this->board()->move(ChessBoard::index(QPoint(0,this->hand().y())), ChessBoard::index(QPoint(3,this->hand().y())));
          this->setKing(this->player(), QPoint(2,this->hand().y()));
      } else if (not this->kingWasMoved(this->player()) and to.x() == 7) { // rokirovka
          this->board()->move(ChessBoard::index(this->hand()), ChessBoard::index(QPoint(6,this->hand().y())));
          this->board()->move(ChessBoard::index(QPoint(7,this->hand().y())), ChessBoard::index(QPoint(5,this->hand().y())));
          this->setKing(this->player(), QPoint(6,this->hand().y()));
      } else {
        this->board()->move(ChessBoard::index(this->hand()), ChessBoard::index(to));
        this->setKing(this->player(), to);
      }
      this->setKingWasMoved(this->player(), true);
    } else { //!KING
      this->board()->move(ChessBoard::index(this->hand()), ChessBoard::index(to));
      if (piece(to).toLower().unicode() == PAWN) {
        if (player() == WHITE and to.y() == 7) {
          board()->setCell(ChessBoard::index(QPoint(to.x(), 7)), QUEEN);
        } else if (player() == BLACK and to.y() == 0) {
          board()->setCell(ChessBoard::index(QPoint(to.x(), 0)), QChar(QUEEN).toUpper());
        }
      }
    }
  } else {
    return false;
  }

  if (not cellAttackers(not this->player(), this->king(not this->player())).isEmpty()) { // шах
    sach = true;
    std::cout << "ШАХ" << std::endl;
    if (isMat(not this->player())) {
      std::cout << "MAT" << std::endl;
    } else {
      std::cout << "НЕ МAT" << std::endl;
    }
  }

  //this->registerMove(was_on_from, was_on_to, sach);
  this->changePlayer();

  return true;
}

bool ChessLogic::isMat(bool color) {
  for (QPoint coordinate: getKingCells(king(color))) {
    if (this->checkFinalCell(king(color), coordinate, color)) {
      if (this->tryMove(king(color), coordinate, color)) {
        return false;
      }
    }
  }
  std::cout << "King can not move" << std::endl;

  QVector <QPoint> attackers = cellAttackers(color, king(color));

  for (auto x: attackers) {
    std::cout << "attacker X: " <<  x.x() << ", Y: " << x.y() << std::endl;
    std::cout << attackers.count() << std::endl;
  }

  if (attackers.count() > 1) { return true; } // если король не может ходить и обидчиков 2 и более

  if (piece(attackers.last()).toLower().unicode() == KNIGHT) {
    for (QPoint piece_coord : board()->getActualPieces(color)) { // кто то может уюить коня
        if (tryMove(piece_coord, attackers.last(), color)) { return false; }
    }
    return true;
  }

  for (QPoint cell : getCellsToCoordinate(king(color), attackers.last())) {
    std::cout << "============================" << std::endl;
    std::cout << "Checking POINT X: " <<  cell.x() << ", Y: " << cell.y() << std::endl;
    for (QPoint piece_coord : board()->getActualPieces(color)) { // кто то может заслонить собой
      if (canMove(piece_coord, cell)) {
        if (tryMove(piece_coord, cell, color)) { return false; }
      }
      std::cout << "Figure X: " << piece_coord.x() << ", Y: " << piece_coord.y() << " -- cannot" << std::endl;
    }
    std::cout << "============================" << std::endl;
  }
  return true;
}

QVector <QPoint> ChessLogic::getCellsToCoordinate(QPoint cell, QPoint attacker) {
  QVector <QPoint> cells = QVector <QPoint> ();
  int offset_x = attacker.x() - cell.x();
  int offset_y = attacker.y() - cell.y();
  if (abs(offset_x) == abs(offset_y)) { // DIAGONAL
    if (offset_x > 0 and offset_y > 0) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x() + i, cell.y() + i));
        }
    } else if (offset_x > 0 and offset_y < 0) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x() + i, cell.y() - i));
        }
    } else if (offset_x < 0 and offset_y > 0) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x() - i, cell.y() + i));
        }
    } else if (offset_x < 0 and offset_y < 0) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x() - i, cell.y() - i));
        }
    }
  } else {
    if (offset_x == 0) {
      if (offset_y > 0) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x(), cell.y() + i));
        }
      } else if (offset_y < 0) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x(), cell.y() - i));
        }
      }
    } else if (offset_y == 0) {
      if (offset_x > 0 ) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x() + i, cell.y()));
        }
      } else if (offset_x < 0) {
        for (int i = 1; i < abs(offset_y); i++) {
          cells.append(QPoint(cell.x() - i, cell.y()));
        }
      }
    }
  }
  cells.append(attacker);
  return cells;
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

QVector <QPoint>  ChessLogic::getKingCells(QPoint coordinate) {
  QVector <QPoint>  temp = QVector <QPoint> ();
  QVector <QPoint>  result = QVector <QPoint> ();
  temp.append(QPoint(coordinate.x()+1,coordinate.y()));
  temp.append(QPoint(coordinate.x(),coordinate.y()+1));
  temp.append(QPoint(coordinate.x()+1,coordinate.y()+1));

  temp.append(QPoint(coordinate.x()-1,coordinate.y()));
  temp.append(QPoint(coordinate.x(),coordinate.y()-1));
  temp.append(QPoint(coordinate.x()-1,coordinate.y()-1));

  temp.append(QPoint(coordinate.x()+1,coordinate.y()-1));
  temp.append(QPoint(coordinate.x()-1,coordinate.y()+1));

  for (auto x: temp) {
    if (x.x() >= 0 and x.x() <=7 and x.y() >=0 and x.y() <=7) {
      result.append(x);
    }
  }
  return result;
}

QVector <QPoint> ChessLogic::cellAttackers(bool color, QPoint cell) {
  QVector <QPoint> attackers = QVector <QPoint>();
  QChar piece;

  for (QPoint coordinate : getStraightCells(cell)) {
    piece = this->piece(coordinate);
    if (color == WHITE) {
      if (piece.isUpper()) { // черная фигура
        if (this->canMove(coordinate, cell)) { attackers.append(coordinate); break;}
      }
    } else if (color == BLACK) {
      if (piece.isLower()) {
        if (this->canMove(coordinate, cell)) { attackers.append(coordinate); break;}
      }
    }
  }
  for (QPoint coordinate : getDiagonalCells(cell)) {
    piece = this->piece(coordinate);
    if (color == WHITE) {
      if (piece.isUpper()) { // черная фигура
        if (this->canMove(coordinate, cell)) { attackers.append(coordinate); break;}
      }
    } else if (color == BLACK) {
      if (piece.isLower()) {
        if (this->canMove(coordinate, cell)) { attackers.append(coordinate); break;}
      }
    }
  }
  for (QPoint coordinate : getKnightCells(cell)) {
    piece = this->piece(coordinate);
    if (color == WHITE) {
      if (piece.isUpper()) { // черная фигура
        if (this->canMove(coordinate, cell)) { attackers.append(coordinate); }
      }
    } else if (color == BLACK) {
      if (piece.isLower()) {
        if (this->canMove(coordinate, cell)) { attackers.append(coordinate); }
      }
    }
  }

  return attackers;
}

bool ChessLogic::checkFinalCell (QPoint from, QPoint to, bool color) {
  if (color == WHITE and
      (this->piece(to).isNull() or this->piece(to).isUpper())) { }
  else if (color == BLACK and
      (this->piece(to).isNull() or this->piece(to).isLower())) { }
  else if (this->piece(from).toLower().unicode() == KING and
           this->piece(to).toLower().unicode() == ROOK)
  {
    if (this->kingWasMoved(color)) { return false; }
  }
  else  { return false; }
  return true;
}
