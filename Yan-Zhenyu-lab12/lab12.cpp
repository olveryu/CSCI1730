
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

void repl(string str);

int main(){
  cout.setf(std::ios_base::unitbuf);
  while(true){
    string str;
    cout << "repl$:";
    getline(cin,str);						// get user input
    repl(str);							// read user input
  }
  return EXIT_SUCCESS;
}// main

/*
 * this function is to print out the information of the user input
 *
 *@param: str which is the user input
 *
 */
void repl(string str){
  int pipeCounter = 0;						// count how many pipe
  int processCounter = 1;					// count how many process
  int redirectionPos = -1;					// check if there has any redirection
  string stdin = "STDIN_FILENO";				// standard input
  string stdout = "STDOUT_FILENO";				// standard output
  string stderr = "STDOUT_FILENO";				// standard error

  vector <string> split;					// vector to store all the element split by space
  string buf;							// buffer
  stringstream ss(str);						// stringstream to seperate the element
  while(ss >> buf) split.push_back(buf);			// store in the verctor split

  for(unsigned int i = 0; i < split.size(); i++){
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
  vector<string> * process = new vector<string>[processCounter];// store element in a 2d array
  int index = 0;
  for(int i = 0; (unsigned)i < split.size(); i++){
    if(i == redirectionPos){
      break;
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
	  stdin = split.at(i+1);
	}else if(split[i] == ">"){
	  stdout = split.at(i+1);
	  stdout += "(truncate)";
	}else if(split[i] == ">>"){
	  stdout = split.at(i+1);
	  stdout += "(append)";
	}else if(split[i] == "e>"){
	  stderr = split.at(i+1);
	  stderr += "(truncate)";
	}else if(split[i] == "e>>"){
	  stderr = split.at(i+1);
	  stderr += "(append)";
	}
      }
    }
  }
  
  cout << endl				   			// print out the information
       <<"job STDIN  = " << stdin << "\n"
       << "job STDOUT = " << stdout << "\n"
       << "job STDERR = " << stderr << "\n"
       << endl
       << pipeCounter << " pipe(s)" << "\n"
       << processCounter << " process(es)" << "\n" 
       << endl;
  for(int i = 0; i < processCounter; i++){			// print out the argv
    cout << "Process " << i << " argv:" << endl;
    for(unsigned int j = 0; j < process[i].size(); j++){
      if(process[i][j] == "echo"){				// echo command
	string temp = "";
	cout << j << ": " << process[i][j] << endl;

	for(unsigned int k = 1; k < process[i].size(); k++){
	  temp += process[i][k];
	  temp += " ";						// add space between it
	}
	temp.erase(0,1);					// take off ""
	temp.erase(temp.length()-2,1);				// take off ""
	for(unsigned int l = 0; l < temp.length();l++){
	  if(temp.at(l) == '"'){				// take off "\\"
	    if(temp.at(l-1) == '\\'){
	      temp.erase(l-1,1);
	    } 
	  }
	}
	cout << j+1 << ": " << temp << endl;
	break;
      }
      cout << j << ": " << process[i][j] << endl;
    }
    cout << endl;
  }
  for (int i = 0; i < processCounter; ++i) {
    process[i].clear();
  }
  delete [] process;
} //repl
