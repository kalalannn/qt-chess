#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include <QObject>
#include <QPointer>
#include <QMap>
#include <QIcon>
#include <QMouseEvent>

#include "chess_board.h"

class ChessView : public QObject {
	// мы тут обрабатываем MouseEvent
	// походу должен наследоваться от QWidget..
  Q_OBJECT

public:
	explicit ChessView(QObject *parent = nullptr);
	QPointer<ChessBoard> board() { return m_board; }

	void setBoard(QPointer<ChessBoard> board) { m_board = board; }

	void mouseEvent(QMouseEvent *event);
	// If clicked on board returns field coords QPoint, otherwise null QPoint
	QPoint fieldAt(const QPoint &point);

	// тут ебанешь draw методы

private:
	QPointer<ChessBoard> m_board;
	QMap<char, QIcon> pieces;
};

#endif // CHESS_VIEW_H
