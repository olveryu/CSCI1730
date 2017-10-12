#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace::std;

int main(const int argc, const char * argv[]){

  initscr();
  ifstream r, r1;
  ofstream outFile;

  r.open(argv[1]);
  r1.open(argv[1]);
  int numlines = 0; 


  int height, width;
  getmaxyx(stdscr, height, width); 

  string line;
  while( getline(r,line)){
    numlines++;
  } 
  string * storage = nullptr; 
  storage = new string[numlines];


  for(int j = 0; j < numlines; j++){
    getline(r1,line);
    storage[j] = line;
  } 



  WINDOW * win = newpad(numlines,width);
  refresh();
  for(int i = 0; i < numlines; i++){
    wprintw(win, storage[i].c_str());
  }
  
 
  

  chtype c;
  c = mvwinch(win,0,0);
  char cc = (char)c;
  string s(1,cc);
  
  outFile.open("test1.txt");
  outFile << s;
  outFile.close();

  int start = 0;
  prefresh(win,start,0,0,0,height-1,width);

  keypad(win, true);
  int KEY = wgetch(win);
  int breakout=0;
  while(breakout==0){
    switch(KEY){
    case KEY_UP: 
      if(start >= 0)
	{
	  start--;
	}
      prefresh(win,start,0,0,0,height-1,width);
      KEY = wgetch(win);
      break;

    case KEY_DOWN:
      if(start < numlines-height)
	{
	  start++;
	}
      prefresh(win,start,0,0,0,height-1,width);






      KEY = wgetch(win);
      break;

    default:

      breakout=1;
      break;
    }
  }




  refresh();
  delete [] storage;

  endwin();
  return 0;
}
