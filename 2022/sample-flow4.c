#include <stdio.h>
#include "event.h"

char current_char = '_';
int global_state = 0;
int a() { printf("a\n"); current_char = 'a'; global_state++; }
int b() { printf("b\n"); current_char = 'b'; global_state++; }
int c() { printf("c\n"); current_char = 'c'; global_state++; }

int main() {
  init_event();

  set_callback_func('a', a);
  set_callback_func('b', b);
  set_callback_func('c', c);
  
  while ( 1 ) {
    if ( global_state >= 3 ) {
      break;
    }
    main_event_loop();
    printf("%c ", current_char);
  }
  exit(0);
}
