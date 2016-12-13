				
		//main.c
		#include "headers.h"
		#include "display.c"
		#include "pipes_redirection.c"
		#include "cd.c"
		#include "list.c"
		#include "globbing.c"



		void ctrl_C(int sig){

		//we setup a signal for the SIGINT signal so that the shell does not terminate when
		//the user sends a terminate signal to the child process			
			printf(" Signal recieved [Exit by typing exit]\n");


		}


		int color_scheme=0;


		void color(){
	
		// circlulate around with the specified color schemes
		//add additional user scemens with scheme code in display if needed
			color_scheme++;
			if(color_scheme==MAX_COLOR_SCHEME)
			color_scheme=0;
	

		}



		int execute(char * argv[],int argc){

			int status; 
			int i;
			int background=0;
		    	
			//if the last argument is an ampersand '&' setup a flag 
			//and run the process in the background without waiting

	
			if(strchr(argv[argc-1],'&')!=NULL){
				background=1;
				argv[argc-1]=NULL;
				argc--;
			}

			if(strcmp(argv[0],"cd")==0){
					cd(argv,argc);
			}
			else if(strcmp(argv[0],"list")==0){
		
					list();
			}
			else if(strcmp(argv[0],"color")==0){

					color();
	
			}
			else
			{
			//child_process will contain the pid of the child
			 
		
				pid_t child_process=fork();	
				if(child_process<0){

					fprintf(stderr, "cant fork process%s\n",strerror(errno) );
					return 1;
				}
				else if(child_process==0){
		
			//execution of child starts here
			//check to see if the last argument is a null argument
			//the first argument is the program name the second is a char pointer
			// array of arguments 					
					if(execvp(argv[0],argv)<0){
					    fprintf(stderr, "cant run program:%s\n",strerror(errno) );
			
					    return 1;
					}
			
					}
				else
				{
			
			

					if(!background){
			//the process is not running in background wait for the process
			//give terminal access to user after program execution
					while(wait(&status)!=child_process)
						;

					}


				}



			}
	
			return 0;
		}


		   
		int parse(char * buffer,size_t argv_size)
		    {

			char *p, *start_of_word;
			char *argv[30];
			int c,i,j;
		
			memset(argv,0,sizeof(argv));
			int flag_pipe_or_redirection=0;
		   
		//parser works in three states
		//split string based on spaces
		//if space is present when parser in state IN_STRING ignore space
	


		    enum states { START, IN_WORD, IN_STRING } state = START;
			size_t argc = 0;

			for (p = buffer; argc < argv_size && *p != '\0'; p++) {
			    c = (unsigned char) *p;
				switch (state) {
				    case START:

				             if (isspace(c)) {
				                 continue;
				              }

				               if (c == '"') {
				                  state = IN_STRING;
				                  start_of_word = p + 1;
				                  continue;
				                }
				                        state = IN_WORD;
				                        start_of_word = p;
				                        continue;

				     case IN_STRING:
				                        if (c == '"') {
				                                *p = 0;
				                            argv[argc++] = start_of_word;
				                            state = START;
				                        }
				                        continue;

				     case IN_WORD:
				                        if (isspace(c)) {
				                                *p = 0;
				                            argv[argc++] = start_of_word;
				                            state = START;
				                        }
				                        continue;
				                }
				    }

		       		 argv[argc++] = start_of_word;
	

		//check to see if argument contains pipe or redirection if yes
		//set up a flag

		for (i = 0; i < argc; i++)
		{
		if(strchr(argv[i],'|')!=NULL || strchr(argv[i],'<')!=NULL || strchr(argv[i],'>')!=NULL)
		flag_pipe_or_redirection=1;
		 }
		    
		       


		//if the redirection flag is set call the handler

		    if(flag_pipe_or_redirection){
		    	
				   pipes_redirection(argv,argc);

			     return 0;

		  	}
		    


			execute(argv,argc);
		
			return 0;

		}


		int main(){

		//setup a signal hanler for the shell to handle SIGINT interrupts		    
		(void) signal(SIGINT,ctrl_C);
		    
		    char buf[MAX_SIZE];
		    int i,argc;
		    char * input;
		   
			//
			welcome();
	do{	

		

	if(NO_READLINE==0){
					print_prompt();
		    			input=readline("\x1b[31m > \033[0m");
		   			if(strlen(input)==0){
							strcpy(buf,"\n");
					}
					else{
							strcpy(buf,input);
					}

	if(buf[0]=='e' && buf[1]=='x' && buf[2]=='i' && buf[3]=='t' || strcmp(buf,"exit")==0){                
														
					exit(0);
					printf("Cannot exit shell now! try again");
							
	}       
		
		 }



	if(NO_READLINE){
					print_prompt();
					fgets(buf,MAX_SIZE,stdin);
			
	if(strlen(buf)>1)
		   if(buf[0]=='e' && buf[1]=='x' && buf[2]=='i' && buf[3]=='t'){                
							return 0;
							exit(0);
					}
        		}


	if(strchr(buf,'*')!=NULL || strchr(buf,'[')!=NULL)
		    			glob_parser(buf);
	else if(strlen(buf)!=1)
					argc=parse(buf,MAX_SIZE);
	
	


						memset(buf,'\0',MAX_SIZE);
				

			}while(1);


			return 0;
		}

