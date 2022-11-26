#include "mainwindow.h"
#include "train.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  labels[0] = ui->label_train0;
  labels[1] = ui->label_train1;
  labels[2] = ui->label_train2;
  labels[3] = ui->label_train3;
  labels[4] = ui->label_train4;

  sliders[0] = ui->slider_train0;
  sliders[1] = ui->slider_train1;
  sliders[2] = ui->slider_train2;
  sliders[3] = ui->slider_train3;
  sliders[4] = ui->slider_train4;

  for (int i = 0; i < N_TRAINS; i++) {
    position pos = {labels[i]->geometry().x(), labels[i]->geometry().y()};
    trains[i] = new Train(i, pos);
    connect(trains[i], SIGNAL(update_position(int, int, int)),
            SLOT(update_interface(int, int, int)));
  }

  connect(sliders[0], SIGNAL(valueChanged(int)),
          SLOT(update_speed_train0(int)));
  connect(sliders[1], SIGNAL(valueChanged(int)),
          SLOT(update_speed_train1(int)));
  connect(sliders[2], SIGNAL(valueChanged(int)),
          SLOT(update_speed_train2(int)));
  connect(sliders[3], SIGNAL(valueChanged(int)),
          SLOT(update_speed_train3(int)));
  connect(sliders[4], SIGNAL(valueChanged(int)),
          SLOT(update_speed_train4(int)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update_interface(int id, int x, int y) {
  labels[id]->setGeometry(x, y, 20, 20);
}

void MainWindow::update_speed_train0(int speed) {
  trains[0]->set_speed(speed);
  ui->label_speed0->setText(QString::number(speed));
}

void MainWindow::update_speed_train1(int speed) {
  trains[1]->set_speed(speed);
  ui->label_speed1->setText(QString::number(speed));
}

void MainWindow::update_speed_train2(int speed) {
  trains[2]->set_speed(speed);
  ui->label_speed2->setText(QString::number(speed));
}

void MainWindow::update_speed_train3(int speed) {
  trains[3]->set_speed(speed);
  ui->label_speed3->setText(QString::number(speed));
}

void MainWindow::update_speed_train4(int speed) {
  trains[4]->set_speed(speed);
  ui->label_speed4->setText(QString::number(speed));
}

void MainWindow::on_button_start_clicked() {
  for (int i = 0; i < N_TRAINS; i++)
    trains[i]->start();
}

void MainWindow::on_button_stop_clicked() {
  for (int i = 0; i < N_TRAINS; i++)
    trains[i]->terminate();
}

void MainWindow::on_button_reset_clicked() {
  for (int i = 0; i < N_TRAINS; i++) {
    trains[i]->reset();
    trains[i]->terminate();
    // sliders[i]->setValue(sliders[i]->minimum());
  }
}
