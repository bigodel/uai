#include "train.h"
#include <QtCore>

Train::Train(int id, int x, int y) {
  this->id = id;
  this->x = x;
  this->y = y;
  speed = 100;
}

void Train::move_train(int id, int x_initial, int y_initial) {
  int x_final = x_initial + 100;
  int y_final = y_initial + 100;

  if (x < x_final && y == y_initial) // right
    x += 10;
  else if (x == x_final && y < y_final) { // down
    y += 10;
  } else if (x > x_initial && y == y_final) { // left
    x -= 10;
  } else if (x == x_initial && y > y_initial) { // up
    y -= 10;
  }

  emit update_GUI(id, x, y); // Emite um sinal
}

void Train::run() {
  while (true) {
    switch (id) {
    case 1: // Trem 1
      move_train(1, 50, 20);
      break;
    case 2:                   // Trem 2
      move_train(2, 150, 20);
      break;
    case 3:                   // Trem 3
      move_train(3, 250, 20);
      break;
    case 4:                    // Trem 4
      move_train(4, 100, 120);
      break;
    case 5:                    // Trem 5
      move_train(5, 200, 120);
      break;
    default:
      break;
    }
    msleep(speed);
  }
}
