	//display.c
	#include "headers.h"

	void welcome(){

	printf("\n\n");
	PRINT_CYAN("\n\t████████████████████████████████████████████████████████████");
	PRINT_CYAN("\n\t████████████████████████████████████████████████████████████");
	PRINT_CYAN("\n\t█                                                          █");
	PRINT_CYAN("\n\t█      ▁ ▂ ▄ ▅ ▆ ▇ █  Zeus  Shell   █ ▇ ▆ ▅ ▄ ▂ ▁          █");
	PRINT_CYAN("\n\t█                                                          █");
	PRINT_CYAN("\n\t█            A Free and Opensource   Shell                 █");
	PRINT_CYAN("\n\t████████████████████████████████████████████████████████████");
	printf("\n\n\n");
	}

	void print_prompt(){


		extern int color_scheme;

		switch(color_scheme)
		{

				case 0:
				PRINT_YELLOW("[");
				PRINT_RED(getenv("USER"));
				PRINT_YELLOW("]");
				PRINT_BLUE(getenv("PWD"));
				PRINT_MAGENTA(">");
				break;


				case 1:
				PRINT_GREEN("[");
				PRINT_YELLOW(getenv("USER"));
				PRINT_GREEN("]");
				PRINT_CYAN(getenv("PWD"));
				PRINT_RED(">");
				break;

				case 2:
				PRINT_MAGENTA("[");
				PRINT_YELLOW(getenv("USER"));
				PRINT_MAGENTA("]");
				PRINT_GREEN(getenv("PWD"));
				PRINT_BLUE(">");
				break;



		}


	}
