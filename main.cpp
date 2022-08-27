#include <iostream>
#include <exception>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "colors.h"

using std::cerr, std::cout, std::endl;
using std::vector;

static const int window_width = 1920; ///< the window's width
static const int window_height = 1020; ///< the window's height

enum DIR {
  left,
  right,
  up,
  down
};

int main() try {
  // Init SDL
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);
  SDL2pp::SDLTTF ttf;

  SDL2pp::Window window("Fusilli", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height,
                        SDL_WINDOW_RESIZABLE);

  SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL2pp::Font font("../assets/ComicPapyrus.ttf", 24);

  // Load sprite images a new textures
  SDL2pp::Texture spriteR(renderer, "../assets/yeehaw_sprite.png");
  SDL2pp::Texture spriteL(renderer, "../assets/yeehaw_sprite_left.png");
  SDL2pp::Texture spriteU(renderer, "../assets/yeehaw_sprite_up.png");
  SDL2pp::Texture spriteD(renderer, "../assets/yeehaw_sprite_down.png");
  // Load background
  SDL2pp::Texture background(renderer, "../assets/bg.bmp");
  SDL2pp::Texture text(renderer, font.RenderText_Solid("yeehaw!", Colors::bright_yellow));

  int x = 200;
  int y = 200;
  bool quit = false;
  SDL_Event event;

  unsigned int prevTicks = SDL_GetTicks();
  DIR dir = right;

  while ( !quit ) {
    // Main Loop

    // Handle events:
    // exit application when Q or ESC pressed or the window is closed.
    SDL_PollEvent(&event);
    if ( event.type == SDL_QUIT ) quit = true;
    else if ( event.type == SDL_KEYDOWN ) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE:
          quit = true;
          break;
        case SDLK_LEFT:
          x -= (x > 0) ? 5 : 0;
          dir = left;
          break;
        case SDLK_RIGHT:
          x += (x < window_width) ? 5 : 0;
          dir = right;
          break;
        case SDLK_UP:
          y -= (y > 0) ? 5 : 0;
          dir = up;
          break;
        case SDLK_DOWN:
          y += (y < window_height) ? 5 : 0;
          dir = down;
          break;
      }
    }

    // Timing: calculate difference between this and previous frame in milliseconds
    unsigned int frameTicks = SDL_GetTicks();
    unsigned int frameDelta = frameTicks - prevTicks;
    prevTicks = frameTicks;
    int spriteSpeed = (int) frameTicks / 200 % 2;
    SDL_Rect spriteBox   = {spriteSpeed * 500, 0, 500, 500};
    SDL_Rect headBox     = {x, y, 128, 128};


    renderer.Clear();
    renderer.Copy(background);
    SDL_Rect textLocation = {250, 75, text.GetWidth(), text.GetHeight()};
    renderer.Copy(text, SDL2pp::NullOpt, textLocation);
    switch(dir) {
      case right:
        renderer.Copy(spriteR, spriteBox, headBox);
        break;
      case left:
        renderer.Copy(spriteL, spriteBox, headBox);
        break;
      case up:
        renderer.Copy(spriteU, spriteBox, headBox);
        break;
      case down:
        renderer.Copy(spriteD, spriteBox, headBox);
        break;
    }

    // Show rendered frame
    renderer.Present();
  }


  // All resources should be automatically released and the library should de-initialize.
  return 0;
} catch ( std::exception &e ) {
  // In the event of an error, print it and exit.
  cerr << e.what() << endl;
}
