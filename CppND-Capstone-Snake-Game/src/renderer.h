#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>

#include "SDL.h"

#include "snake.h"
#include "food.h"

class SDLContext {
  public:
    SDLContext(const std::size_t screen_width, const std::size_t screen_height,
               const std::size_t grid_width, const std::size_t grid_height);
    ~SDLContext();

    // // copy 
    // SDLContext(const SDLContext& source);
    // SDLContext &operator=(const SDLContext& source);

    // // move
    // SDLContext(SDLContext &&other);
    // SDLContext &operator=(SDLContext &&other);

    SDL_Window* window;
    SDL_Renderer* renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

class Renderer {
 public:
  Renderer(SDLContext* ctx);
  ~Renderer();

  void Render(Snake const& snake);
  void Render(Food const& food);
  void Render(std::vector<Point> points);
  void ClearBoard();
  void UpdateBoard();

  void UpdateWindowTitle(int score, int fps);

 private:
  // std::unique_ptr<SDLContext> _sdlContext;
  SDLContext* _sdlContext;
};

#endif