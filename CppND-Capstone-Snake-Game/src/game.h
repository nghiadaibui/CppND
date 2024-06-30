#ifndef GAME_H
#define GAME_H

#include <thread>
#include <future>
#include <mutex>
#include "controller.h"
#include "renderer.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  // ~Game();
  void Run(Controller const &controller,
           Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake _snake;
  Food _food;
  // add some toxic food to the game
  Food _toxic;
  std::vector<Point> _total_toxic;
  std::future<void> _future;
  // std::thread _gen_toxic;
  std::mutex _mutex;

  int _score{0};

  void Update();
};

#endif