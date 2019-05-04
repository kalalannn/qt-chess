#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

ChessApp::ChessApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  board = new ChessBoard(this);
  logic = new ChessLogic(this, board);
  view = new ChessView(this, board);

  connect(view, &ChessView::clicked,
          this, &ChessApp::viewClicked);

  view->setPiece('p', QIcon(":/pieces/Chess_plt45.svg")); // pawn
  view->setPiece('k', QIcon(":/pieces/Chess_klt45.svg")); // king
  view->setPiece('d', QIcon(":/pieces/Chess_qlt45.svg")); // queen
  view->setPiece('v', QIcon(":/pieces/Chess_rlt45.svg")); // rook
  view->setPiece('j', QIcon(":/pieces/Chess_nlt45.svg")); // knight
  view->setPiece('s', QIcon(":/pieces/Chess_blt45.svg")); // bishop

  view->setPiece('P', QIcon(":/pieces/Chess_pdt45.svg")); // pawn
  view->setPiece('K', QIcon(":/pieces/Chess_kdt45.svg")); // king
  view->setPiece('D', QIcon(":/pieces/Chess_qdt45.svg")); // queen
  view->setPiece('V', QIcon(":/pieces/Chess_rdt45.svg")); // rook
  view->setPiece('J', QIcon(":/pieces/Chess_ndt45.svg")); // knight
  view->setPiece('S', QIcon(":/pieces/Chess_bdt45.svg")); // bishop

  setCentralWidget(view);
  view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  view->setFieldSize(QSize(50,50));
  layout()->setSizeConstraint(QLayout::SetFixedSize);
}

ChessApp::~ChessApp()
{
  delete ui;
}

void ChessApp::viewClicked(const QPoint &field) {
  if (logic->hand() == QPoint(-1,-1)) {
    if (logic->getPiece(field)) {
      m_selectedField = new ChessView::FieldHighlight(
                  field.x(), field.y(), QColor(0, 30, 255, 50));
      view->addHighlight(m_selectedField);
    }
  } else {
    logic->putPiece(field);
    view->removeHighlight(m_selectedField);
    delete m_selectedField;
    m_selectedField = nullptr;
    logic->set_hand(QPoint(-1,-1));
  }
}
