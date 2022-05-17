#include <stdio.h>
#include "event.h"

int a() { printf("a\n"); }
int b() { printf("b\n"); }
int c() { printf("c\n"); }

int main() {
  init_event();
  while(1) {
    char ch = _getch();
    switch ( ch ) {
      case 'a': a(); break;
      case 'b': b(); break;
      case 'c': c(); break;
      case 'q': exit(0);
    }
  }
}
