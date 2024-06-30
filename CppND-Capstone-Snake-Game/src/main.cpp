#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  SDLContext ctx(kScreenWidth, kScreenHeight,
                 kGridWidth, kGridHeight);
  Renderer renderer(&ctx);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}