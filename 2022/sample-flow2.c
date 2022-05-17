#include <stdio.h>
#include "event.h"

int a() { printf("a\n"); }
int b() { printf("b\n"); }
int c() { printf("c\n"); }

int main() {
  init_event();
  set_callback_func('a', a);
  set_callback_func('b', b);
  set_callback_func('c', c);
  set_callback_func('q', (int (*)(void))exit);

  while (1) { // or use main_event();
    main_event_loop();
  }
}
