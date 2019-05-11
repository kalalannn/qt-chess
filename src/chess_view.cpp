#include "chess_view.h"

#include <QPainter>

ChessView::ChessView(QWidget *parent,
                     ChessBoard *board,
                     ChessLogic *logic) : QWidget (parent) {
  this->setBoard(board);
  this->setLogic(logic);
  this->setPiece('p', QIcon(":/pieces/Chess_plt45.svg")); // pawn
  this->setPiece('k', QIcon(":/pieces/Chess_klt45.svg")); // king
  this->setPiece('d', QIcon(":/pieces/Chess_qlt45.svg")); // queen
  this->setPiece('v', QIcon(":/pieces/Chess_rlt45.svg")); // rook
  this->setPiece('j', QIcon(":/pieces/Chess_nlt45.svg")); // knight
  this->setPiece('s', QIcon(":/pieces/Chess_blt45.svg")); // bishop

  this->setPiece('P', QIcon(":/pieces/Chess_pdt45.svg")); // pawn
  this->setPiece('K', QIcon(":/pieces/Chess_kdt45.svg")); // king
  this->setPiece('D', QIcon(":/pieces/Chess_qdt45.svg")); // queen
  this->setPiece('V', QIcon(":/pieces/Chess_rdt45.svg")); // rook
  this->setPiece('J', QIcon(":/pieces/Chess_ndt45.svg")); // knight
  this->setPiece('S', QIcon(":/pieces/Chess_bdt45.svg")); // bishop
  this->setFieldSize(QSize(50,50));
  connect(this, &ChessView::clicked,
          this, &ChessView::viewClicked);
}

void ChessView::viewClicked(const QPoint &field) {
  if (logic()->hand() == QPoint(-1,-1)) {
    if (logic()->getPiece(field)) {
      m_selectedField = new FieldHighlight(
                  field.x(), field.y(), QColor(0, 30, 255, 50));
      this->addHighlight(m_selectedField);
    }
  } else {
    logic()->putPiece(field);
    this->removeHighlight(m_selectedField);
    delete m_selectedField;
    m_selectedField = nullptr;
    logic()->setHand(QPoint(-1,-1));
  }
}

QSize ChessView::sizeHint() const {
    QSize boardSize = QSize(fieldSize().width()  * SIZE +1,
                            fieldSize().height() * SIZE +1);
    int rankSize =   fontMetrics().width('M')+4;
    int columnSize = fontMetrics().height()+4;
    return boardSize + QSize(rankSize, columnSize);
}

QRect ChessView::fieldRect(int column, int rank) const {
    const QSize fs = fieldSize();
    QRect fRect = QRect(QPoint((column) * fs.width(),
                               (SIZE- rank - 1)*fs.height()), fs);
    // offset rect by rank symbols
    int offset = fontMetrics().width('M'); // 'M' is the widest letter
    return fRect.translated(offset, 0);
}

void ChessView::drawHighlights(QPainter *painter) {
  for(int idx=0; idx < highlightCount(); ++idx) {
    Highlight *hl = highlight(idx);
    if(hl->type() == FieldHighlight::Type) {
      FieldHighlight *fhl = static_cast<FieldHighlight*>(hl);
      QRect rect = fieldRect(fhl->column(), fhl->rank());
      painter->fillRect(rect, fhl->color());
    }
  }
}
void ChessView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    for(int r = SIZE -1 ; r >= 0; --r) {
        painter.save();
        drawRank(&painter, r);
        painter.restore();
    }
    for(int c = 0; c < SIZE ; ++c) {
        painter.save();
        drawColumn(&painter, c);
        painter.restore();
    }
    for(int r = 0; r < SIZE ; ++r) {
        for(int c = 0; c < SIZE ; ++c) {
            painter.save();
            drawField(&painter, c, r);
            painter.restore();
        }
    }
    drawHighlights(&painter);
    for(int r = SIZE - 1 ; r >= 0 ; --r) {
        for(int c = 0; c < SIZE ; ++c) {
            drawPiece(&painter, c, r);
        }
    }
    Q_UNUSED(event)
}

void ChessView::drawRank(QPainter *painter, int rank) {
    QRect r = fieldRect(0, rank);
    QRect rankRect = QRect(0, r.top(), r.left(), r.height()).adjusted(2, 0, -2, 0);
    QString rankText = QString::number(rank + 1);
    painter->drawText(rankRect, Qt::AlignVCenter|Qt::AlignRight, rankText);
}

void ChessView::drawColumn(QPainter *painter, int column) {
    QRect r = fieldRect(column, 0);
    QRect columnRect = QRect(r.left(), r.bottom(),
                             r.width(), this->height()-r.bottom()).adjusted(0, 2, 0, -2);
    painter->drawText(columnRect, Qt::AlignHCenter|Qt::AlignTop, QChar('a'+column));
}

void ChessView::drawField(QPainter *painter, int column, int rank) {
    QRect rect = fieldRect(column, rank);
    QColor fillColor = (column+rank) % 2 ? palette().color(QPalette::Light)
                                         : palette().color(QPalette::Mid);
    painter->setPen(palette().color(QPalette::Dark));
    painter->setBrush(fillColor);
    painter->drawRect(rect);
}

void ChessView::drawPiece(QPainter *painter, int column, int rank) {
    QRect rect = fieldRect(column, rank);
    QChar value = m_board->piece(ChessBoard::index(QPoint(column, rank)));
    if(value != QChar::Null) {
        QIcon icon = piece(value);
        if(!icon.isNull()) {
            icon.paint(painter, rect, Qt::AlignCenter);
        }
    }
}

QPoint ChessView::fieldAt(const QPoint &pt) const {
    if(!m_board) return QPoint();
    const QSize fs = fieldSize();
    int offset = fontMetrics().width('M'); // 'M' is the widest letter
    if(pt.x() < offset) return QPoint(-1,-1);
    int c = (pt.x()-offset) / fs.width();
    int r = pt.y()/fs.height();
    if(c < 0 || c >= SIZE || r < 0 || r >= SIZE)
        return QPoint(-1,-1);

    return QPoint(c, SIZE - r - 1); // max rank - r
}

void ChessView::mouseReleaseEvent(QMouseEvent *event) {
    QPoint pt = fieldAt(event->pos());
    if(pt == QPoint(-1,-1)) { return; }
    emit clicked(pt);
}
