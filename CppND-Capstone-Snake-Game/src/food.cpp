#include "food.h"

// void Food::placefor(Snake snake) {
//   unsigned int x = random_w(engine);
//   unsigned int y = random_h(engine);

//   while (snake.SnakeCell(x, y)) {
//     x = random_w(engine);
//     y = random_h(engine);
//   }
  
//   pos.x = x;
//   pos.y = y;
// }

void Food::placefor(Snake snake, std::vector<Point> points) {
  unsigned int x, y;
  bool exist = true;

  while (exist) {
    exist = false;
    x = random_w(engine);
    y = random_h(engine);

    if (snake.SnakeCell(x, y)) {
      exist = true;
    }

    for (Point const& point : points) {
      if (point.x == x && point.y == y) {
        exist = true;
      }
    } 
  }
  
  pos.x = x;
  pos.y = y;
}