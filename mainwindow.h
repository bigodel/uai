#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trem.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void updateInterface(int, int, int);

private slots:
  void on_button_ligar_clicked();

  void on_button_parar_clicked();

private:
  Ui::MainWindow *ui;

  // Cria os objetos TREM's
  Trem *trem1;
  Trem *trem2;
  Trem *trem3;
  Trem *trem4;
  Trem *trem5;
};

#endif // MAINWINDOW_H
