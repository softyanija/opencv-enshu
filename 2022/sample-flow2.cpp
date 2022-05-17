#include <iostream>
#include "event.h"

int a() { std::cerr << "a" << std::endl; }
int b() { std::cerr << "b" << std::endl; }
int c() { std::cerr << "c" << std::endl; }

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
