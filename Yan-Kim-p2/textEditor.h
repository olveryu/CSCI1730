
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <ncurses.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>

using std::string;

class textEditor{

  int starty;               //starting row position
  int width;                //width of the window
  int height;               //height of the window
  string wholeString;       //saves text on screen to a string
  string fileName;          //fileName
  int editCheck;            //checks to see if user has edited the text
  int x;                    //column position
  int y;                    //row position
  int opened;               //checks to see if a file has been opened

 public:
  textEditor();
  void newPad();
  string getFileName();
  void editorPad(int starty,int height,int width);
  
  int F1(WINDOW * win);
  int menu();
  void print_menu(WINDOW * menu_win, int highlight);
  int openFile(WINDOW * win, string fileName);
  void printError(const char * tempName);
  void save();
  void saveAsWindow();
  void saveChanges();
  
};
#endif
