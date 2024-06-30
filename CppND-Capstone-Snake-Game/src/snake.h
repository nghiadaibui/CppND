#ifndef SNAKE_H
#define SNAKE_H

#include "game_config.h"
#include <vector>

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<Point> body;

 private:
  void UpdateHead();
  void UpdateBody(Point &current_cell, Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif