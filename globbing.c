	//globbing.c

	char * glob_pattern(char * wildcard){

	  char * gfilename;
	  size_t cnt,length;
	//glob_t is a glob structure type defined in glob.h
	  glob_t glob_results;
	  char **p;
	//gl_pathV is a list of all matched pathnames
	//gl_pathc is the total count of paths mathched
	  glob(wildcard,GLOB_NOCHECK,0,&glob_results);
	//if GLOB_NOCHECK is used the structure returns
	//wildcard if no matches are found and
	//path count is set to 1
	  for(p=glob_results.gl_pathv,cnt=glob_results.gl_pathc;cnt;p++,cnt--)
	  length += strlen(*p)+ 1;

	  gfilename=(char *) calloc(length,sizeof(char));
	  for(p=glob_results.gl_pathv,cnt=glob_results.gl_pathc;cnt;p++,cnt--)
	  {

	    strcat(gfilename,*p);
	    if(cnt > 1)
	    strcat(gfilename," ");
	  }

	  globfree(&glob_results);
	  return gfilename;

	}

	int glob_parser(char input[]){


	  char * cp;
		char c;
		char word[1024];
		int i=0,j=0;
	  char * results;
		char wild[20];

	//three state parser for seperating normal keywords from wildcards
	//wildcards in this parser are assumed to start with
	// '*' and '[' and ending with a space
	// Example *.c *.mp* or *
	// or [a-z].c or [1-9].*


	  enum states { START, IN_WORD, IN_WILD } state = START;

		for (cp = input; *cp != '\0'; cp++) {
		    c = (unsigned char) *cp;
		        switch (state) {
		            case START:

	      	    	          if(c=='*' || c=='['){
			    	        	state=IN_WILD;
		            			wild[j]=c;
		            			j++;
		            	  	}
		            		else{

		            			state=IN_WORD;
		            			word[i]=c;
		            			i++;
		            		}
		           	continue;

		             case IN_WORD:
		             	if(c =='*' || c=='['){
		             		state=IN_WILD;
					 wild[j]=c;
		             		j++;
		             	}
		             else{
		             		word[i]=c;
		             		i++;
		             	}
		             		continue;

		             case IN_WILD:
		              	if(c==' '){
		              			state=START;
		              			word[i]=c;
		              	}
		             	 else{
		              			wild[j]=c;
		              			j++;

		              		}

		               }
		       }


		word[i]='\0';
		wild[j]='\0';



	/*
	  for(cp=word;*cp!='\0';cp++){

	    printf("|%c|",*cp);
	  }

	  printf("\n\n");

	  for(cp=wild;*cp!='\0';cp++){
	    printf("|%c|",*cp);
	  }
	*/

	//removing the trailing newline from array  
	  strtok(wild,"\n");
	  results=glob_pattern(wild);
	  strcat(word," ");
	  strcat(word,results);


	  parse(word,1024);

	  return 0;
	}
