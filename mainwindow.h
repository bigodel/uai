#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define N_TRAINS 3

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
  void update_speed_train0(int);
  void update_speed_train1(int);
  void update_speed_train2(int);
  void update_speed_train3(int);
  void update_speed_train4(int);

private slots:
  void on_button_start_clicked();

  void on_button_stop_clicked();

  void on_button_reset_clicked();

private:
  Ui::MainWindow *ui;

  Train *train0;
  Train *train1;
  Train *train2;
  Train *train3;
  Train *train4;

  // Array para armazenar os trains para executarmos ações em todos num loop
  Train *trains[N_TRAINS];
};

#endif // MAINWINDOW_H
