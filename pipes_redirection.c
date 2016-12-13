//pipes_redirection.c
#include "headers.h"

int pipes_(char * a[],char * b[]){

	int fd_A[2];
	int status;
	int i;

	pipe(fd_A);
	pid_t pid_a,pid_b;

	if(!(pid_a=fork())){
		close(1);
		dup(fd_A[WRITE_END]);

		close(fd_A[0]);
		close(fd_A[1]);

		execvp(a[0],a);

	}
	else
	{

		//wait for the first command to end
		wait(&status);
		if(!(pid_b=fork()))
		{
			close(0);
			dup(fd_A[READ_END]);
			//the second process
			close(fd_A[0]);
			close(fd_A[1]);
			execvp(b[0],b);

		}



		close(fd_A[WRITE_END]);
		close(fd_A[READ_END]);
	}


	wait(&status);
	//wait for 2nd process to end
	return 0;
}

int redirection_(char * a[],char type_red[],char * b[]){

	int err = -1;
	int fileDescriptor;
	int option=0;

	pid_t pid;

	if(strcmp(type_red,">")==0)   option=0;
	if(strcmp(type_red,"<")==0)   option=1;
	if(strcmp(type_red,">>")==0)  option=2;



	if((pid=fork())==-1){
		printf("Child process could not be created\n");
		return;
	}
	if(pid==0){

		if (option == 0){



			fileDescriptor = open(b[0], O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);



		}else if (option == 1){

			fileDescriptor = open(b[0], O_RDONLY, 0600);
			dup2(fileDescriptor, STDIN_FILENO);
			close(fileDescriptor);

		}else if(option ==2){

			fileDescriptor = open(b[0], O_CREAT | O_WRONLY | O_APPEND, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);
		}



		if (execvp(a[0],a)==err){
			printf("err");
			kill(getpid(),SIGTERM);
		}
	}
	waitpid(pid,NULL,0);



	return 0;
}

int pipes_redirection(char * argv[],int argc){


	char * command1[10];
	char * command2[10];
	int pipe_count=0;
	int i;
	int temp_count1,temp_count2;
	int flag_pipe,flag_redirection;
	temp_count1=0;
	temp_count2=0;
	char type_red[3];
	memset(command1,0,sizeof(command1));
	memset(command2,0,sizeof(command2));


	for (i = 0; i < argc; i++)
	{


		if(strchr(argv[i],'<')!=NULL || strchr(argv[i],'|')!=NULL || strchr(argv[i],'>')!=NULL){
			pipe_count=pipe_count+1;
			if(  strchr(argv[i],'<')!=NULL || strchr(argv[i],'>')!=NULL  ){
				flag_redirection=1;
				strcpy(type_red,argv[i]);
			}
			if(strcmp(argv[i],"|")==0)
			flag_pipe=1;

			continue;
		}



		if(pipe_count==0){

			command1[temp_count1]=(char *)malloc(sizeof(char)*(strlen(argv[i])+1));
			command1[temp_count1]=argv[i];
			temp_count1++;

		}
		if(pipe_count==1){


			command2[temp_count2]=(char *)malloc(sizeof(char)*(strlen(argv[i])+1));
			command2[temp_count2]=argv[i];
			temp_count2++;

		}




	}

	if(flag_pipe==1 && flag_redirection==1){
		printf("This is a basic shell nesting of pipes and redirection not allowed\n");
		return -1;
	}

	if(flag_pipe==1)
	pipes_(command1,command2);

	if(flag_redirection==1)
	redirection_(command1,type_red,command2);

	return 0;

}
