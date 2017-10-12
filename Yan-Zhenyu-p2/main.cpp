
#include "textEditor.h"
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>

using std::string;

int main(){

  WINDOW * win;
  int startx, starty, width, height;
  string fileName;

  // init the program
  initscr();
  clear();
  cbreak();
  start_color();

  // set up the color
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  init_pair(2,COLOR_YELLOW,COLOR_BLUE);
  init_pair(3,COLOR_GREEN,COLOR_BLACK);
  init_pair(4,COLOR_YELLOW,COLOR_RED);
  init_pair(5,COLOR_RED,COLOR_BLACK);
  init_pair(6,COLOR_YELLOW,COLOR_BLACK);

  // set up the elements
  height = LINES-5;
  width = COLS;
  starty = (LINES - height)/2;
  startx = (COLS - width)/2;
    
  
  // print out the title
  mvprintw(1,(width/2)-6,"TEXT EDITOR");
  attron(COLOR_PAIR(4));
  mvprintw(0,10,"(Make by zhenyu Yan and stephen kim)");
  attron(COLOR_PAIR(2));
  mvprintw(0,0,"F1:MENU");
  mvprintw(LINES-1,0,"(No file open.)");

  // create the window for text editor
  win = newwin(height, width, starty, startx);
  keypad(win, TRUE);
  wattron(win,COLOR_PAIR(3));
  box(win,0,0);
  refresh();
  wrefresh(win);
  
 
  textEditor editor;
  editor.newPad();
  refresh();
  wrefresh(win);
  endwin();
  return EXIT_SUCCESS;
}
