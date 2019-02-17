#include <keyboard.h>

#include "keymap.h"
#include <virtualterminal.h>

void keyboard_handler(signed char keycode)
{
  /* highest bit set == key released */
  if(keycode & 0x80) {
    virtualterminal_writestring(2, key_fr[keycode & 0x7F]);
    virtualterminal_writestring(2, "key_released");
  } else {
    virtualterminal_writestring(2, key_fr[keycode]);
    virtualterminal_writestring(2, "key_pressed");
  }
}
