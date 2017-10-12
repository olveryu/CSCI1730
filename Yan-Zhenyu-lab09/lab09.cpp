
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <grp.h>
#include <string>
#include <sstream>
#include <string.h>
#include <fcntl.h>

using std::string;
using std::stringstream;

int main(int argc, char *argv[]){
  struct stat sb;

  //check if the user input a filename after the application
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for(int i=1; i< argc; i++){
    // check if the file exist    
    string fileName = argv[i];
    if(fileName == "-"){
      fstat(STDIN_FILENO,&sb);
    }else{
      if(lstat(argv[i], &sb) == -1){
	printf("  File: `%s'\n",		// check file exist
	       argv[i]);
	perror("  stat");
	printf("\n");
	continue;
      }
    }
    // first line of fileName
    if(S_ISLNK(sb.st_mode)){			// check fileName for symbolic link
      char buf[1000];
      char * path = realpath(argv[i],buf);
      fileName = "`";
      fileName += argv[i];
      fileName += "'";
      fileName += "->";
      fileName += "`";
      fileName += path;
      fileName += "'";
    }else{
      fileName = "`";
      fileName += argv[i];
      fileName += "'";
    }
    printf("  File: %s\n",		        // print filename
	   fileName.c_str());
    
    // second line
    printf("  Size: %lld\t\t",			// print size	
	   (long long) sb.st_size);	 
    printf("Blocks: %lld\t   ",			// print block
	   (long long) sb.st_blocks);
    printf("IO Block: %ld   ",			// print IO block
	   (long) sb.st_blksize);
    switch (sb.st_mode & S_IFMT) {		// print the file type
      case S_IFBLK:  printf("block device\n");            break;
      case S_IFCHR:  printf("character device\n");        break;
      case S_IFDIR:  printf("directory\n");               break;
      case S_IFIFO:  printf("FIFO/pipe\n");               break;
      case S_IFLNK:  printf("symlink\n");                 break;
      case S_IFREG: 
	if((long long) sb.st_size == 0){
	  printf("regular empty file\n");           
	}else{
	  printf("regular file\n");
	}
	break;
      case S_IFSOCK: printf("socket\n");                  break;
      default:       printf("unknown?\n");                break;
    }
    
    // thrid line
    printf("Device: %lxh/%ldd\t",			// print device
	   (long) sb.st_dev,
	   (long) sb.st_dev);
    
    printf("Inode: %ld\t   ",			// print inode
	   (long) sb.st_ino);
    
    printf("Links: %ld\n",			// print links
	   (long) sb.st_nlink);
    
    // forth line
    int mode = (int) sb.st_mode;
    stringstream modeSs;
    modeSs << std::oct << mode;
    string modeString(modeSs.str());
    modeString = modeString.substr(modeString.length()-4,4);
    
    printf("Access: (%s/",			// print it in octal format
	   modeString.c_str());

    // this is to determine the type of the file
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
    
    // this is just the last parenthesis
    printf(")  ");
    
    
    struct passwd *pw;
    struct group *gr;

    pw = getpwuid(sb.st_uid);
    gr = getgrgid(sb.st_gid);
    printf("Uid: (%ld/  %s)\t",    		// print uid
	   (long) sb.st_uid,
	   pw->pw_name);
    printf("Gid: (%ld/  %s)\n",			// print gid
	   (long) sb.st_gid,
	   gr->gr_name);
    
    
    // 5,6,7 line of time
    printf("Access: %s", ctime(&sb.st_atime));
    printf("MODIFY: %s", ctime(&sb.st_mtime));
    printf("change: %s\n", ctime(&sb.st_ctime));  
  }
  exit(EXIT_SUCCESS);
}
