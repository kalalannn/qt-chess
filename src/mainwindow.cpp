#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

ChessApp::ChessApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->maxIndex = 0;
  ui->setupUi(this);
}

ChessApp::~ChessApp() {
  delete ui;
}

void ChessApp::viewClicked(const QPoint &field) {
  int index = ui->tabWidget->currentIndex();
  if (v_logic[index]->hand() == QPoint(-1,-1)) {
    if (v_logic[index]->getPiece(field)) {
      m_selectedField = new ChessView::FieldHighlight(
                  field.x(), field.y(), QColor(0, 30, 255, 50));
      v_view[index]->addHighlight(m_selectedField);
    }
  } else {
    v_logic[index]->putPiece(field);
    v_view[index]->removeHighlight(m_selectedField);
    delete m_selectedField;
    m_selectedField = nullptr;
    v_logic[index]->setHand(QPoint(-1,-1));
  }
}

void ChessApp::on_actionNew_Game_triggered() {
  v_board.append(new ChessBoard(this));
  v_logic.append(new ChessLogic(this, v_board.last()));
  v_view.append(new ChessView(this, v_board.last()));

  connect(v_view.last(), &ChessView::clicked,
          this, &ChessApp::viewClicked);



  maxIndex = 1 + ui->tabWidget->addTab(v_view.last(),QString("Game " + QString::number(maxIndex)));
  //view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  //layout()->setSizeConstraint(QLayout::SetFixedSize);

}
