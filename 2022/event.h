#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios orig_termios;

void _reset_terminal_mode()
{
  tcsetattr(0, TCSANOW, &orig_termios);
}

void _set_conio_terminal_mode()
{
  struct termios new_termios;

  /* take two copies - one for now, one for later */
  tcgetattr(0, &orig_termios);
  memcpy(&new_termios, &orig_termios, sizeof(new_termios));

  /* register cleanup handler, and set the new terminal mode */
  atexit(_reset_terminal_mode);
  cfmakeraw(&new_termios);
  tcsetattr(0, TCSANOW, &new_termios);
}

int _kbhit()
{
  struct timeval tv = { 0L, 0L };
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &tv);
}

int _getch()
{
  if ( _kbhit() ) {
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
      return r;
    } else {
      return c;
    }
  }
  return 0;
}

int init_event() {
  _set_conio_terminal_mode();
}

struct callback_func_cell
{
  char key;
  int (*func)(void);
  struct callback_func_cell *next;
};
struct callback_func_cell *callback_func_head = NULL;

int set_callback_func(char key, int (*func)(void)) {
  struct callback_func_cell *cell = (struct callback_func_cell *)malloc(sizeof(struct callback_func_cell));

  cell->key = key;
  cell->func = func;
  cell->next = callback_func_head;
  callback_func_head = cell;
}

int main_event_loop() {

  char ch = _getch();

  struct callback_func_cell *cell;

  for (cell = callback_func_head; cell != NULL; cell = cell->next){
    if ( cell->key == ch ) {
      cell->func();
    }
  }
}

int main_event() {
  while (1) {
    main_event_loop();
  }
}
