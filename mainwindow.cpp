#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  train0 = new Train(0, {50, 20});
  train1 = new Train(1, {150, 20});
  train2 = new Train(2, {250, 20});
  train3 = new Train(3, {100, 120});
  train4 = new Train(4, {200, 120});

  connect(train0, SIGNAL(update_position(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train1, SIGNAL(update_position(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train2, SIGNAL(update_position(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train3, SIGNAL(update_position(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train4, SIGNAL(update_position(int, int, int)),
          SLOT(update_interface(int, int, int)));

  connect(ui->slider_train0, SIGNAL(valueChanged(int)),
          SLOT(update_speed_train0(int)));
  connect(ui->slider_train1, SIGNAL(valueChanged(int)),
          SLOT(update_speed_train1(int)));
  connect(ui->slider_train2, SIGNAL(valueChanged(int)),
          SLOT(update_speed_train2(int)));
  connect(ui->slider_train3, SIGNAL(valueChanged(int)),
          SLOT(update_speed_train3(int)));
  connect(ui->slider_train4, SIGNAL(valueChanged(int)),
          SLOT(update_speed_train4(int)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update_interface(int id, int x, int y) {
  switch (id) {
  case 0:
    ui->label_train0->setGeometry(x, y, 20, 20);
    break;
  case 1:
    ui->label_train1->setGeometry(x, y, 20, 20);
    break;
  case 2:
    ui->label_train2->setGeometry(x, y, 20, 20);
    break;
  case 3:
    ui->label_train3->setGeometry(x, y, 20, 20);
    break;
  case 4:
    ui->label_train4->setGeometry(x, y, 20, 20);
    break;
  default:
    break;
  }
}

void MainWindow::update_speed_train0(int speed) {
  train0->set_speed(speed);
  ui->label_speed0->setText(QString("%1").arg(speed));
}

void MainWindow::update_speed_train1(int speed) {
  train1->set_speed(speed);
  ui->label_speed1->setText(QString("%1").arg(speed));
}

void MainWindow::update_speed_train2(int speed) {
  train2->set_speed(speed);
  ui->label_speed2->setText(QString("%1").arg(speed));
}

void MainWindow::update_speed_train3(int speed) {
  train3->set_speed(speed);
  ui->label_speed3->setText(QString("%1").arg(speed));
}

void MainWindow::update_speed_train4(int speed) {
  train4->set_speed(speed);
  ui->label_speed4->setText(QString("%1").arg(speed));
}

void MainWindow::on_button_start_clicked() {
  train0->start();
  train1->start();
  train2->start();
  train3->start();
  train4->start();
}

void MainWindow::on_button_stop_clicked() {
  train0->terminate();
  train1->terminate();
  train2->terminate();
  train3->terminate();
  train4->terminate();
}

void MainWindow::on_button_reset_clicked() {
  train0->reset();
  train0->terminate();

  train1->reset();
  train1->terminate();

  train2->reset();
  train2->terminate();

  train3->reset();
  train3->terminate();

  train4->reset();
  train4->terminate();

  ui->slider_train0->setValue(1);
  ui->slider_train1->setValue(1);
  ui->slider_train2->setValue(1);
  ui->slider_train3->setValue(1);
  ui->slider_train4->setValue(1);
}
