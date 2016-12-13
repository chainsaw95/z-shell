	//headers.h	
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/stat.h>
	#include <gnu/libc-version.h>
	#include <unistd.h>
	#include <errno.h>
	#include <string.h>
	#include <dirent.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <ctype.h>
	#include <time.h>
	#include <glob.h>
	#include <readline/readline.h>
	#include <readline/history.h>




	#define READ_END 0
	#define WRITE_END 1
	#define MAX_SIZE 1024
	#define MAX_OPTION 10
	#define MAX_ARGS 50
	#define debug 0
	#define ANSI_COLOR_RED "\x1b[31m"
	#define ANSI_COLOR_GREEN "\x1b[32m"
	#define ANSI_COLOR_YELLOW "\x1b[33m"
	#define ANSI_COLOR_BLUE "\x1b[34m"
	#define ANSI_COLOR_MAGENTA "\x1b[35m"
	#define ANSI_COLOR_CYAN "\x1b[36m"
	#define ANSI_END_COLOR "\033[0m"
	#define PRINT_RED(x) printf("%s%s%s",ANSI_COLOR_RED,x,ANSI_END_COLOR);
	#define PRINT_GREEN(x) printf("%s%s%s",ANSI_COLOR_GREEN,x,ANSI_END_COLOR);
	#define PRINT_YELLOW(x) printf("%s%s%s",ANSI_COLOR_YELLOW,x,ANSI_END_COLOR);
	#define PRINT_BLUE(x) printf("%s%s%s",ANSI_COLOR_BLUE,x,ANSI_END_COLOR);
	#define PRINT_MAGENTA(x) printf("%s%s%s",ANSI_COLOR_MAGENTA,x,ANSI_END_COLOR);
	#define PRINT_CYAN(x) printf("%s%s%s",ANSI_COLOR_CYAN,x,ANSI_END_COLOR);
	#define MAX_COLOR_SCHEME 3
	#define NO_READLINE 0

	 

