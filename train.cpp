#include "train.h"
#include <QtCore>

Train::Train(int id, int x, int y) {
  this->id = id;
  this->x = x;
  this->y = y;
  speed = 100;
}

void move_train(int id, int x_offset, int y_offset) {

}

void Train::run() {
  while (true) {
    switch (id) {
    case 1: // Trem 1
      if (y == 20 && x < 140)   // right
        x += 10;
      else if (x == 140 && y < 120) // down
        y += 10;
      else if (x > 20 && y == 120) // left
        x -= 10;
      else                      // up
        y -= 10;
      emit update_GUI(id, x, y); // Emite um sinal
      break;
    case 2: // Trem 2
      if (y == 20 && x < 260)   // right
        x += 10;
      else if (x == 260 && y < 120) // down
        y += 10;
      else if (x > 140 && y == 120) // left
        x -= 10;
      else                      // up
        y -= 10;
      emit update_GUI(id, x, y); // Emite um sinal
      break;
    case 3: // Trem 3
      if (y == 20 && x < 380)   // right
        x += 10;
      else if (x == 380 && y < 120) // down
        y += 10;
      else if (x > 260 && y == 120) // left
        x -= 10;
      else                      // up
        y -= 10;
      emit update_GUI(id, x, y); // Emite um sinal
      break;
    case 4: // Trem 4
      if (y == 120 && x < 200)   // right
        x += 10;
      else if (x == 200 && y < 220) // down
        y += 10;
      else if (x > 80 && y == 220) // left
        x -= 10;
      else                      // up
        y -= 10;
      emit update_GUI(id, x, y); // Emite um sinal
      break;
    case 5: // Trem 5
      if (y == 120 && x < 320)   // right
        x += 10;
      else if (x == 320 && y < 220) // down
        y += 10;
      else if (x > 200 && y == 220) // left
        x -= 10;
      else                      // up
        y -= 10;
      emit update_GUI(id, x, y); // Emite um sinal
      break;
    default:
      break;
    }
    msleep(speed);
  }
}
