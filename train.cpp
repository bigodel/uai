#include "train.h"
#include <QtCore>

using mutex = std::mutex;
using semaphore = QSemaphore;

semaphore region0(1);
semaphore region1(1);
semaphore region2(1);
semaphore region3(1);
semaphore region4(1);
semaphore region5(1);
semaphore region6(1);
semaphore region7(1);

semaphore left_intersection(2);
semaphore middle_intersection(2);
semaphore right_intersection(2);

semaphore crossing(3);

Train::Train(int id, position start_pos, position top_left)
    : Train(id, start_pos, top_left, 1){};

Train::Train(int id, position start_pos, position top_left, int speed) {
  this->id = id;
  this->x = start_pos.x;
  this->y = start_pos.y;
  this->top_left = top_left;
  this->bottom_right.x = top_left.x + TRAIL_SIZE;
  this->bottom_right.y = top_left.y + TRAIL_SIZE;
  this->speed = speed;
}

void Train::move_train() {
  if (x < bottom_right.x && y == top_left.y) { // right
    x += 10;
  } else if (x == bottom_right.x && y < bottom_right.y) { // down
    y += 10;
  } else if (x > top_left.x && y == bottom_right.y) { // left
    x -= 10;
  } else if (x == top_left.x && y > top_left.y) { // up
    y -= 10;
  }
}

void Train::run() {
  while (true) {
    if (speed > 0) {
      switch (id) {
      case 0:
        // -> 0
        if (x == bottom_right.x - TRAIN_SIZE && y == top_left.y) {
          crossing.acquire();
          left_intersection.acquire();
          region0.acquire();
        }

        // -> 2
        if (x == bottom_right.x && y == bottom_right.y - TRAIN_SIZE) {
          region2.acquire();
        }

        // 0 ->
        if (x == bottom_right.x - TRAIN_SIZE && y == bottom_right.y) {
          left_intersection.release();
          region0.release();
        }

        // 2 ->
        if (x == MID_LEFT && y == bottom_right.y) {
          crossing.release();
          region2.release();
        }

        break;
      case 1:
        // -> 1
        if (x == bottom_right.x - TRAIN_SIZE && y == top_left.y) {
          crossing.acquire();
          right_intersection.acquire();
          region1.acquire();
        }

        // -> 4
        if (x == bottom_right.x && y == bottom_right.y - TRAIN_SIZE) {
          middle_intersection.acquire();
          region4.acquire();
        }

        // 1 ->
        if (x == bottom_right.x - TRAIN_SIZE && y == bottom_right.y) {
          right_intersection.release();
          region1.release();
        }

        // -> 3
        if (x == MID_RIGHT && y == bottom_right.y) {
          left_intersection.acquire();
          region3.acquire();
        }

        // 4 ->
        if (x == MID_LEFT && y == bottom_right.y) {
          middle_intersection.release();
          region4.release();
        }

        // -> 0
        if (x == top_left.x + TRAIN_SIZE && y == bottom_right.y) {
          region0.acquire();
        }

        // 3 ->
        if (x == top_left.x && y == bottom_right.y - TRAIN_SIZE) {
          crossing.release();
          left_intersection.release();
          region3.release();
        }

        // 0 ->
        if (x == top_left.x + TRAIN_SIZE && y == top_left.y) {
          region0.release();
        }

        break;
      case 2:
        // -> 5
        if (x == MID_RIGHT && y == bottom_right.y) {
          crossing.acquire();
          right_intersection.acquire();
          region5.acquire();
        }

        // -> 1
        if (x == top_left.x + TRAIN_SIZE && y == bottom_right.y) {
          region1.acquire();
        }

        // 5 ->
        if (x == top_left.x && y == bottom_right.y) {
          crossing.release();
          right_intersection.release();
          region5.release();
        }

        // 1 ->
        if (x == top_left.x + TRAIN_SIZE && y == top_left.y) {
          region1.release();
        }

        break;
      case 3:
        // -> 2
        if (x == top_left.x && y == top_left.y + TRAIN_SIZE) {
          crossing.acquire();
          left_intersection.acquire();
          region2.acquire();
        }

        // -> 3
        if (x == MID_LEFT && y == top_left.y) {
          middle_intersection.acquire();
          region3.acquire();
        }

        // 2 ->
        if (x == MID_RIGHT && y == top_left.y) {
          left_intersection.release();
          region2.release();
        }

        // -> 6
        if (x == bottom_right.x - TRAIN_SIZE && y == top_left.y) {
          region6.acquire();
        }

        // 3 ->
        if (x == bottom_right.x && y == top_left.y + TRAIN_SIZE) {
          crossing.release();
          middle_intersection.release();
          region3.release();
        }

        // 6 ->
        if (x == bottom_right.x - TRAIN_SIZE && y == bottom_right.y) {
          region6.release();
        }

        break;
      case 4:
        // -> 6
        if (x == top_left.x + TRAIN_SIZE && y == bottom_right.y) {
          crossing.acquire();
          middle_intersection.acquire();
          region6.acquire();
        }

        // -> 4
        if (x == top_left.x && y == top_left.y + TRAIN_SIZE) {
          right_intersection.acquire();
          region4.acquire();
        }

        // 6 ->
        if (x == top_left.x + TRAIN_SIZE && y == top_left.y) {
          middle_intersection.release();
          region6.release();
        }

        // -> 5
        if (x == MID_LEFT && y == top_left.y) {
          region5.acquire();
        }

        // 4 ->
        if (x == MID_RIGHT && y == top_left.y) {
          right_intersection.release();
          region4.release();
        }

        // -> 5
        if (x == bottom_right.x && y == top_left.y + TRAIN_SIZE) {
          crossing.release();
          region5.release();
        }

        break;
      }

      move_train();
      emit update_position(id, x, y);
    }

    msleep(101 - speed);
  }
}

void Train::set_speed(int speed) { this->speed = speed; }
