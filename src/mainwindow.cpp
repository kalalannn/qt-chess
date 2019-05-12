#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

ChessApp::ChessApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->maxIndex = 0;
  ui->setupUi(this);
  on_actionNew_Game_triggered();
}

ChessApp::~ChessApp() {
  delete ui;
}

void ChessApp::on_actionNew_Game_triggered() {
  v_board.append(new ChessBoard(this));
  v_logic.append(new ChessLogic(this, v_board.last()));
  v_view.append(new ChessView(this, v_board.last(), v_logic.last()));

  maxIndex = 1 + ui->tabWidget->addTab(v_view.last(),QString("Game " + QString::number(maxIndex)));
  ui->tabWidget->setCurrentIndex(maxIndex-1);
  connect(v_logic.last(), &ChessLogic::onMat,
          this, &ChessApp::on_actionMat);
}

void ChessApp::on_tabWidget_tabCloseRequested(int index) {
  if (not v_logic[index]->output().isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("Do you want to save the Game " + QString::number(index) + "?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
        ui->tabWidget->setCurrentIndex(index);
        on_actionSave_Game_triggered();
        break;
      case QMessageBox::Cancel:
        return;
      case QMessageBox::Discard:
        break;
    }
  }
  ui->tabWidget->removeTab(index);
  if (ui->tabWidget->currentIndex() == -1) {
    on_actionNew_Game_triggered();
  }
}



void ChessApp::on_actionSave_Game_triggered() {
  QString fileName = QFileDialog::getSaveFileName(this,
          tr("Save Game"), "",
          tr("Chess Game (*.chs);;All Files (*)"));
  if (fileName.isEmpty()) { }
  else {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::information(this, tr("Unable to open file"),
                              file.errorString());
      return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << v_logic[ui->tabWidget->currentIndex()]->output().toLatin1().constData();
  }
}

void ChessApp::on_actionMat(bool player) {
  QString winner = "";
  if (player == WHITE) {
    winner += "White player";
  } else {
    winner += "Black player";
  }
    QMessageBox msgBox;
    msgBox.setText("Game over\nWinner: " + winner);
    msgBox.exec();
}

void ChessApp::on_actionLoad_Game_triggered() {
    QMessageBox msgBox;
    msgBox.setText("Sorry, this feature is not currently implemented");
    msgBox.setDetailedText("This feature will be implemented later");
    msgBox.exec();
}

void ChessApp::on_actionAbout_triggered() {
    QMessageBox msgBox;
    msgBox.setText("Author: Nikolaj Vorobiev\nVersion: 1.0");
    msgBox.exec();

}
