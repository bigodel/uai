#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "train.h"
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
  void update_interface(int, int, int);

private slots:
  void on_button_start_clicked();

  void on_button_stop_clicked();

private:
  Ui::MainWindow *ui;

  // Cria os objetos TREM's
  Train *train1;
  Train *train2;
  Train *train3;
  Train *train4;
  Train *train5;
};

#endif // MAINWINDOW_H
