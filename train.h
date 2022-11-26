#ifndef TRAIN_H
#define TRAIN_H

#define TRAIL_SIZE 100

#include <QThread>

typedef struct position_s {
  int x;
  int y;
} position;

/*
 * Classe Train herda QThread
 * Classe Train passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar
 * a função RUN. Para parar a execução da função RUN da thread, basta executar a
 * função TERMINATE.
 *
 */
class Train : public QThread {
  Q_OBJECT
public:
  Train(int, position);
  Train(int, position, int);
  void run();
  void reset();
  // void move_train(int, int);
  void set_speed(int);

signals:
  void update_position(int, int, int);

private:
  int id;
  int x;
  int y;
  position start_pos;
  int speed;
};

#endif // TRAIN_H
