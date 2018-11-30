#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int keycodeToInt (char* keycode){

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
	printf("The code passed was %s\n", keycode);
	
	sscanf(keycode, "%d", &returnValue); /*Much more reliable than atoi in this situation*/

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
		if(returnValue == 14){
			//BackSpace, back up the array by returning -2
			returnValue = -2;
			printf("Backspace\n");
		}else{
		returnValue = -1;
		printf("The keycode is not a number\n");
		}
	}
	

	return(returnValue);
} 

int luhn(int *cardArray){

	long long int cardNum = 0;
	int j = 0;
	while(j<16){
		//printf("Debug: cardNum %lli\n", cardNum);
		cardNum = cardNum * 10;
		cardNum += (long long int)cardArray[j];
		//printf("Debug: cardNum %lli, cardArray %d\n", cardNum, cardArray[j]);
		j++;
	}
	printf("The card number is: %lli\n", cardNum);
	if(cardNum>0){
	
	/*Size will be 16 or standard credit cards*/
	int i = 0; //Iterating varible

	/*Step 1: Double every other number starting with the first number*/
	while(i<16){
		int holder = cardArray[i];
		holder = holder * 2;
		cardArray[i] = holder;
		i = i + 2;
	}

	i = 0; //Reset itterator
	
	/*Step 2: If a number has 2 digits, add them together*/
	while(i<16){
		int base = 1; //No number is greater than 20 so base addition is 1
		int holder2 = cardArray[i];
		if(holder2>=10){
			int base2 = holder2-10;
			cardArray[i] = base + base2;
		}
		i++;
	}

	i = 0; //Reset itterator

	/*Step 3: Sum all elements in the array*/
	int sum = 0;
	while(i<16){
		sum+=cardArray[i];
		i++;
	}

	/*Step 4: Perform a mod 10 check, all valid credit card numbers will have a mod 10 of 0*/
	if(cardNum != 0){
	if(sum%10 == 0){
		printf("The credit card number is valid\n");
		char string[4];
		printf("Did you enter this number on purpose, yes or no?\n");
		scanf("%s",string);
		if(strcmp("yes",string) != 0){
			printf("Would you like to shutdown yes or no?\n");
			scanf("%s",string);
			if(strcmp("no",string) !=0){
				printf("Shutting Down System!\n");
				system("shutdown -P now");
			}
		}
		
	}else{
		printf("The credit card number is not valid\n");
	}
	}else{
		printf("The card number can't be zero\n");
	}
	}else{
		printf("Card Number cannot be negative, and was skipped\n");
	}
	
}

void main() 
{ 
while(1){
	FILE* logFile;
	logFile = fopen("/var/log/syslog", "r");
	if(logFile == NULL)
	{
		perror("error");
	}
	int n = 100;
    int count = 0;  // To count '\n' characters 

    unsigned long long pos; 
    char str[200]; 
    int possibleCards[100]; //Array of digits tht can form possible card numbers
  
    // Go to End of file 
    if (fseek(logFile, 0, SEEK_END)) 
        perror("fseek() failed"); 
    else
    { 
        // pos will contain no. of chars in 
        // input file. 
        pos = ftell(logFile); 
  
        // search for '\n' characters 
        while (pos) 
        { 
            // Move 'pos' away from end of file. 
            if (!fseek(logFile, --pos, SEEK_SET)) 
            { 
                if (fgetc(logFile) == '\n') 
  
                    // stop reading when n newlines 
                    // is found 
                    if (count++ == n) 
                        break; 
            } 
            else
                perror("fseek() failed"); 
        } 
  
	// Debug statment
        // print last n lines 
        //printf("Printing last %d lines -\n", n); 
	    
	int i = 0; //Pointer for possible cards array pos
        while (fgets(str, sizeof(str), logFile)){
   				const char s[2] = "]";
				const char s2[2] = " ";
   				char *token;
				char *token2;
				int codeNum;
   
   				/* get the first token */
   				token = strtok(str, s);
				//Skip first token, and read the next one which holds the keycode
				token = strtok(NULL,s);
				//Remove leading space
				token2 = strtok(token, s2);

			if(token2 != NULL){
				printf("-----------------------------\n");
            			printf("The Token was %s\n", token2);
				codeNum = keycodeToInt(token2);
				printf("CodeNum = %d\n", codeNum);
				if(codeNum == -2){
					//Backspace, back up array position
					if(i != 0){
						i--;
					}
				}else if(codeNum>-1){
					//write the number
					possibleCards[i] = codeNum;
					i++;
				}else{
					//write -1 for invalid values to hold space
					possibleCards[i] = codeNum;
					i++;
				}
			}
		} 
    } 
    printf("\n\n"); 

	int begin = 0;
	int end = 15;
	int r = 0;
	int size = sizeof(possibleCards)/sizeof(possibleCards[0]);
	//printf("Debug: Array is of size %d\n", size);
	
	while(end < size){
		//printf("Debug: begin %d, end %d\n", begin, end);
		int returnArray[16];
		int i = begin;
		while(i<=end){
			//printf("Debug: r %d, i %d\n",r,i);
			returnArray[r] = possibleCards[i];
			//printf("Debug: rArray %d, iArray %d\n",returnArray[r], cardArray[i]);
			r++;
			i++;
		}
		begin++;
		end++;
		r = 0;

		luhn(returnArray);
	}
sleep(15);//Repeat function every 15 seconds until user provides ctrl+c in terminal, or computer shuts down.
}
}
