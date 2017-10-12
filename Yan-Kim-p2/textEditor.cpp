
#include "textEditor.h"

using namespace::std;

    /******************************************
   Constructor - sets up default variables
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/

textEditor::textEditor(){
  height = LINES-5;
  width = COLS;
  starty = (LINES - height)/2;
  wholeString = "";
  editCheck = 0;
  opened = 0;
}


    /******************************************
   newPad method - creates a new pad for the editor
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/


void textEditor::newPad(){
  editorPad(starty,height,width);
}

    /******************************************
   fexists method - checks to see if the file exists
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/

bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}

    /******************************************
   getFileName method - returns the fileName
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/

string textEditor::getFileName(){
  char mesg[] = "Please enter the Filename to open. ";
  string fileName;
  curs_set(1);
  echo();
  attron(COLOR_PAIR(1));
  mvprintw(LINES-2,0,mesg);
  int ch = getch();
  
  while ( ch != '\n' )     //allows user to type in full file name
    {
      fileName.push_back( ch );
      ch = getch();
    }
  
  move(LINES-2,0);
  clrtoeol();
  attron(COLOR_PAIR(2));
  curs_set(0);
  this->fileName = fileName;   //sets fileName
  return fileName;
}

    /******************************************
    editorPad method - creates the pad used for editing text
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
    Params: starty = starting row position of window
            height = height of editing window
            width  = width of editing window
  *******************************************/

void textEditor::editorPad(int starty,int height, int width){
  x = 0;
  y = 0;
  int rows = 10000; 
  int start = 0;  
  int breakout = 0;
  width -= 2;

  // create the pad for scrolling
  WINDOW * win = newpad(rows,width);      //creates the editor pad
  refresh();
  scrollok(win,true);
  keypad(win, true);
  wmove(win,0,0);
  prefresh(win,start,0,starty+1,1,height,width);

  // key binding
  int KEY = wgetch(win);
  while(breakout==0){
    int length = (int)wholeString.length();    
    int checkLines = length/width;
    string temp = "";
    switch(KEY){
      
    case KEY_UP:  				          //key up
      if(y > 0){
	y--;
      }
      wmove(win,y,x);
      if(start >= 0 &&  y <=  height){
	start--;  
      }
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      break;
      
    case KEY_DOWN:        				  //key down
      if(y < checkLines){
	y++;
      }
      if(y*width+x > length){
	y = checkLines;
	x = length % width;
      }
      wmove(win,y,x);
      
      if(start < rows && y >= height-1){
	start++;
      }
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      break;
      
    case KEY_RIGHT:          				    //key right
      if(y >= checkLines){
	if(length > width){
	  length = length - (checkLines * width);
	}
      }
      if(x < length){
	x++;
      }
      if(x == width && y <checkLines){
	x = 0;
	y++;
      }
      wmove(win,y,x);
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      break;
      
    case KEY_LEFT:   				            //key left
      if(x > 0){
	x--;
      }else if(x == 0 && y != 0){
	x = width-1;
	y--;
      }
      wmove(win,y,x);
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      break;
      
    case KEY_BACKSPACE:		   		           //key backspace
      if(x > 0){
	x--;
      }else if(x == 0 && y != 0){
	x = width-1;
	y--;
      }
      wholeString.erase(y*width+x,1);
      wclear(win);
      wprintw(win,wholeString.c_str());
      wmove(win,y,x);
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      editCheck++;
      break;
      
    case 10:           					   //key enter
      for(int i = x; i < width; i++){
	temp += " ";
      }
      wholeString.insert(y*width+x,temp);
      x = 0;
      y++;
      wclear(win);
      wprintw(win,wholeString.c_str());
      wmove(win,y,x);
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      editCheck++;
      break;

    case 9:                                               //key tab
      wholeString.insert(y*width+x,"    ");
      if(x+4>=width){
        y++;
        x = x+4-width;
      }else{
        x += 4;
      }
      wclear(win);
      wprintw(win,wholeString.c_str());
      wmove(win,y,x);
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      editCheck++;
      break;
      
    case KEY_F(1):      			          //key f1 menu
      breakout = F1(win);
      prefresh(win,start,0,starty+1,1,height,width);
      if(breakout == 0)KEY = wgetch(win);
      break;
      
     default:         				          //key insert
       char c = (char)KEY;
       string temp(1,c);
      if(x == width && y <= rows){
	x = 0;
	y++;
      }      
      wholeString.insert(y*width+x,temp);
      wclear(win);
      wprintw(win,wholeString.c_str());
      x++;
      wmove(win,y,x);
      prefresh(win,start,0,starty+1,1,height,width);
      KEY = wgetch(win);
      editCheck++;
      break;
    }
  }
  refresh();
}

    /******************************************
    F1 method - When user selects a choice, perform it's corresponding action.
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
    Params: win = the current window
  *******************************************/

