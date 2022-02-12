#include "target_interface.h"
#include "main_menu.h"

int main(void)
{
  target_interface__init();

  mmbtc_main_menu_render();

  while (!target_interface__get_quit_event())
  {
    target_interface__lv_task_handler();
  }

  target_interface__deinit();
  return 0;
}
