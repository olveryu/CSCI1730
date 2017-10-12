
#include "Shell.h"

Shell::Shell(){

  inBackup = dup(STDIN_FILENO);
  outBackup = dup(STDOUT_FILENO);
  errBackup = dup(STDERR_FILENO);
  exitStatus = 0;
  debug = -1;
  signal(SIGINT, SIG_IGN); 
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
}

    /******************************************
   void userInput - Gets user input from CMD
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
  *******************************************/

void Shell::userInput(){

  string str;							// get user input
  str = autoComplete();
  if (cin.eof()==1) {						// disable ctrl-D
    cin.clear();
    cin.ignore();
  }
  jobs(true);	       						// check backgound process
  if (str == ""){
    jobs(true);	       						// check backgound process
  }else if(str == "exit"){
    exit(exitStatus);
  }else if(str.size() > 5 && str.find("exit ",0,5) !=  string::npos){
    exitOpt(str);
  }else if(str.size() > 7 && str.find("export ",0,6) != string::npos){
    exportFunction(str);
  }else if(str.size() > 3 && str.find("fg ",0,2) !=  string::npos){    
    fg(str);
  }else if(str.size() > 3 && str.find("bg ",0,2) !=  string::npos){    
    bg(str);
  }else if(str == "echo $?"){
    cout << exitStatus << endl;
  }else if(str == "help"){
    help();
  }else if(str == "debug on"){
    debug = 1;
  }
  else if(str == "debug off"){
    debug = -1;
  }
  else if(str == "jobs"){
    jobs(false);
  }else{
    childName.push_back(str);
    repl(str);						       	// read user input
    jobs(true);	       						// check backgound process
  }
}

    /******************************************
   void exitOpt - Gets and checks exit status
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: str - string to check
  *******************************************/

void Shell::exitOpt(string str){
  string temp = str.substr(5,str.size());
  if (isdigit(temp.c_str()[0])){
    exitStatus = atoi(temp.c_str());
    exit(exitStatus);
  }else{
    fprintf(stderr, "Invalid format.\n");
  }
}

    /******************************************
   void exportFunction - Code for the Export Function
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: str - string to check
  *******************************************/

void Shell::exportFunction(string str){
  string temp = str.substr(7,str.size());
  std::size_t found = temp.find("=");
  if(found + 1 < temp.size()){
    if (found!=std::string::npos){
      std::size_t pos = temp.find("=");
      std::string envname = temp.substr (0, pos);
      std::string enval = temp.substr (pos + 1);
      setenv(envname.c_str(),enval.c_str(),1);
    }
    else{
      fprintf(stderr, "\n");
    }
  }
}

    /******************************************
   void fg - Sets a process to the foreground
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: str - string to check
  *******************************************/

void Shell::fg(string str){
  string temp = str.substr(3,str.size());
  if (isdigit(temp.c_str()[0])){
    pid_t fg = atoi(temp.c_str());
    for(unsigned int i = 0; i < child.size(); i++){
      if(child[i] == fg){
	int tempStatus;
	pid_t terminal = getpid();

	if(kill(fg,SIGCONT) == -1){
	  perror("fg");
	}

	signal(SIGTTOU,SIG_IGN);
	if(tcsetpgrp(1,child[i]) == -1){
	  perror("tcsetpgrp");
	}
	signal(SIGTTOU,SIG_DFL);

	waitpid(child[i],&tempStatus, WUNTRACED | WCONTINUED);

	signal(SIGTTOU,SIG_IGN);
	if(tcsetpgrp(1,terminal) == -1){
	  perror("tcsetpgrp");
	}
	signal(SIGTTOU,SIG_DFL);

	exitStatus = WEXITSTATUS(tempStatus);
	jobs(false);
      }
    }
  }else{
    fprintf(stderr, "Invalid format.\n");
  }
}

    /******************************************
   void bg - Sets a process to the background
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: str - string to check
  *******************************************/

void Shell::bg(string str){
  string temp = str.substr(3,str.size());
  if (isdigit(temp.c_str()[0])){
    pid_t bg = atoi(temp.c_str());
    cout << bg << endl;
    if(kill(bg,SIGCONT) == -1){
      perror("bg");
    }
  }
}

    /******************************************
   void jobs - Prints out list of jobs
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: periodicallyCheck - boolean to clean out finished processes
  *******************************************/

