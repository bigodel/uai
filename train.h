#ifndef TRAIN_H
#define TRAIN_H

#include <QThread>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar
 * a função RUN. Para parar a execução da função RUN da thread, basta executar a
 * função TERMINATE.
 *
 */
class Train : public QThread {
  Q_OBJECT
public:
  Train(int, int, int); // construtor
  void run();           // função a ser executada pela thread
  void move_train(int, int, int);

  // Cria um sinal
signals:
  void update_GUI(int, int, int);

private:
  int x;     // posição X do trem na tela
  int y;     // posição Y do trem na tela
  int id;    // ID do trem
  int speed; // Velocidade. É o tempo de dormir em milisegundos entre a mudança
             // de posição do trem
};

#endif // TRAIN_H
