#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#define strtok_r strtok

void lineByLine(FILE*);
void populateOpcode(FILE*);
int isAD(char*);
void symbolAddresses(FILE*);

void lineByLine(FILE *fp)
{
	char str[80];
	const char s[2] = " ";
	char *token,*savePtr;
	lineNum = 1;

	
	struct opcode *op1 = (struct opcode*)malloc(sizeof(struct opcode));
	struct symbol *sym1 = (struct symbol*)malloc(sizeof(struct symbol));

	printf("\nLINE\tLOC\t\tSource Statement\t\tObject Code\n");
	printf("----\t---\t\t----------------\t\t-----------\n");
	
	//FIRST LINE--------------------------------------------
	fgets(str,80,fp);
	printf("%d   \t",(lineNum++)*5);
	token = strtok_r(str,s);//PROG NAME
	progName = malloc(sizeof(strlen(token)+1));
	strcpy(progName,token);//Put prog name into global variable

	token = strtok_r(NULL,s);//START Command
	token = strtok_r(NULL,s);//Location start
	sscanf(token,"%x",&startLocation);
	
	//First and Second line both have the same start location
	lineLoc[1] = startLocation;
	lineLoc[2] = startLocation;
	printf("%x  \t\t%s START %x\n",lineLoc[1],progName,lineLoc[1]);
	//END FIRST LINE----------------------------------------

	//loop to cycle through the file and parse every word seperated by a space
	//via the token constant. Retrieves both Mnemonics and Symbols
	while(fgets(str,80,fp) != NULL)
	{
		printf("%d   \t",(lineNum)*5);//Line number multiples of 5
		printf("%x  \t\t",lineLoc[lineNum]);//Location number
		lineLoc[lineNum+1] = lineLoc[lineNum] + 3;//add 3 to every location number
		

		token = strtok_r(str,s);

		

		op1 = searchOpcode(token);
		sym1 = searchSymbols(token);
		if(op1 != NULL)
		{
			printf("\n*** OPCODE WORKING ***\n");
			lineOp[lineNum] = (returnOpcode(op1)) << 16;
		}
		
		else if((sym1 == NULL) && (isAD(token) == 0))
		{
			addSymbol(token,-1);
		}
		op1 = NULL;
		
		while(token != NULL)
		{
			printf("%s ",token);
			token = strtok_r(NULL,s);
			op1 = searchOpcode(token);
			sym1 = searchSymbols(token);

			if(op1 != NULL)
			{
				printf("\n*** OPCODE WORKING ***\n");
				lineOp[lineNum] = (returnOpcode(op1)) << 16;
			}
			
			else if((sym1 == NULL) && (isAD(token) == 0))
			{
				addSymbol(token,-1);
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
		token = strtok_r(str,s);
		//printf("\nAD:%s\t",token);
		code = token;
		token = strtok_r(NULL,s);
		sscanf(token,"%x", &op);
		//printf("OP:%x\n",op);
		
		
		addOpcode(code,op);

	}
}

void symbolAddresses(FILE *fp)
{
	printf("\nSYMBOL ADDRESS IS RUNNING...\n");
	char str[80];
	char firstWord[25] = "";
	lineNum = 1;
	struct symbol *sym1 = (struct symbol*)malloc(sizeof(struct symbol));
	int i = 0,j = 0;

	while(fgets(str,80,fp) != NULL)
	{
		printf("\n%s\n",str);
		while(!(isspace(str[i])))
		{
			firstWord[j++] = str[i++];
		}
		firstWord[j] = '\0';
		printf("first word is %s",firstWord);
		if(strcmp(firstWord,"END") == 0)
		{
			lineNum++;
			return;
		}
		if(isSymbol(firstWord) == 1)
		{
			sym1 = searchSymbols(firstWord);
			setAddress(sym1,lineLoc[lineNum]);
			
		}

		i = 0;
		j = 0;
		lineNum++;
	}
}
void setSymbolAddresses(FILE *fp)
{
	int i = 0,j = 0;
	char str[80] = "";
	char firstWord[25] = "",secondWord[25] = "", thirdWord[25] = "";
	lineNum = 1;
	while(fgets(str,80,fp))
	{
		if(sscanf(str,"%24s %24s %24s",firstWord,secondWord,thirdWord) == 2)
			thirdWord[0] = '/0';
		printf("First Word:%s Second Word:%s Third Word:%s\n",firstWord,secondWord,thirdWord);
		if(getAddress(secondWord)>0)
		{
			printf("%s is a symbol\n",secondWord);
			lineOp[lineNum] = lineOp[lineNum] | getAddress(secondWord);
		}
		if(getAddress(thirdWord)>0)
		{
			printf("%s is a symbol\n",thirdWord);
			lineOp[lineNum] = lineOp[lineNum] | getAddress(thirdWord);
		}
		if((thirdWord[0] == 'C') && (thirdWord[1] == 39))
			lineOp[lineNum] = thirdWord[2] << 16;

		
		printf("\nLINE %d\n",lineNum);
		lineNum++;
		

	}
}

int isAD(char* word)
{
	char *token;
	const char s[2] = " ";
	
	
	token = strtok_r(assemblyDirectives,s);
	
	if((word == NULL) || (token == NULL))
		return 0;
	if(strcmp(token,word) == 0)
		return 1;

	while(token != NULL)
	{
		token = strtok_r(NULL,s);

		if(token != NULL)
		{
			if(strcmp(token,word) == 0)
				return 1;
		}
	}
	return 0;
}

void writeObjFile(FILE *input,FILE *output)
{
	fprintf(output,"%s\n",progName);
	int i = 0;
	for(i = 1; i < lineNum; i++)
	{
		fprintf(output,"%06x\n",lineOp[i]);
	}
	fprintf(output,"END");
}
