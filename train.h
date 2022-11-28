#ifndef TRAIN_H
#define TRAIN_H

#include <QSemaphore>
#include <QThread>

#define TRAIN_SIZE 20
#define TRAIL_SIZE 180
#define MID_OFFSET top_left.x + (TRAIL_SIZE / 2)
#define MID_LEFT MID_OFFSET - TRAIN_SIZE
#define MID_RIGHT MID_OFFSET + TRAIN_SIZE

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
  Train(int, position, position);
  Train(int, position, position, int);
  void move_train();
  void run();
  void set_speed(int);

signals:
  void update_position(int, int, int);

private:
  int id;
  int x;
  int y;
  position top_left;
  position bottom_right;
  int speed;
};

#endif // TRAIN_H
