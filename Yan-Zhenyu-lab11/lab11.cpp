#include <unistd.h>                                      
#include <getopt.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <string>
#include <fcntl.h>


using std::string;

int copyFile(string fileName1, string fileName2);
int copyDirectory(string fileName1,string fileName2);

int main(int argc, char *argv[]){
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);	       		// set printf unbuffer

  if (argc < 3 || argc > 4) {				        // check user argc number
    fprintf(stderr, "Usage: %s (-option) <pathname> <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);						// exit
  }

  if(argc == 3){						// 3 argument
    struct stat sb;  
    string fileName1 = argv[1];
    string fileName2 = argv[2];
    stat(fileName1.c_str(),&sb);
    if (S_ISDIR(sb.st_mode)){					// check if the user try to copy a dir
      fprintf(stderr, "cp: omitting directory `%s'\n", argv[1]);
      exit(EXIT_FAILURE);					// exit
    }
    stat(fileName2.c_str(),&sb);
    if(S_ISDIR(sb.st_mode)){					// check if the user try to copy in to a dir
      fileName2 += "/";
      fileName2 += fileName1;
    }
    copyFile(fileName1,fileName2);     				// copy file
  }else{							// 4 argument
    int option;
    opterr = 0;
    while((option = getopt(argc, argv, "r:")) != -1){
      string fileName1;
      string fileName2;
      int fd = -1;
      switch(option){
      case 'r':
	fileName1 = argv[2];
	fileName2 = argv[3];
	fd = open(fileName2.c_str(),O_RDONLY);
	if(fd == -1){						// check if the directory does not exist
	  copyDirectory(fileName1,fileName2);			// copy directory
	}else{							// check if the directory exist
	  fileName2 += "/";
	  fileName2 += fileName1;
	  copyDirectory(fileName1,fileName2);			// copy directory
	}
	break;
      default:
	fprintf(stderr,"No such option, please try -r.\n");
        exit(EXIT_FAILURE);					// exit
      }
    }
  }
  return EXIT_SUCCESS;
}// main

/*
 * function: to copy file
 *
 * @param: fileName1 is the file to copy
 * @param: fileName2 is the name of the new file
 *
 * @return: int, 0 success, other fail
 */

int copyFile(string fileName1, string fileName2){
  int in_file;
  int out_file;
  const int BUFF_SIZE = 1024;
  char buffer[BUFF_SIZE];
  int n;
  struct stat sb;
  stat(fileName1.c_str(),&sb);
  if((in_file = open(fileName1.c_str(), O_RDONLY)) == -1){	// file open to read
    fprintf(stderr,"file:%s can not ",fileName1.c_str());
    perror("open");
    return -1;
  }
  if((out_file = open(fileName2.c_str(),O_WRONLY | O_CREAT, sb.st_mode)) == -1){// file open to write
    fprintf(stderr,"file:%s can not ",fileName2.c_str());
    perror("copy");
    return -2;
  }
  while((n = read(in_file, buffer, BUFF_SIZE)) > 0){
    if (write(out_file, buffer, n) == -1) {
      perror("write");
      return -3;
      }
    }
  close(in_file);						// file open to read close
  close(out_file);						// file open to write close
  return 0;
}// copyFile


/*
 * function: recursively copy directory
 *
 * @param: fileName1 which is the name of the directory
 * @param: fileName2 is the new directory new
 *
 * @return: int 0 is success, others are fail
 */

int copyDirectory(string fileName1, string fileName2){
  DIR * dir1;
  struct dirent * entry;
  struct stat sb;
  dir1 = opendir(fileName1.c_str());
  if(dir1){
    stat(fileName1.c_str(),&sb);
    mkdir(fileName2.c_str(),sb.st_mode);
    while((entry = readdir(dir1)) != NULL){
      if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")){
	continue;
      }
      string tempName1 = fileName1;
      tempName1 += "/";
      tempName1 += entry->d_name;
      string tempName2 = fileName2;
      tempName2 += "/";
      tempName2 += entry->d_name;
      stat(tempName1.c_str(),&sb);
      if(S_ISDIR(sb.st_mode)){
	copyDirectory(tempName1,tempName2);
      }else{
	copyFile(tempName1,tempName2);
      }
    }
  }else{
    perror("copyDirectory");
    closedir(dir1);
    return -1;
  }
  closedir(dir1);
  return 0;
}// copy directory;
