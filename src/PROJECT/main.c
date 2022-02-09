#include "target_interface.h"
// #include "lv_examples.h"

int main(void)
{
  target_interface__init();

  // lv_ex_get_started_2();

  while (!target_interface__get_quit_event())
  {
    target_interface__lv_task_handler();
  }

  target_interface__deinit();
  return 0;
}
