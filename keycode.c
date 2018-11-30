#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** argv){

/*
Translation table for Keycodes to numbers

K == N
2 == 1
3 == 2
4 == 3
5 == 4
6 == 5
7 == 6
8 == 7
9 == 8
10 == 9
11 == 0
*/
	int returnValue;
	printf("The code passed was %s\n", argv[1]);
	
	sscanf(argv[1], "%d", &returnValue); /*Much more reliable than atoi in this situation*/

	printf("The code was converted to %d\n", returnValue);
	
	if((returnValue>1)&&(returnValue<12)){	/*See if this is a Keycode rep of a number*/
		if(returnValue==11){
			returnValue = 0;
			printf("The keycode translates to %d\n", returnValue);
		}else{
			returnValue = returnValue-1; /*Converts the ASCII rep to a number*/
			printf("The keycode translates to the number %d\n", returnValue);
		}
	}else{
		returnValue = 0;
		printf("The keycode is not a number\n");
	}
	
	/*Once we add this to the tail code we'll return the return value*/

	return(0);
}


