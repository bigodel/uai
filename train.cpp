#include "train.h"
#include <QtCore>

Train::Train(int id, position pos) {
  this->id = id;
  this->x = pos.x;
  this->y = pos.y;
  this->start_pos = pos;
  this->speed = 1;
}

Train::Train(int id, position pos, int speed) {
  this->id = id;
  this->x = pos.x;
  this->y = pos.y;
  this->start_pos = pos;
  this->speed = speed;
}

void Train::run() {
  while (true) {
    if (speed > 0) {
      int x_final = start_pos.x + TRAIL_SIZE;
      int y_final = start_pos.y + TRAIL_SIZE;

      if (x < x_final && y == start_pos.y) // right
        x += 10;
      else if (x == x_final && y < y_final) { // down
        y += 10;
      } else if (x > start_pos.x && y == y_final) { // left
        x -= 10;
      } else if (x == start_pos.x && y > start_pos.y) { // up
        y -= 10;
      }

      emit update_position(id, x, y); // Emite um sinal
      msleep(101 - speed);
    }
  }
}

void Train::reset() {
  this->x = start_pos.x;
  this->y = start_pos.y;
  emit update_position(id, start_pos.x, start_pos.y);
}

void Train::set_speed(int speed) { this->speed = speed; }
