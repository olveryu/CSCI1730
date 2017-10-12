#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstring>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <array>
#include <pwd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



class Shell {

  int exitStatus;
  int inBackup;
  int outBackup;
  int errBackup;
  int debug;
  vector<pid_t> child;
  vector<string> childName;
  vector<pid_t> stopList;

public:

  Shell();
  
  void exitOpt(string str);
  void exportFunction(string str);
  void fg(string str);
  void bg(string str);
  string autoComplete();
  void userInput();
  void jobs(bool periodicallyCheck);
  void help();
  void bashName();
  void doubleQuote(unsigned int processCounter, vector<string> * process);
  void cdCommand(vector <string> split);
  void printDebug(unsigned int processCounter, unsigned int pipeCounter, vector<string> * process, vector <string> split);
  void repl(string str);
  void close_pipe(int pipefd [2]);
  vector<char *> mk_cstrvec(vector<string> & strvec);
  void dl_cstrvec(vector<char *> & cstrvec);
  void nice_exec(vector<string> args, int inFd, int outFd, int errFd);
  void run(unsigned int processCounter, vector<string> * process, int inFd, int outFd, int errFd, int ampersand);
  
}; //Shell

#endif
