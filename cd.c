	
#include "headers.h"

/*	set the environment variables for PWD
	PWD Environment variables are changed
	after successfull chdir() to reflect 
	changes on the prompt.

	note: do not use  putenv to updtae environment variables
	if you consistent results across various permissions.
*/		
void add(char * name,char * value){
	unsetenv(name);
	setenv(name,value,1);
}


void dump(char * name){
	char * value = getenv(name);
	printf(" %s = %s \n",name,value);
}


int cd(char * argv[] , int argc){

	char cwd[1024];

	if(argc > 2){

	printf("\nToo many arguments\n");
	return -1;

	}

	//the default behaviour of cd is to return to home directory
    if(argv[1]==NULL){

		if( chdir(getenv("HOME") )==0){
			add("PWD",getenv("HOME"));
			dump("PWD");
			return 0;
		}

	}


	if(chdir(argv[1])!=0){

		printf("\n No Such Directory\n");
		return -1;

	}

	if (!getcwd (cwd, sizeof(cwd))) {
	
		perror ("getcwd");
		exit (EXIT_FAILURE);
	}
	else {
		//update PWD with the value of CWD and print
		add("PWD",cwd);
		dump("PWD");
	}

	return 0;

}
