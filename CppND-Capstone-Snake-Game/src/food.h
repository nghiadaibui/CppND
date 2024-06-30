#ifndef FOOD_H
#define FOOD_H

#include "game_config.h"
#include <random>
#include "snake.h"

typedef enum {
  normal,
  special,
  poison
} FoodType;

class Food {
  public:
    // getter/setter
    FoodType GetType() const { return _type; }
    void SetType(FoodType type) { _type = type; }
    // constructor//destructor
    Food(std::size_t grid_width, std::size_t grid_height, FoodType type)
      : engine(dev()),
        random_w(0, static_cast<int>(grid_width - 1)),
        random_h(0, static_cast<int>(grid_height - 1)),
        _type(type) {}
    ~Food() {}

    Point pos;

    // void placefor(Snake snake);
    void placefor(Snake snake, std::vector<Point> points);

  private:
    FoodType _type;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
};

#endif