int textEditor::F1(WINDOW * win){
  int choice;
  string fileName;
  int breakout = 0;
  choice = menu();
  if(choice == 1){       //opens file
    if(editCheck != 0){
      saveChanges();
    }
    fileName = getFileName();
    const char * tempName = fileName.c_str();
    move(LINES-1,0);
    clrtoeol();
    attron(COLOR_PAIR(2));
    mvprintw(LINES-1,0,tempName);
    attron(COLOR_PAIR(1));
    refresh();
    if((openFile(win,fileName)== -1)){
      printError(tempName);
    }
  }
  if(choice == 2){                //saves the file
    if(opened == 1){
      save();
    }
    else
      {
    saveChanges();
  }
  }
    if(choice == 3){              //Save as
    saveAsWindow();
  }
  if(choice == 4){                //Quit
    if(editCheck != 0){
    saveChanges();
    }
    breakout = 1;
  }
  return breakout;
}

    /******************************************
    menu method - Lets user navigate through the f1 menu and select
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/

int textEditor::menu(){
  const char * choices[] = { 
    "open",
    "save",
    "save as",
    "Exit",
  };
  int n_choices = sizeof(choices) / sizeof(char *);
  WINDOW * menu_win;
  int highlight = 1;
  int choice = 0;
  int c;
  int starty = (LINES/2)-5;
  int startx = (COLS/2)-30;
  int breakout = 0;
  
  noecho();
  curs_set(0);
  menu_win = newwin(10, 35, starty, startx);
  wattron(menu_win,COLOR_PAIR(6));
  keypad(menu_win, TRUE);
  refresh();
  print_menu(menu_win, highlight);
  while(breakout == 0){
    c = wgetch(menu_win);
    switch(c){
    case KEY_UP:
      if(highlight == 1)
  highlight = n_choices;
      else
  --highlight;
      break;
    case KEY_DOWN:
      if(highlight == n_choices)
	highlight = 1;
      else 
  ++highlight;
      break;
    case 10:
      choice = highlight;
      breakout = 1;
      break;

    case KEY_F(1):
      breakout = 1;
      break;

    default:
      refresh();
      break;
    }
    print_menu(menu_win, highlight);
  }
  wclear(menu_win);
  wrefresh(menu_win);
  echo();
  curs_set(1);
  refresh();
  return choice;
}

    /******************************************
    print_menu method - shows the f1 menu
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
    Params: menu_win = the menu window
            highlight = returns the highlighted choice
  *******************************************/

void textEditor::print_menu(WINDOW * menu_win, int highlight){
  const char * choices[] = { 
    "open",
    "save",
    "save as",
    "Exit",
  };
  int n_choices = sizeof(choices) / sizeof(char *);
  int x, y;
  x = 2;
  y = 4;
  box(menu_win, 0, 0);
  mvwprintw(menu_win,1,13,"menu");
  mvwprintw(menu_win,2,1,"---------------------------------");
  for(int i = 0; i < n_choices; ++i){
    if(highlight == i + 1){
      wattron(menu_win, A_REVERSE); 
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    }
    else
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    ++y;
  }
  wrefresh(menu_win);
}

    /******************************************
    openFile method - opens a file
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
    Params: win = the current window
            fileName = current file
  *******************************************/

int textEditor::openFile(WINDOW * win, string fileName){
  ifstream r,r1;
  int fd = -1;
  width -= 2;
  r.open(fileName);
  r1.open(fileName);
  if(r.is_open()){
    wholeString = "";
    wclear(win);
    fd = 1;
    int numlines = 0; 
    string line = "";
    while( getline(r,line)){
      numlines++;
    }
    for(int j = 0; j < numlines; j++){
      getline(r1,line);
      wholeString += line;
    }
    mvwprintw(win,0,0,wholeString.c_str());
  }
  x = 0;
  y = 0;
  wmove(win,0,0);
  curs_set(1);
  r.close();
  r1.close();
  opened = 1;
  return fd;
}
    /******************************************
    printError method - Prints out an error if user tries to open a nonexisting file.
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
    Params: tempName = the file name
  *******************************************/

