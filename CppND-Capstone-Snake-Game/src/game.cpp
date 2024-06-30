#include <iostream>
#include <chrono>
#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : _snake(grid_width, grid_height) ,
      _food(grid_width, grid_height, FoodType::normal),
      _toxic(grid_width, grid_height, FoodType::poison) {
  // _gen_toxic = std::thread(&Food::placefor, &_toxic, _snake, _total_toxic);
  _future = std::async(&Food::placefor, &_toxic, _snake, _total_toxic);
  _food.placefor(_snake, _total_toxic);
}

// Game::~Game() {
//   _gen_toxic.join();
// }

void Game::Run(Controller const &controller,
               Renderer &renderer,
               std::size_t target_frame_duration) {
  auto title_timestamp = std::chrono::system_clock::now();
  std::chrono::system_clock::time_point frame_start;
  std::chrono::system_clock::time_point frame_end;
  std::chrono::milliseconds frame_duration, frame_offset;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = std::chrono::system_clock::now();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _snake);
    Update();

    renderer.ClearBoard();
    renderer.Render(_snake);
    renderer.Render(_food);
    _mutex.lock();
    renderer.Render(_total_toxic);
    _mutex.unlock();
    renderer.UpdateBoard();

    frame_end = std::chrono::system_clock::now();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start);
    frame_offset = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - title_timestamp);

    // After every second, update the window title.
    if (frame_offset.count() >= 1000) {
      renderer.UpdateWindowTitle(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration.count() < target_frame_duration) {
      std::this_thread::sleep_for(std::chrono::milliseconds(target_frame_duration - frame_duration.count()));
    }
  }
}

void Game::Update() {
  if (!_snake.alive) return;
  _snake.Update();

  int new_x = static_cast<int>(_snake.head_x);
  int new_y = static_cast<int>(_snake.head_y);

  // Check if there's food over here
  if (_food.pos.x == new_x && _food.pos.y == new_y) {
    // Grow snake and increase speed.
    if (_food.GetType() == FoodType::normal) {
      _snake.GrowBody();
      _score++;
      _snake.speed += 0.01;
    } else if (_food.GetType() == FoodType::special) {
      _future = std::async(&Food::placefor, &_toxic, _snake, _total_toxic);
      _food.SetType(FoodType::normal);
      _score += 5;
      _snake.speed += 0.05;
    }
    // Generate new food
    if (_snake.size % 5 == 1 && _snake.size > 5) {
      _food.SetType(FoodType::special);
    }
    _food.placefor(_snake, _total_toxic);
  }

  // Check if there's toxic over here
  for (Point const& point : _total_toxic) {
    if (point.x == new_x && point.y == new_y) {
      _snake.alive = false;
      return;
    }
  }

  // Update new toxic
  if (_snake.size % 7 == 1) {
    _future.wait();
    _mutex.lock();
    Point new_toxic {
      .x = _toxic.pos.x,
      .y = _toxic.pos.y
    };
    _total_toxic.emplace_back(new_toxic);
    _mutex.unlock();
  } 
}

int Game::GetScore() const { return _score; }
int Game::GetSize() const { return _snake.size; }