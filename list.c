	
	//list.c
	// a simple implementatio of the ls command
	// directories are printed in yellow
	//regular files in blue
	//add new colors for file types by using colors
	//macros and a filetype check

	#include "headers.h"

	int list(){

		DIR *d;
		struct dirent *dir;
		int file=0;
		struct stat fileStat;
		//list the file in the current directory takes no argument

		d=opendir(".");

		if(d)
		{
			while((dir=readdir(d))!=NULL){

				//open file in read only permisiion so command
				// works across various acess rights

				if((file=open(dir->d_name,O_RDONLY)) < -1)
				return 1;

				if(fstat(file,&fileStat) < 0)
				return 1;


				printf(" | ");
				//check if it is directory
				if(S_ISDIR(fileStat.st_mode)){
				PRINT_YELLOW(dir->d_name);
				}
				else
				{
				PRINT_BLUE(dir->d_name);
				}
				printf("\n");
				printf("Size: %d bytes   ",fileStat.st_size);
				printf("Inode: %d ",fileStat.st_ino);
				printf("Permissions:");
				printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-" );
				printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-" );
				printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-" );
			//only print user FIle stats uncomment for other permissions
				/*
				printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-" );
				printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-" );
				printf( (fileStat.st_mode & S_IROTH) ? "r" : "-" );
				printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-" );
				printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-" );
				*/



				printf("\n");

			}

			closedir(d);
		}

		printf("\n");
		return 0;

	}