void Shell::jobs(bool periodicallyCheck){
  for(unsigned int i = 0; i < child.size();i++){
    int tempStatus;
    if(waitpid(child[i],&tempStatus, WUNTRACED | WCONTINUED | WNOHANG)){
      if (WIFEXITED(tempStatus)) {
	printf("JID:%ld",(long)child[i]); 
	printf(" status: exited.(status = %d)   ", WEXITSTATUS(tempStatus));
	printf(" Command: %s\n",childName[i].c_str());
	child.erase (child.begin()+i);
	childName.erase (childName.begin()+i);
	for(unsigned int j = 0; j < stopList.size(); j++){
	  if(child[i] == stopList[j]){
	    stopList.erase (stopList.begin()+ j);
	  }
	}
	i--;
	exitStatus = WEXITSTATUS(tempStatus);
      } else if (WIFSIGNALED(tempStatus)) {
	printf("JID:%ld",(long)child[i]); 
	printf(" status: killed.(signal = %d)   ", WTERMSIG(tempStatus));
	printf(" Command: %5s\n",childName[i].c_str()); 
	child.erase (child.begin()+i);
	childName.erase (childName.begin()+i);
	for(unsigned int j = 0; j < stopList.size(); j++){
	  if(child[i] == stopList[j]){
	    stopList.erase (stopList.begin()+ j);
	  }
	}
	i--;
	exitStatus = WEXITSTATUS(tempStatus);
      } else if (WIFSTOPPED(tempStatus)) {
	printf("JID:%ld",(long)child[i]); 
	printf(" status: stopped.(signal = %d)  ", WSTOPSIG(tempStatus));
	printf(" Command: %s\n",childName[i].c_str());
	exitStatus = tempStatus;
	stopList.push_back(child[i]);
      } else if (WIFCONTINUED(tempStatus)) {
	printf("JID:%ld",(long)child[i]);
	printf(" status:continued.              ");
	printf(" Command: %s\n",childName[i].c_str()); 
	for(unsigned int j = 0; j < stopList.size(); j++){
	  if(child[i] == stopList[j]){
	    stopList.erase (stopList.begin()+ j);
	  }
	}
      }
    } else {
      bool stopCheck = false;
      if(!periodicallyCheck){
	for(unsigned int j = 0; j < stopList.size(); j++){
	  if(child[i] == stopList[j]){
	    printf("JID:%ld",(long)child[i]);
	    printf(" status:stopped                 ");
	    printf(" Command: %s\n",childName[i].c_str()); 
	    stopCheck = true;
	  }
	}
	if(!stopCheck){
	  printf("JID:%ld",(long)child[i]);
	  printf(" status:running                 ");
	  printf(" Command: %s\n",childName[i].c_str()); 
	}
      }
    } 
  }
}

    /******************************************
   void help - Prints out list possible commands
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
  *******************************************/

void Shell::help(){
  cout << "help    : Display helpful information about builtin commands." << endl;
  cout << "cd[path]: hange the current directory toPATH. The environmental variableHOMEis the defaultPATH." << endl;
  cout << "exit [N]: Cause the shell to exit with a status of N. If N is omitted, the exit status is that of the last job executed." << endl;
  cout << "export NAME[=WORD] - NAME is automatically included in the environment of subsequently executed jobs." << endl;
  cout << endl;
  cout << "extra function" << endl;
  cout << "echo &?      : display exit status" << endl;
  cout << "debug on/off : display jobs and process " << endl;
  cout << "KEY tab      : Auto-Completion for File Names" << endl;
  cout << "fg JID       : Resume job JID in the foreground, and make it the current job." << endl;
  cout << "bg JID       : Resume the stopped job JID in the background, as if it had been started with&." << endl;
}

    /******************************************
   void bashName - Prints out the bashName
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
  *******************************************/

