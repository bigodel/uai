#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Cria o trem com seu (ID, posição X, posição Y)
  train1 = new Train(1, 20, 20);
  train2 = new Train(2, 140, 20);
  train3 = new Train(3, 260, 20);
  train4 = new Train(4, 80, 120);
  train5 = new Train(5, 200, 120);

  /*
   * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
   * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função
   * UPDATEINTERFACE. Os 3 parâmetros INT do sinal serão utilizados na função.
   * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto
   * chamar o sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
   */
  connect(train1, SIGNAL(update_GUI(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train2, SIGNAL(update_GUI(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train3, SIGNAL(update_GUI(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train4, SIGNAL(update_GUI(int, int, int)),
          SLOT(update_interface(int, int, int)));
  connect(train5, SIGNAL(update_GUI(int, int, int)),
          SLOT(update_interface(int, int, int)));
}

// Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::update_interface(int id, int x, int y) {
  switch (id) {
  case 1: // Atualiza a posição do trem1
    ui->label_train1->setGeometry(x, y, 20, 20);
    break;
  case 2: // Atualiza a posição do train2
    ui->label_train2->setGeometry(x, y, 20, 20);
    break;
  case 3: // Atualiza a posição do train3
    ui->label_train3->setGeometry(x, y, 20, 20);
    break;
  case 4: // Atualiza a posição do train4
    ui->label_train4->setGeometry(x, y, 20, 20);
    break;
  case 5: // Atualiza a posição do train5
    ui->label_train5->setGeometry(x, y, 20, 20);
    break;
  default:
    break;
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_start_clicked() {
  train1->start();
  train2->start();
  train3->start();
  train4->start();
  train5->start();
}

void MainWindow::on_button_stop_clicked() {
  train1->terminate();
  train2->terminate();
  train3->terminate();
  train4->terminate();
  train5->terminate();
}
