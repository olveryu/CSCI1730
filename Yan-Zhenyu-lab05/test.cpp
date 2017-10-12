#include <string.h>
#include <ncurses.h>
#include <unistd.h>

int main(){
  initscr();
  start_color();
  WINDOW* win = newwin(100,100,100,100);
  wrefresh(win);
  init_pair(1,COLOR_GREEN,COLOR_BLACK);
  init_pair(2,COLOR_YELLOW,COLOR_BLACK);
  do{
    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
	attron(COLOR_PAIR(1));
	mvprintw(i,j,"Hello");
	refresh();
	attron(COLOR_PAIR(2));
	mvprintw(10-i,10-j,"World");
	refresh();
	usleep(100000);
	clear();
      }
    }
  }while(true);
  endwin();
  return 0;
}
