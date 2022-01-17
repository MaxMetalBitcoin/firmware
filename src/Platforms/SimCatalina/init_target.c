#include "init_target.h"
// #include "init_sdl.h"
#include "stdio.h"
#include "time.h"
// #include "lvgl.h"
#include <SDL.h>

#include "mbtc_connector.h"

int init_target(void)
{

  printf("hello\n");
  printf("%s", mbtc_get_key());
  printf("\n");

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
