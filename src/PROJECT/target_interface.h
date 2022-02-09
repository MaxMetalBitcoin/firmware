#ifndef TARGET_INTERFACE_H
#define TARGET_INTERFACE_H

#include <stdint.h>

void target_interface__init(void);
uint8_t target_interface__get_quit_event(void);
void target_interface__lv_task_handler(void);
void target_interface__deinit(void);

#endif
