		//cd.c		
		#include "headers.h"

		//set the environment variables for PWD
		//PWD Environment variables are changed
		//after successfull chdir() to reflect 
		//changes on the prompt		
		void add(char * name,char * value){

		    unsetenv(name);
		    setenv(name,value,1);
		//note: do not use  putenv to updtae environment variables
		//it  will not produce consistent results acroos su permissions
		//and virtual machines and is buggy


		}
		void dump(char * name){

		    char * value=getenv(name);
		    printf("%s=%s\n",name,value);


		}


		int cd(char * argv[],int argc){

		    char cwd[1024];

		   //check for argument count

	     if(argc>2){
	printf("\n Too many arguments cd accepts only one argument that is the directory name\n");
		return -1;
	     }
			
		//the default behaviour of cd in most shell is to return to home directory
		    if(argv[1]==NULL){
			if(chdir(getenv("HOME"))==0){
			    add("PWD",getenv("HOME"));
			    dump("PWD");
			    return 0;
			}

		    }

		   
		   if(chdir(argv[1])!=0){
		    printf("\n No Such Directory\n");
		    printf("\nUSAGE:> cd Dir_name [Where Directory_Name is the Directory name] \n");
		    return -1;

	         }

		//if chdir is successfull store the current directory in an array
		    if (!getcwd (cwd, sizeof(cwd))) {
			perror ("getcwd");
			exit (EXIT_FAILURE);

		    }

		    else{
			//update PWD with the value of CWD and print
			add("PWD",cwd);
			dump("PWD");


		    }
	
			return 0;

		}
