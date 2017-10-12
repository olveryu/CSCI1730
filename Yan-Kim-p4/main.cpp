#include "Shell.h"

int main(){
  cout.setf(ios_base::unitbuf);
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);

 cout  << "_______________________" << endl
       << "< Hello, cs1730!      >" << endl
       << "< check out my SHELL  >" << endl
       << "< type exit to quit.  >" << endl
       << "_______________________" << endl
       << "\\                                  ___-------___"                                 << endl
        << "\\                             _-~~             ~~-_"                             << endl
        << " \\                          _-~                    /~-__"                        << endl
        << "         /^\\__/^\\          /~ \\                   /     \\ "                   << endl
        << "        /|  O|| O|        /      \\_______________/        \\ "                   << endl
        << "       | |___||__|      /       /                \\          \\ "                 << endl
        << "       |          \\   /      /                    \\          \\ "               << endl
        << "       |   (_______) /______/                        \\_________ \\ "             << endl
        << "       |         / /         \\                      /            \\ "            << endl
        << "        \\         \\^\\       \\                  /               \\     /"      << endl
        << "          \\         ||          \\______________/      _-_       //\\__//"       << endl
        << "            \\       ||------_-~~-_ ------------- \\ --/~   ~\\    || __/"        << endl
        << "              ~-----||====/~     |==================|       |/~~~~~"              << endl
        << "               (_(__/  ./     /                    \\_\\      \\."                << endl
        << "                      (_(___/                         \\_____)_)"                 << endl
        << endl;


 Shell turtleShell;

  while(true){
    turtleShell.bashName();							// display bash name
    turtleShell.userInput();
  }

  return EXIT_SUCCESS;
}// main