void Shell::bashName(){
  char temp[1024];
  getcwd(temp,1024);
  string path(temp);
  struct passwd * pw = getpwuid(getuid());
  const char * homedir = pw->pw_dir;
  string home(homedir);
  int start_pos = path.find(homedir);
  if(start_pos != -1){
    path.replace(start_pos, home.length(),"1730sh:~");
  }else{
    path.insert(0,"1730sh:");
  }
  path += "$";
  string color ="\033[1;31m";
  color += path;
  color += "\033[0m";
  cout << color;
}

/*
 * this function is to print out the information of the user input
 *
 *@param: str which is the user input
 *
 */
void Shell::repl(string str){
  int pipeCounter = 0;						// count how many pipe
  int processCounter = 1;					// count how many process
  int redirectionPos = -1;					// check if there has any redirection
  int ampersand = -1;
  vector <string> split;					// vector to store all the element split by space
  string buf;							// buffer
  stringstream ss(str);						// stringstream to seperate the element
  while(ss >> buf) split.push_back(buf);			// store in the verctor split

  for(unsigned int i = 0; i < split.size(); i++){
    if(split[i] == "cd"){					// cd command
      cdCommand(split);
      return;
    }
    if(split[i] == "|"){
      pipeCounter ++;						// pipe counter ++
      processCounter ++;					// process counter ++
    }
    if(split[i] == "<" || split[i] == ">" ||
       split[i] == ">>" || split[i] == "e>" ||
       split[i] == "e>>"){
      redirectionPos = i;					// store the redirection position
      break;
    }
  }
  
  if(split.size() > 1 && split[split.size()-1] == "&"){
    ampersand = 1;
  }

  vector<string> * process = new vector<string>[processCounter];// store element in a 2d array

  int index = 0;
  int inFd = -10;
  int outFd = -10;
  int errFd = -10;
  for(int i = 0; (unsigned)i < split.size(); i++){
    if(i == redirectionPos){
      break;
    }
    if(ampersand == 1){
      if((unsigned)i == split.size()-1){
	break;
      }
    }
    if(split[i] != "|"){
      process[index].push_back(split[i]);			// store element split by pipe
    }else{
      index++;
    }
  }
  if(redirectionPos != -1){					// changed the job
    for(unsigned int i = redirectionPos; i < split.size(); i++){
      if(split[i] == "<" || split[i] == ">" ||
	 split[i] == ">>" || split[i] == "e>" || 
	 split[i] == "e>>"){
	if(i+2 > split.size()){
	  cerr << "Redirection fails." << endl;
	  return;
	}else if(split[i] == "<"){
	  inFd = open(split[i+1].c_str(), O_RDONLY); 
	  if(inFd == -1) perror("open");
	}else if(split[i] == ">"){
	  outFd = open(split[i+1].c_str(), O_WRONLY | O_CREAT, 0644); 
	  if(outFd == -1) perror("open");
	}else if(split[i] == ">>"){
	  outFd = open(split[i+1].c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644);
 	  if(outFd == -1) perror("open");
	}else if(split[i] == "e>"){
	  errFd = open(split[i+1].c_str(), O_WRONLY | O_CREAT, 0644); 
	  if(errFd == -1) perror("open");
	}else if(split[i] == "e>>"){
	  errFd = open(split[i+1].c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644); 
	  if(errFd == -1) perror("open");
	}
      }
    }
  }

  if(debug == 1){
    printDebug(processCounter, pipeCounter, process, split);
  }
  doubleQuote(processCounter, process);
  run(processCounter, process, inFd, outFd, errFd, ampersand);
  if (dup2(inBackup, STDIN_FILENO) == -1) perror("dup2");
  if (dup2(outBackup, STDOUT_FILENO) == -1) perror("dup2");
  if (dup2(errBackup, STDERR_FILENO) == -1) perror("dup2");
  for (int i = 0; i < processCounter; ++i) {			// deallocate 2-d array-vector
    process[i].clear();
  }
  delete [] process;
} //repl

    /******************************************
   void printDebug - prints out REPL
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: processCounter - number of processes
                pipeCounter - number of pipes
                process - string vector of user input
                split - vector of user input is split
  *******************************************/

