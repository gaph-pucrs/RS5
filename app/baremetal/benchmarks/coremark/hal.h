#ifndef _HAL_H
#define _HAL_H

#include "prototypes.h"

#define TIMER_REG (*(volatile uint32_t*)0x20000000)
#define UART_REG (*(volatile char*)0x80004000)

// Stubs, need real implementation
static inline int enter_critical() { return 0; }
static inline void leave_critical(int i) {}
void halt() __attribute__ ((noreturn));

#endif
