#include <stdio.h>
#include <stdlib.h>

int a() { printf("a\n"); }
int b() { printf("b\n"); }
int c() { printf("c\n"); }

int main() {
  a();
  b();
  c();
  exit(0);
}
