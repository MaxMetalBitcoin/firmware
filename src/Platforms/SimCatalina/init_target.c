#include "init_target.h"
#include "stdio.h"
#include <SDL.h>

#include "mbtc_connector.h"

int init_target(void)
{

  printf("hello");
  printf(mbtc_get_key());

  char quit = 0;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("SDL2 Pixel Drawing",
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

  while (!quit)
  {
    SDL_WaitEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
      quit = 1;
      break;
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
