#include "target_interface.h"

#include "lv_conf.h"
#include "lvgl.h"
#include "lv_examples.h"
#include "lv_sdl_drv_display.h"
#include "lv_sdl_drv_input.h"
// #include "lv_if_drv_filesystem.h"
#include "input_test.h"
#include <stdio.h>

void target_interface__init(void)
{
  lv_init();

  lv_sdl_init_display("Hola", 640, 480);
  lv_sdl_init_input();
}

uint8_t target_interface__get_quit_event(void)
{
  return (uint8_t)get_quit_event();
}

void target_interface__lv_task_handler(void)
{
  lv_task_handler();
}

void target_interface__deinit(void)
{
  printf("Freeing resources and quitting\n");
  lv_sdl_deinit_input();
  lv_sdl_deinit_display();
  lv_deinit();
}