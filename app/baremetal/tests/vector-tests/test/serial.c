#include <stdint.h>

#ifdef SAIL

// Console of the Sail model's host-target interface: device 1, command 1
// prints the low byte. On RV32 the model acts on the write of the upper word.
extern volatile uint32_t tohost[2];

void _putchar(char character) {
  while (tohost[0] | tohost[1])
    ;
  tohost[0] = (uint8_t)character;
  tohost[1] = 0x01010000u;
}

#else

extern char fake_uart;

void _putchar(char character) {
  // send char to console
  fake_uart = character;
}

#endif
