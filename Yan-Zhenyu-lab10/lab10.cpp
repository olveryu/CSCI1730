#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>

using std::string;
using std::cout;
using std::endl;
using std::cin;

void deleteDirectory(string tempName,bool force);

int main(int argc, char *argv[]){

  if (argc < 2) {						// check user input
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }  
  string temp = argv[1];
  if(temp == "-r" || temp == "-rf"){				// if there are option
    if(argc == 2){
      fprintf(stderr,"Missing operand");
      exit(EXIT_FAILURE);
    }else{
      if(temp == "-r"){						// check if user want to unlink a directory
	for(int i = 2; i < argc; i++){
	  string fileName;
	  fileName = argv[i];
	  deleteDirectory(fileName,false);			// delete file
	}
      }else{
      	for(int i = 2; i < argc; i++){				// delete file with -f command
	  string fileName;
	  fileName = argv[i];
	  deleteDirectory(fileName,true);
	}
      }
    }
  }else{
    if(temp == "-f"){						
      if(argc == 2){						// check user input
	fprintf(stderr,"Missing operand");
	exit(EXIT_FAILURE);
      }
      for(int i = 2; i < argc; i++){			        // delete file with -f command
	if (unlink(argv[i]) != 0){
	  perror("rm");
	}
      }
    }else{
      for(int i = 1; i< argc; i++){
	struct stat sb;
	stat(argv[i],&sb);
	int fileMode = sb.st_mode;
	if(fileMode & S_IWUSR){
	  if (unlink(argv[i]) != 0){
	    perror("rm");
	  }
	}else{
	  while(true){
	    cout << "rm: remove write-protected: "
		 << argv[i]
		 << " ? ";
	    string yesNo;
	    cin >> yesNo;					// ask user for premission
	    if(yesNo == "yes"){
	      if (unlink(argv[i]) != 0){
		perror("rm");
	      }
	      break;
	    }else{
	      break;
	    }
	  }
	}
      }
    }
  }
  exit(EXIT_SUCCESS);
} // main


/*
 * function: recursively delete directory
 *
 * @param: fileName which is the name of the directory
 * @param: force which is the force command "-f"
 *
 * @return: void
 */

void deleteDirectory(string fileName, bool force){
  DIR * dir;
  struct dirent * dp;
  struct stat sb;
  dir = opendir(fileName.c_str());				// open DIR
  if(dir){
    while((dp = readdir(dir)) != NULL){
      if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")){
	continue;
      }
      string tempName = fileName;				// get the fileName with his path
      tempName += "/";
      tempName += dp->d_name;
      stat(tempName.c_str(),&sb);
      if (S_ISDIR(sb.st_mode)){
      	deleteDirectory(tempName, force);	    		// recursively call this function
      }else{
	if(!force){						// with out force mode
	  int fileMode = sb.st_mode;
	  if(fileMode & S_IWUSR){
	    if (unlink(tempName.c_str()) != 0){
	      perror("rm");
	    }
	  }else{
	    while(true){
	      cout << "rm: remove write-protected: "
		   << tempName
		   << " ? ";
	      string yesNo;
	      cin >> yesNo;					// ask user for premission
	      if(yesNo == "yes"){
		if (unlink(tempName.c_str()) != 0){
		  perror("rm");
		}
		break;
	      }else{
		break;
	      }
	    }
	  }
	}else{
	  if (unlink(tempName.c_str()) != 0){			// with force mode
	    perror("rm");
	  }
	}
      }
    }
    closedir(dir);						// close DIR
    rmdir(fileName.c_str());
  }else{
    perror("rm");
  }
}