void textEditor::printError(const char * tempName){
  int starty = (LINES/2)-5;
  int startx = (COLS/2)-30;
  noecho();
  WINDOW * temp = newwin(10,35,starty,startx);
  wattron(temp,COLOR_PAIR(2));
  box(temp,0,0);
  wattron(temp,COLOR_PAIR(5));
  mvwprintw(temp,2,4,"File:");
  mvwprintw(temp,2,9,tempName);
  mvwprintw(temp,3,4,"fail to open because:");
  mvwprintw(temp,4,4,"(File did not exist.");
  mvwprintw(temp,5,4,"or permission denied.)");
  refresh();
  wrefresh(temp);
  getch();
  wclear(temp);
  wrefresh(temp);
  refresh();
  move(LINES-2,0);
  clrtoeol();
  move(LINES-1,0);
  clrtoeol();
  attron(COLOR_PAIR(1));
}

    /******************************************
    saveAsWindow method - Asks user if they want save and overwriting the existing file or not.
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/

void textEditor::saveAsWindow(){
  string fileName = "";
  int starty = (LINES/2)-5;
  int startx = (COLS/2)-30;
  noecho();
  WINDOW * temp = newwin(5,60,starty,startx);
  wattron(temp,COLOR_PAIR(2));
  box(temp,0,0);
  wattron(temp,COLOR_PAIR(5));
  mvwprintw(temp,2,4,"Save As: ");
  refresh();
  wrefresh(temp);
  echo();
  int ch = wgetch(temp);
  wmove(temp,starty,startx);
  wrefresh(temp);

  while ( ch != '\n' )
    {
      fileName.push_back( ch );
      ch = wgetch(temp);
      wmove(temp,starty,startx);
        wrefresh(temp);
    }
  
  if (fexists(fileName) == true){

  int starty = (LINES/2)-5;
  int startx = (COLS/2)-30;
  noecho();
  WINDOW * qtemp = newwin(5,60,starty,startx);
  wattron(qtemp,COLOR_PAIR(2));
  box(qtemp,0,0);
  wattron(qtemp,COLOR_PAIR(5));
  echo();
  mvwprintw(qtemp,2,4,"Overwrite existing file? (yes)/(no) ");
  refresh();
  wrefresh(qtemp);
  int ch = wgetch(qtemp);
  wmove(qtemp,starty,startx);
  wrefresh(qtemp);
  
  int check = 0;
while (check == 0){

  string question = "";

    while ( ch != '\n' )
    {
      question.push_back( ch );
      ch = wgetch(qtemp);
      wmove(qtemp,starty,startx);
        wrefresh(qtemp);
    }

    if (question == "yes"){
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    ofstream myfile;
    myfile.open (fileName);
    myfile << wholeString;
    myfile.close();
    wmove(qtemp, LINES-2,0);
    editCheck = 0;
    check++;
    }
    else if (question == "no"){
      endwin();
      check++;
    }
    else{
      werase(qtemp);
      wattron(qtemp,COLOR_PAIR(2));
      box(qtemp,0,0);
      wattron(qtemp,COLOR_PAIR(5));
      echo();
      mvwprintw(qtemp,2,4,"Please try again. Overwrite? (yes)/(no) ");
      ch = wgetch(qtemp);
      wmove(qtemp,starty,startx);
      wrefresh(qtemp);
    }
   }
 }
else{

  std::ofstream ofs;
  ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
 }
  ofstream myfile;
  myfile.open (fileName);
  myfile << wholeString;
  myfile.close();
  editCheck = 0;

  wmove(temp, LINES-2,0);
}

    /******************************************
    save method - Saves file
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/

void textEditor::save(){

std::ofstream ofs;
ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
ofs.close();

  ofstream myfile;
  myfile.open (fileName);
  myfile << wholeString;
  myfile.close();
  editCheck = 0;

}

    /******************************************
    saveChanges method - Checks to see if user has not saved edited text. Asks if they want to save or not.
    Author: Stephen Kim and Zhenyu Yan
    Date: 3/27/2017
  *******************************************/

void textEditor::saveChanges(){
int starty = (LINES/2)-5;
  int startx = (COLS/2)-30;
  noecho();
  WINDOW * qtemp = newwin(5,60,starty,startx);
  wattron(qtemp,COLOR_PAIR(2));
  box(qtemp,0,0);
  wattron(qtemp,COLOR_PAIR(5));
  echo();
  mvwprintw(qtemp,2,4,"Save unsaved file? (yes)/(no) ");
  refresh();
  wrefresh(qtemp);
  int ch = wgetch(qtemp);
  wmove(qtemp,starty,startx);
  wrefresh(qtemp);

      int check = 0;
while (check == 0){

  string question = "";

    while ( ch != '\n' )
    {
      question.push_back( ch );
      ch = wgetch(qtemp);
      wmove(qtemp,starty,startx);
        wrefresh(qtemp);
    }

    if (question == "yes"){
    saveAsWindow();
    wmove(qtemp, LINES-2,0);
    editCheck = 0;
    check++;
    }
    else if (question == "no"){
      endwin();
      check++;
    }
    else{
      werase(qtemp);
      wattron(qtemp,COLOR_PAIR(2));
      box(qtemp,0,0);
      wattron(qtemp,COLOR_PAIR(5));
      echo();
      mvwprintw(qtemp,2,4,"Please try again. Save? (yes)/(no) ");
      ch = wgetch(qtemp);
      wmove(qtemp,starty,startx);
      wrefresh(qtemp);
    }
   }
}

