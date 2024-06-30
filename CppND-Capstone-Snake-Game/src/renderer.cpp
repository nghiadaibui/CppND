#include "renderer.h"
#include <iostream>
#include <string>

/* Implementation of class SDLContext */
SDLContext::SDLContext(const std::size_t screen_width, const std::size_t screen_height,
                       const std::size_t grid_width, const std::size_t grid_height)
           : screen_width(screen_width), screen_height(screen_height),
             grid_width(grid_width), grid_height(grid_height)  {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen_width,
                            screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

SDLContext::~SDLContext() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

// SDLContext(const SDLContext& source) {}
// SDLContext &operator=(const SDLContext& source) {}

// SDLContext(SDLContext &&other) {}
// SDLContext &operator=(SDLContext &&other) {}

/* Implementation of class Renderer */
Renderer::Renderer(SDLContext* ctx) {
  // _sdlContext = std::make_unique<SDLContext>(kScreenWidth, kScreenHeight,
  //                                            kGridWidth, kGridHeight);
  _sdlContext = ctx;
}

Renderer::~Renderer() {}

void Renderer::Render(Snake const& snake) {
  SDL_Rect block;
  block.w = _sdlContext->screen_width / _sdlContext->grid_width;
  block.h = _sdlContext->screen_height / _sdlContext->grid_height;

  // Render snake's body
  SDL_SetRenderDrawColor(_sdlContext->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_sdlContext->renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(_sdlContext->renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(_sdlContext->renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(_sdlContext->renderer, &block);
}

void Renderer::Render(Food const& food) {
  SDL_Rect block;
  block.w = _sdlContext->screen_width / _sdlContext->grid_width;
  block.h = _sdlContext->screen_height / _sdlContext->grid_height;

  // Render food
  if (food.GetType() == FoodType::normal) {
    SDL_SetRenderDrawColor(_sdlContext->renderer, 0xFF, 0xCC, 0x00, 0xFF);
  } else if (food.GetType() == FoodType::special) {
    SDL_SetRenderDrawColor(_sdlContext->renderer, 0xDD, 0x70, 0x90, 0xFF);
  } else if (food.GetType() == FoodType::poison) {
    SDL_SetRenderDrawColor(_sdlContext->renderer, 0x00, 0xFF, 0x00, 0xFF);
  }
  
  block.x = food.pos.x * block.w;
  block.y = food.pos.y * block.h;
  SDL_RenderFillRect(_sdlContext->renderer, &block);
}

void Renderer::Render(std::vector<Point> points) {
  SDL_Rect block;
  block.w = _sdlContext->screen_width / _sdlContext->grid_width;
  block.h = _sdlContext->screen_height / _sdlContext->grid_height;

  // Render points
  SDL_SetRenderDrawColor(_sdlContext->renderer, 0x00, 0xFF, 0x00, 0xFF);
  for (Point const& point : points) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_sdlContext->renderer, &block);
  }
}

void Renderer::ClearBoard() {
  // Clear screen
  SDL_SetRenderDrawColor(_sdlContext->renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdlContext->renderer);
}

void Renderer::UpdateBoard() {
  // Update Screen
  SDL_RenderPresent(_sdlContext->renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_sdlContext->window, title.c_str());
}
