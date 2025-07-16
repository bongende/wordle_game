/*We have a wordle.txt file */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ResultGreen	1
#define ResultYellow	2
#define ResultRed	4 // why 4 instead of 3

int main(int, char **);


struct s_word 
{
	char **arr;
	int n;
};

typedef char Result;
typedef struct s_word Words;


bool isin(char, char*);
Result cc(char, int, char *);
Result* cw(char *, char *);
void Example_print_result(Result *);
Words readfile(char *, int);


// check if a character is in correct place and assign a color wheither yes or no

bool isin(char c, char *str) 
{
	bool ret;
	ret = false;

	int size = strlen(str);

	for (int i=0;i<size; ++i) 
		ret = ret || (c == str[i]);
		
	return ret;
}


Result cc(char guess, int idx, char *word) 
{

	char correct = word[idx];

	if (guess == correct) return ResultGreen;
	else if (isin(guess, word))	return ResultYellow;
	return ResultRed;
}


Result* cw( char * guess, char * word) 
{

	static Result res[5];

	for (int i = 0; i < 5; ++i )
		res[i] = cc(guess[i], i, word);

	return res;
}


void Example_print_result(Result* res) 
{

	int i;

	for (i=0; i<5; ++i) 
	{
		switch (res[i] ) 
		{
			case ResultGreen :
				printf("%s\n", "Green");
				break;
			case ResultYellow :
				printf("%s\n", "Yellow");
				break;
			case ResultRed : 
				printf("%s\n", "Red");
				break;
			default :
				printf("Unknown: %d\n",res[i]);
				break;
		}
	}
}


Words readfile(char *filename, int max) 
{
	char buf[8];
	int i, size;
	FILE *fd;

	char **ret;
	//Words words;


	fd = fopen(filename, "r");
	if (!fd)
	{
		perror("fopen");
		Words words = 
		{
			.arr = (char **)0,
			.n = 0
		}; 

		return words;
	}

	size = max * 5;

	ret = (char **)malloc(size);
	
	if (!ret) 
	{
		fclose(fd);
		perror("malloc");
		Words words = 
		{
			.arr = (char **)0, 
			.n = 0
		}; 

		return words;
	}

	i = 0;
	memset(buf, 0, 8);

	while (fgets(buf, 7, fd)) 
	{
		size = strlen(buf);

		if (size < 1) 
		{
			memset(buf, 0, 8);
			continue;
		}

		--size;
		buf[size] = 0;

		if (size != 5) 
		{
			memset(buf, 0, 8);
			continue;
		}

		ret[i][0] = buf[0];
		ret[i][1] = buf[1];
		ret[i][2] = buf[2];
		ret[i][3] = buf[3];
		ret[i][4] = buf[4];

		memset(buf, 0, 8);
		++i; // not declared yet;

		if (max < i) 
			break;

	}

	fclose(fd);

	Words words = 
	{
		.arr = ret,
		.n = i
	};
	
	return words;
}


int main(int argc, char *argv[]) 
{

	char *correct, *guess;
	Result* res;


	if (argc < 3) 
	{
	
		fprintf(stderr, "Usage: %s CORRECT GUESSWORLD\n", argv[0]);

		return -1;
	}

	correct = argv[1];
	guess = argv[2];

	res = cw(guess, correct);

	Example_print_result(res);

	return 0;
}



















