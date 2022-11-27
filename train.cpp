#include "train.h"
#include <QtCore>
#include <map>
#include <vector>

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

// semaphore crossing(3);

std::map<int, std::vector<position>> critical_regions;

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

  if (id == 0) {
    critical_regions[0] = {{200, 20}, {200, 200}};
    critical_regions[1] = {{380, 20}, {380, 200}};
    critical_regions[2] = {{200, 200}, {110, 200}};
    critical_regions[3] = {{290, 200}, {200, 200}};
    critical_regions[4] = {{380, 200}, {290, 200}};
    critical_regions[5] = {{470, 200}, {380, 200}};
    critical_regions[6] = {{290, 200}, {290, 380}};
  }
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
          // entering left_intersection
          // printf("0 entering left_intersection\n");
          left_intersection.acquire();

          // entering region 0
          // printf("0 entering region0\n");
          region0.acquire();
        }

        // -> 2
        if (x == bottom_right.x && y == bottom_right.y - TRAIN_SIZE) {
          // entering region 2
          // printf("0 entering region2\n");
          region2.acquire();
        }

        // 0 ->
        if (x == bottom_right.x - TRAIN_SIZE && y == bottom_right.y) {
          // left left_intersection
          // printf("0 left left_intersection\n");
          left_intersection.release();

          // left region 0
          // printf("0 left region0\n");
          region0.release();
        }

        // 2 ->
        if (x == MID_LEFT && y == bottom_right.y) {
          // left region 2
          // printf("0 left region2\n");
          region2.release();
        }

        break;
      case 1:
        // -> 1
        if (x == bottom_right.x - TRAIN_SIZE && y == top_left.y) {
          // entering intersection 2
          // printf("1 entering right_intersection\n");
          right_intersection.acquire();

          // entering region 1
          // printf("1 entering region1\n");
          region1.acquire();
        }

        // -> 4
        if (x == bottom_right.x && y == bottom_right.y - TRAIN_SIZE) {
          // entering middle_intersection
          // printf("1 entering middle_intersection\n");
          middle_intersection.acquire();

          // entering region 4
          // printf("1 entering region4\n");
          region4.acquire();
        }

        // -> 1
        if (x == bottom_right.x - TRAIN_SIZE && y == bottom_right.y) {
          // left intersection 2
          // printf("1 left right_intersection\n");
          right_intersection.release();

          // left region 1
          // printf("1 left region1\n");
          region1.release();
        }

        // -> 3
        if (x == MID_RIGHT && y == bottom_right.y) {
          // entering left_intersection
          // printf("1 entering left_intersection\n");
          left_intersection.acquire();

          // entering region 3
          // printf("1 entering region3\n");
          region3.acquire();
        }

        // 4 ->
        if (x == MID_LEFT && y == bottom_right.y) {
          // left middle_intersection
          // printf("1 left middle_intersection\n");
          middle_intersection.release();

          // left region 4
          // printf("1 left region4\n");
          region4.release();
        }

        // -> 0
        if (x == top_left.x + TRAIN_SIZE && y == bottom_right.y) {
          // entering region 0
          // printf("1 entering region0\n");
          region0.acquire();
        }

        if (x == top_left.x && y == bottom_right.y - TRAIN_SIZE) {
          // left left_intersection
          // printf("1 left left_intersection\n");
          left_intersection.release();

          // left region 3
          // printf("1 left region3\n");
          region3.release();
        }

        // 0 ->
        if (x == top_left.x + TRAIN_SIZE && y == top_left.y) {
          // left region 0
          // printf("1 left region0\n");
          region0.release();
        }

        break;
      case 2:
      case 3:
        // -> 2
        if (x == top_left.x && y == top_left.y + TRAIN_SIZE) {
          // entering left_intersection
          // printf("3 entering left_intersection\n");
          left_intersection.acquire();

          // entering region 2
          // printf("3 entering region2\n");
          region2.acquire();
        }

        // -> 3
        if (x == MID_LEFT && y == top_left.y) {
          // entering middle_intersection
          // printf("3 entering middle_intersection\n");
          middle_intersection.acquire();

          // entering region 3
          // printf("3 entering region3\n");
          region3.acquire();
        }

        // 2 ->
        if (x == MID_RIGHT && y == top_left.y) {
          // left left_intersection
          // printf("3 left left_intersection\n");
          left_intersection.release();

          // left region 2
          // printf("3 left region2\n");
          region2.release();
        }

        // -> 6
        if (x == top_left.x - TRAIN_SIZE && y == top_left.y) {
          // entering region 6
          // printf("3 entering region6\n");
          region6.acquire();
        }

        // 3 ->
        if (x == bottom_right.x && y == top_left.y + TRAIN_SIZE) {
          // left left_intersection
          // printf("3 left left_intersection\n");
          middle_intersection.release();

          // left region 3
          // printf("3 left region3\n");
          region3.release();
        }

        // 6 ->
        if (x == bottom_right.x - TRAIN_SIZE && y == bottom_right.y) {
          // left region 6
          // printf("3 left region6\n");
          region6.release();
        }

        break;
      case 4:
        break;
      }

      move_train();
      emit update_position(id, x, y);
    }

    msleep(101 - speed);
  }
}

void Train::set_speed(int speed) { this->speed = speed; }
