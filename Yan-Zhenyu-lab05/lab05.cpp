#include <curses.h>
#include <panel.h>


int main() {
  initscr();
  cbreak();
  curs_set(0);
  refresh();
  /* Creating windows */
  WINDOW *topwin = newwin(10, 10, 10, 10);
  WINDOW *bottompad = newpad(20, 20);
  /* Creating panels */
  PANEL *winp = new_panel(topwin);
  PANEL *padp = new_panel(bottompad);
  /* Putting borders around, so we can actually see something */
  box(topwin, 0, 0);
  box(bottompad, 0, 0);
  /* Updating (unnecessary if pads were working properly) */
  update_panels();
  pnoutrefresh(bottompad, 0, 0, 15, 15, 35, 35);
  /* Putting window on top of pad */
  top_panel(winp);
  /* Updating panels */
  update_panels();
  doupdate();
  getch();
  del_panel(padp);
  del_panel(winp);
  delwin(bottompad);
  delwin(topwin);
  endwin();
  return 0;
}