void Shell::printDebug(unsigned int processCounter, unsigned int pipeCounter, vector<string> * process, vector <string> split){
  cout << "________________________________________________________" << endl;
  cout << endl;

  string stdIn = "STDIN_FILENO";
  string stdOut = "STDOUT_FILENO";
  string stdErr = "STDERR_FILENO";

  for(unsigned int i = 0; i < split.size(); i++){          
    if (split[i] == "<"){
      stdIn = split[i+1];
    }
    else if(split[i] == ">"){
      stdOut = split[i+1] + " (truncate)";
    }
    else if(split[i] == ">>"){
      stdOut = split[i+1] + " (append)";
    }
    else if(split[i] == "e>"){
      stdErr = split[i+1] + " (truncate)";
    }
    else if(split[i] == "e>>"){
      stdErr = split[i+1] + " (append)";
    }
    else if(split[i] == "|"){
      continue;
    }
    else{
      continue;
    }
  }

  cout << "Job STDIN = " << stdIn << endl
       << "Job STDOUT = " << stdOut << endl
       << "Job STDERR = " << stdErr << endl
       << endl;

  cout << pipeCounter << " pipe(s)" << endl;
  cout << processCounter << " process(es)" << endl;
  cout << endl;

  for(unsigned int i = 0; i < processCounter; i++){  
    cout << "Process " << i << " argv" << endl;   
    for(unsigned int j = 0; j < process[i].size(); j++){  
      cout << j << ": " << process[i][j] << endl;        
    }
    cout << endl;
  }
  cout << "________________________________________________________" << endl;
}

    /******************************************
   void doubleQuote - Checks to see if a word in the string is in double quotes
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: processCounter - number of processes
                process - string vector of user input
  *******************************************/

void Shell::doubleQuote(unsigned int processCounter, vector<string> * process){
  for(unsigned int i = 0; i < processCounter; i++){		       
    for(unsigned int j = 0; j < process[i].size(); j++){	
      if(process[i][j].size() > 1 && 
	 process[i][j].at(0) == '"' && 
	 process[i][j].at(process[i][j].size()-1)){		// check if there has double quote
	string temp = "";
	if(process[i].size() > 1){
	  for(unsigned int k = 1; k < process[i].size(); k++){
	    temp += process[i][k];
	    temp += " ";		      			// add space between it
	  }
	  temp.erase(0,1);					// take off ""
	  temp.erase(temp.length()-2,1);       			// take off ""
	  for(unsigned int l = 0; l < temp.length();l++){
	    if(temp.at(l) == '"'){				// take off "\\"
	      if(temp.at(l-1) == '\\'){
		temp.erase(l-1,1);
	      } 
	    }
	  }
	  process[i].clear();
	  process[i].push_back("echo");
	  process[i].push_back(temp);
	}
      }
    }
  }
}

    /******************************************
   void cdCommand - change directory
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: split - vector of user input is split
  *******************************************/

void Shell::cdCommand(vector <string> split){
  if(split.size() == 1){
    struct passwd * pw = getpwuid(getuid());
    const char * homedir = pw->pw_dir;
    chdir(homedir);
  }else if(split.size() == 2){
    if(split[1] == "~"){
      struct passwd * pw = getpwuid(getuid());
      const char * homedir = pw->pw_dir;
      chdir(homedir);
    }else{
      if(chdir(split[1].c_str()) == -1){
	perror("cd");
      }
    }
  }else{
    cout << "command not found." << endl;
  }
}

    /******************************************
   void run - runs the shell
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: processCounter - number of processes
                process - string vector of user input
                inFd - input file Descriptor
                outFd - output file Descriptor
                errFd - error file Descriptor
                int ampersand - checks to see if ampersand
  *******************************************/

