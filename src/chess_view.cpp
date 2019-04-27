#include "chess_view.h"

#include <QPainter>

ChessView::ChessView(QWidget *parent,
                     QPointer <ChessBoard> board) : QWidget (parent) {
  this->setBoard(board);
}

QSize ChessView::sizeHint() const {
    QSize boardSize = QSize(fieldSize().width()  * SIZE +1,
                            fieldSize().height() * SIZE +1);
    int rankSize =   fontMetrics().width('M')+4;
    int columnSize = fontMetrics().height()+4;
    return boardSize + QSize(rankSize, columnSize) ;//+QSize(200, 50);
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
