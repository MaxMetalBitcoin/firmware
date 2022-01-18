#include "init_target.h"
#include "init_sdl.h"
#include "stdio.h"
#include "time.h"
// #include "lvgl.h"
#include <SDL.h>

#include "mbtc_connector.h"

// static monitor my_monitor;

int init_target(void)
{

  printf("hello\n");
  printf("%s", mbtc_get_key());
  printf("\n");

  char quit = 0;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);

  uint32_t pixels[640 * 480];
  memset(pixels, 255, 640 * 480 * sizeof(uint32_t));
  char leftMouseButtonDown = 0;

  SDL_Window *window = SDL_CreateWindow("SDL2 Pixel Drawing",
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Texture *texture = SDL_CreateTexture(renderer,
                                           SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);

  while (!quit)
  {

    SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(uint32_t));
    SDL_WaitEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
      quit = 1;
      break;
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT)
        leftMouseButtonDown = 0;
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT)
        leftMouseButtonDown = 1;
    case SDL_MOUSEMOTION:
      if (leftMouseButtonDown)
      {
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;
        pixels[mouseY * 640 + mouseX] = 0;
      }
      break;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  // sdl_init();

  return 0;
}

// void delay(int milli_seconds)
// {
//   // Storing start time
//   clock_t start_time = clock();

//   // looping till required time is not achieved
//   while (clock() < start_time + milli_seconds)
//     ;
// }

// int target_lvgl_loop(void)
// {
//   delay(5);
//   lv_task_handler();
// }
