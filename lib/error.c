#include "../include/fonction.h"

void Error(int err) {
	switch(err) {
		case 1: printf("Pointer NULL\n");
			break;
		/*case 2: printf("Pointer NULL\n");
			break;*/
		case 3: printf("There is a stat on 0\n");
			break;
		/*case 1: printf("Pointer NULL\n");
			break;
		case 1: printf("Pointer NULL\n");
			break;*/
		case 10: printf("The choice is out of bound\n");
			break;
		default: printf("Unknown error\n");
	}

	exit(err);
}