1.wget http://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz

2.	
	a.z = filter the archive through gzip
	b.x = extract file from an archive
	c.v = verbosely list files processed
	d.f = use archive file or device ARCHIVE
3.“configure” configures this package to adapt to many kinds of systems.

4.Install architecture-independent files in PREFIX  [/usr/local]

5./home/ugrads/zhenyu/lib/terminfo

6.LD_LIBRARY_PATH is the predefined environmental variable in Linux/Unix which sets the path which the linker should look in to while linking dynamic libraries/shared libraries.

7.because if it did not appears twice, it will wipe out the stuff there before instead of to append it to LD_LIBARY_PATH.

8.So the shell shall give the export attribute to the variables corresponding to the specified names, which shall cause them to be in the environment of subsequently executed commands. 

9.	  
	  a.Initscr: initscr is normally the first curses routine to call  when initializing  a program.  
	  b.Printw: are analogous to printf. In effect, the string that would be output by printf is output instead as though waddstr were used on the given window.
	  c.Refresh: must be called to get actual output to the terminal, as other routines  merely  manipulate  data structures.
	  d.Getch: is used to get a character from console but does not echo to the screen.
	  e.Endwith: The  program must also call endwin for each terminal being  used before exiting from curses.  

10.Because we need the ncruses libary function to compile the sample code.

11.Because we need the ncruses libary function, so we need to link the programs with -lncruse.