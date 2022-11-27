#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "train.h"
#include <QLabel>
#include <QMainWindow>
#include <QSlider>

#define N_TRAINS 5

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

private:
  Ui::MainWindow *ui;

  QLabel *labels[N_TRAINS];
  QSlider *sliders[N_TRAINS];
  Train *trains[N_TRAINS];

  Train *train0;
  Train *train1;
  Train *train2;
  Train *train3;
  Train *train4;
};

#endif // MAINWINDOW_H
