#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 
void main() 
{ 
	FILE* logFile;
	logFile = fopen("/var/log/syslog", "r");
	if(logFile == NULL)
	{
		perror("error");
	}
	int n = 500;
    int count = 0;  // To count '\n' characters 
  
    unsigned long long pos; 
    char str[200]; 
  
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
  
        // print last n lines 
        //printf("Printing last %d lines -\n", n); 
        while (fgets(str, sizeof(str), logFile)){
   				const char s[2] = "]";
				const char s2[2] = " ";
   				char *token;
				char *token2;
   
   				/* get the first token */
   				token = strtok(str, s);
				//Skip first token, and read the next one which holds the keycode
				token = strtok(NULL,s);
				//Remove leading space
				token2 = strtok(token, s2);

   
   				/* walk through other tokens */
   				/*while( token != NULL ) {
      			printf( " %s\n", token );
    
      			token = strtok(NULL, s);
   				} */
			if(token2 != NULL){
            	printf("%s\n", token2);
			}
		} 
    } 
    printf("\n\n"); 
}
