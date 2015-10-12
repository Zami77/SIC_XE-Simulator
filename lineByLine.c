#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void lineByLine(FILE*);
void populateOpcode(FILE*);

void lineByLine(FILE *fp)
{
	char str[80];
	const char s[2] = " ";
	char *token;
	
	struct opcode *op1 = (struct opcode*)malloc(sizeof(struct opcode));

	printf("\nLINE\tLOC\t\tSource Statement\t\tObject Code\n");
	printf("----\t---\t\t----------------\t\t-----------\n");
	
	//FIRST LINE--------------------------------------------
	fgets(str,80,fp);
	printf("%d   \t",(lineNum++)*5);
	token = strtok(str,s);//PROG NAME
	progName = malloc(sizeof(strlen(token)+1));
	strcpy(progName,token);//Put prog name into global variable

	token = strtok(NULL,s);//START Command
	token = strtok(NULL,s);//Location start
	sscanf(token,"%x",&startLocation);
	
	//First and Second line both have the same start location
	lineLoc[1] = startLocation;
	lineLoc[2] = startLocation;
	printf("%x  \t\t%s START %x\n",lineLoc[1],progName,lineLoc[1]);
	//END FIRST LINE----------------------------------------

	//loop to cycle through the file and parse every word seperated by a space
	//via the token constant
	while(fgets(str,80,fp) != NULL)
	{
		printf("%d   \t",(lineNum)*5);//Line number multiples of 5
		printf("%x  \t\t",lineLoc[lineNum]);//Location number
		lineLoc[lineNum+1] = lineLoc[lineNum] + 3;//add 3 to every location number
		

		token = strtok(str,s);

		op1 = searchOpcode(token);
		if(op1 != NULL)
		{
			lineOp[lineNum] = (returnOpcode(op1)) << 16;
		}
		op1 = NULL;
		
		while(token != NULL)
		{
			printf("%s ",token);
			token = strtok(NULL,s);
			op1 = searchOpcode(token);

			if(op1 != NULL)
			{
				printf("\n***[AD:%s\tOP:%x\t]***\n",returnCode(op1),returnOpcode(op1));
				lineOp[lineNum] = (returnOpcode(op1)) << 16;
			}
		}
		
		lineNum++;
	}
}

void populateOpcode(FILE *fp)
{
	char str[80];
	char *code;
	const char s[2] = " ";
	int op;
	char *token;

	while(fgets(str,80,fp) != NULL)
	{
		token = strtok(str,s);
		//printf("\nAD:%s\t",token);
		code = token;
		token = strtok(NULL,s);
		sscanf(token,"%x", &op);
		//printf("OP:%x\n",op);
		
		
		addOpcode(code,op);

	}
}
