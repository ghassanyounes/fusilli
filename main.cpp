#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

using std::cerr, std::cout, std::endl;

int main() try {
    // Init SDL
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("Fusilli", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load sprites image as a new texture
    SDL2pp::Texture sprites(renderer, "/M484SpaceSoldier.png");

    // Clear screen
    renderer.Clear();

    // Render our image, stretching it to the whole window
    renderer.Copy(sprites);

    // Show rendered frame
    renderer.Present();

    // 5 second delay
    SDL_Delay(5000);

    // All resources should be automatically released and the library should de-initialize.
    return 0;
} catch (std::exception &e) {
    // In the event of an error, print it and exit.
    cerr << e.what() << endl;
}