void Shell::run(unsigned int processCounter, vector<string> * process, int inFd, int outFd, int errFd,int ampersand){
  int pid;
  vector<array<int, 2>> pipes;

  if(inFd != -10){// IO redirection for stdin
    if (dup2(inFd, STDIN_FILENO) == -1) perror("dup2");
  }
  if(outFd != -10){// IO redirection for stdout
    if (dup2(outFd, STDOUT_FILENO) == -1) perror("dup2");
  }
  if(errFd != -10){// IO redirection for stderr
    if (dup2(errFd, STDERR_FILENO) == -1) perror("dup2");
  }

  for (unsigned int i = 0; i < processCounter; ++i) {
    if (i != processCounter-1) {
      int pipefd [2];
      if (pipe(pipefd) == -1) {
	perror("pipe");
	exit(EXIT_FAILURE);
      } // if
      pipes.push_back({pipefd[0], pipefd[1]});
    } // if

    if ((pid = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      signal(SIGINT, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);
      signal(SIGTSTP, SIG_DFL);
      if (i != 0) {
	if (dup2(pipes.at(i-1)[0], STDIN_FILENO) == -1) {
	  perror("dup2");
	  exit(EXIT_FAILURE);
	} // if
      } // if

      if (i != processCounter - 1) {
	if (dup2(pipes.at(i)[1], STDOUT_FILENO) == -1) {
	  perror("dup2");
	  exit(EXIT_FAILURE);
	} // if
      } // if

      // close all pipes created so far
      for (unsigned int i = 0; i < pipes.size(); ++i) {
	close_pipe(pipes.at(i).data());
      } // for
      if(ampersand != -1){
	setpgid(getpid(), getppid());
      }
      nice_exec(process[i], inFd,outFd, errFd);
    } // if

  } // for

    // close all pipes
  for (unsigned int i = 0; i < pipes.size(); ++i) {
    close_pipe(pipes.at(i).data());
  } // for
  if(ampersand != -1){
    setpgid(getpid(), getppid());
  }


  child.push_back(pid);// store the child pid

  int status;
  if(ampersand == -1){
    waitpid(pid, &status, WUNTRACED | WCONTINUED);
  }

  if (WIFEXITED(status)) {
    exitStatus = WEXITSTATUS(status);
    if(exitStatus == 0 || exitStatus == 1){
      child.pop_back();
      childName.pop_back();
    }
  }
}

    /******************************************
   void close_pipe - closes a pipe
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: pipefd - pipe file Descriptor
  *******************************************/

void Shell::close_pipe(int pipefd [2]) {
  if (close(pipefd[0]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
  if (close(pipefd[1]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
} // close_pipe

    /******************************************
   void mk_cstrvec - c string vector
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: strvec - string vector
  *******************************************/

vector<char *> Shell::mk_cstrvec(vector<string> & strvec) {
  vector<char *> cstrvec;
  for (unsigned int i = 0; i < strvec.size(); ++i) {
    cstrvec.push_back(new char [strvec.at(i).size() + 1]);
    strcpy(cstrvec.at(i), strvec.at(i).c_str());
  } // for
  cstrvec.push_back(nullptr);
  return cstrvec;
} // mk_cstrvec

    /******************************************
   void dl_cstrvec - c string vector
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: strvec - string vector
  *******************************************/

void Shell::dl_cstrvec(vector<char *> & cstrvec) {
  for (unsigned int i = 0; i < cstrvec.size(); ++i) {
    delete[] cstrvec.at(i);
  } // for
} // dl_cstrvec

    /******************************************
   void nice_exec - executes FD
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
    Parameters: strargs - string arguments
                inFd - input file Descriptor
                outFd - output file Descriptor
                errFd - error file Descriptor

  *******************************************/

void Shell::nice_exec(vector<string> strargs, int inFd, int outFd, int errFd) {
  vector<char *> cstrargs = mk_cstrvec(strargs);
  execvp(cstrargs.at(0), &cstrargs.at(0));
  perror("execvp");
  dl_cstrvec(cstrargs);
  if(inFd != -10){
    if (close(inFd) == -1) perror("close"); 
  }
  if(outFd != -10){
    if (close(outFd) == -1) perror("close"); 
  }
  if(errFd != -10){
    if (close(errFd) == -1) perror("close"); 
  }
  exit(EXIT_FAILURE);
} // nice_exec

    /******************************************
   void autoComplete - autoCompletes user input upon hitting tab
    Author: Stephen Kim and Zhenyu Yan
    Date: 5/2/2017
  *******************************************/

string Shell::autoComplete(){

  string nameString;
  char* buf;
  buf = readline(" ");

  if (buf[0]!=0){
    add_history(buf);
  }
      
  std::string str(buf);
  nameString = str;
  free(buf);

  return nameString;
}

