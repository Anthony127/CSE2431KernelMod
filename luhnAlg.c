#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
			printf("Shutting Down System!\n");
			system("shutdown -P now");
		}
		
	}else{
		printf("The credit card number is not valid\n");
	}
	}else{
		printf("The card number can't be zero\n");
	}
	
}

int main(){
	//int cardArray[16] = {4,0,6,5,4,2,0,7,7,6,8,1,8,4,9,8};//Single Card Example
	//int cardArray[16] = {4,0,6,5,4,2,0,7,7,6,8,1,8,4,9,7};//Bad Card Example
	int cardArray[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//Zeros
	//int cardArray[20] = {1,1,4,0,6,5,4,2,0,7,7,6,8,1,8,4,9,8,1,1};//Card with noise
	int begin = 0;
	int end = 15;
	int r = 0;
	int size = sizeof(cardArray)/sizeof(cardArray[0]);
	//printf("Debug: Array is of size %d\n", size);
	
	while(end < size){
		//printf("Debug: begin %d, end %d\n", begin, end);
		int returnArray[16];
		int i = begin;
		while(i<=end){
			//printf("Debug: r %d, i %d\n",r,i);
			returnArray[r] = cardArray[i];
			//printf("Debug: rArray %d, iArray %d\n",returnArray[r], cardArray[i]);
			r++;
			i++;
		}
		begin++;
		end++;
		r = 0;

		luhn(returnArray);
	}
}

