
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>
#include <pwd.h>
#include <grp.h>

using namespace std;

void list(bool a, bool l, string path);
void listLine(const string * storage,int fileCounter, bool a, string path);
int file_exist(const char *filename);

int main(int argc, char * argv[]) {
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);
  int opt= 0;
  bool a = false;							                                                  // option a (directory entries)
  bool l = false;							                                                  // option l (long format)
  while ((opt = getopt(argc, argv, "al")) != -1){
    switch (opt) {
    case 'a' :
      a = true;
      break;
    case 'l' : 
      l = true;
      break;
    case '?':
      break;
    }
  }

  if(optind == argc){							                                              // current directory
    list(a, l, ".");
  }else{
    for(int i = optind; i < argc; i++){
      list(a,l,argv[i]);						                                            // argv[] directory
    }
  }
  
  return EXIT_SUCCESS;
} // main

    /******************************************
   list - lists out the ls information 
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: a = boolean for all directory entries
            l = boolean for long format
            path = path of the ls
  *******************************************/

void list(bool a, bool l, string path){
  struct stat sb;
  stat(path.c_str(),&sb);
  if(!S_ISDIR(sb.st_mode)){						                                            // check if it is a single file
    if(l){
      if(file_exist(path.c_str())){
	string * temp = new string[1];
	int found = path.find_last_of("/");
	if(found != -1){
	  temp[0] = path.substr(found+1);
	  path = path.substr(0,found);
	}else{
	  temp[0] = path;
	  path = ".";
	}
	listLine(temp, 1, a, path);	    				                                       // print out line format
	delete [] temp;
      }else{
	perror("open");
      }
    }else{
      if(file_exist(path.c_str())){
	string temp = "";
	int found = path.find_last_of("/");
	if(found != -1){
	  temp = path.substr(found+1);
	  path = path.substr(0,found);
	}else{
	  temp = path;
	  path = ".";
	}
	printf("%s\n",temp.c_str());					                                       // print out normal format
      }else{
	perror("open");
      }
    }
  }else{								                                                       // if it is not a single file
    DIR * dir;
    struct dirent * entry;
    dir = opendir(path.c_str());
    if(dir){
      int fileCounter1 = 0;
      while((entry = readdir(dir)) != nullptr){				                         // count how many file in the directory
	fileCounter1 ++;
      }
      closedir(dir);      
      string * storage1 = new string[fileCounter1];		                         // store the fileName
      dir = opendir(path.c_str());
      for(int i = 0;(entry = readdir(dir)) != nullptr; i++){
	storage1[i] += entry->d_name;
      }
      sort(storage1, storage1 + fileCounter1);				                         // sort the order of the file
      closedir(dir);

      if(a && l){							// option a and l
	listLine(storage1, fileCounter1, a, path);
      }else if(a){							// option a
	for(int i = 0; i < fileCounter1; i++){
	  printf("%s  ",storage1[i].c_str());
	}
	printf("\n");
      }else if(l){							// option l
	listLine(storage1, fileCounter1, a, path);
      }else{								// no option;
	for(int i = 0; i < fileCounter1; i++){
	  string temp = storage1[i];
	  if(temp.at(0) == '.'){
	    continue;
	  }	  
	  printf("%s  ",storage1[i].c_str());
	}
	printf("\n");
      }
      delete [] storage1;               			                                 // deallocate 1st dimension
    }else{
      printf("ls: can not access ");
      perror(path.c_str());
    }
  }
}

    /******************************************
   listLine - lists out the ls information 
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: storage = stores the information of ls to be printed
            fileCounter = tracks how many files were found
            a = boolean for writing out directory entries
            path = path of the ls
  *******************************************/

void listLine(const string * storage, int fileCounter ,bool a,string path){
  struct stat sb;
  int totalBlock = 0;
  for(int i = 0; i < fileCounter; i++){
    stat(storage[i].c_str(),&sb);
    if(!a){
      string temp = storage[i];
      if(temp.at(0) == '.'){
	totalBlock -= sb.st_blocks;
      }
    }
    totalBlock += sb.st_blocks;
  }
  printf("total %d\n",totalBlock/2);				        	                         // list the total block

  for(int i = 0; i < fileCounter; i++){				                                 // this is to determine the type of the file
   if(!a){
     string temp = storage[i];
      if(temp.at(0) == '.'){
	continue;
      }
    }
    string temp = path;
    temp += "/";
    temp += storage[i]; 
    lstat(temp.c_str(),&sb);
    string fileType = "";
    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      fileType = "b";
      break;
      
    case S_IFCHR:
      fileType = "c";
      break;
      
    case S_IFDIR:
      fileType = "d";
      break;
      
    case S_IFIFO:
      fileType = "p";
      break;
      
    case S_IFLNK:
      fileType = "l";
      break;
      
    case S_IFREG:
      fileType = "-";
      break;
      
    case S_IFSOCK:
      fileType = "s";
      break;
      
    default:
      fileType = "?";
      break;
    }
    
    printf(fileType.c_str());
    
    int fileMode;
    
    fileMode = sb.st_mode;

                                                                // user    
    if (fileMode & S_IRUSR){
      printf("r");
    }else{
      printf("-");
    }
    
    if (fileMode & S_IWUSR){
      printf("w");
    }else{
      printf("-");
    }
    
    if (fileMode & S_IXUSR){
      if(fileMode & S_ISUID){
	printf("s");
      }else{
	printf("x");
      }
    }else{
      if(fileMode & S_ISUID){
	printf("S");
      }else{
	printf("-");
      }
    }
    
                                                                  // group
    if (fileMode & S_IRGRP){
      printf("r");
    }else{
      printf("-");
    }
    if (fileMode & S_IWGRP){
      printf("w");
    }else{
      printf("-");
    }
    if (fileMode & S_IXGRP){
      if(fileMode & S_ISGID){
	printf("s");
      }else{
	printf("x");
      }
    }else{
      if(fileMode & S_ISGID){
	printf("S");
      }else{
	printf("-");
      }
    }
    
                                                                 // other
    if (fileMode & S_IROTH){
      printf("r");
    }else{
      printf("-");
    }
    if (fileMode & S_IWOTH){
      printf("w");
    }else{
      printf("-");
    }
    if (fileMode & S_IXOTH){
      if(fileMode & S_ISVTX){
	printf("t");
      }else{
	printf("x");
      }
    }else{
      if(fileMode & S_ISVTX){
	printf("T");
      }else{
	printf("-");
      }
    }
    printf(".");

    struct passwd *pw;
    struct group *gr;
    pw = getpwuid(sb.st_uid);
    gr = getgrgid(sb.st_gid);

    printf("%*ld ",4, (long) sb.st_nlink);				              // link number
    printf("%s     ", pw->pw_name);			      		              // uid
    printf("%s     ", gr->gr_name);		       			              // gid
    printf("%*lld ",8, (long long)sb.st_size);		              // size

    time_t timer;
    char buffer[26];
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&sb.st_ctime);
    strftime(buffer, 26, "%b %d %H:%M", tm_info);			          // time
    printf(buffer);

    printf("  %s\n",storage[i].c_str());				                // file Name
  }
}

    /******************************************
   file_exist - checks to see if the file exists 
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: filename = the filename
  *******************************************/

int file_exist (const char *filename){
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}
