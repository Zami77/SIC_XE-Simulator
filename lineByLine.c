#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void lineByLine(FILE*);
void populateOpcode(FILE*);
int isAD(char*);
void symbolAddresses(FILE*);

void lineByLine(FILE *fp)
{
	char str[80];
	const char s[2] = " ";
	char *token;
	lineNum = 1;
	
	struct opcode *op1 = (struct opcode*)malloc(sizeof(struct opcode));
	struct symbol *sym1 = (struct symbol*)malloc(sizeof(struct symbol));

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
	//via the token constant. Retrieves both Mnemonics and Symbols
	while(fgets(str,80,fp) != NULL)
	{
		printf("%d   \t",(lineNum)*5);//Line number multiples of 5
		printf("%x  \t\t",lineLoc[lineNum]);//Location number
		lineLoc[lineNum+1] = lineLoc[lineNum] + 3;//add 3 to every location number
		

		token = strtok(str,s);

		

		op1 = searchOpcode(token);
		sym1 = searchSymbols(token);
		if(op1 != NULL)
		{
			lineOp[lineNum] = (returnOpcode(op1)) << 16;
		}
		
		else if((sym1 == NULL) && (isAD(token) == 0))
		{
			addSymbol(token,0);
		}
		op1 = NULL;
		
		while(token != NULL)
		{
			printf("%s ",token);
			token = strtok(NULL,s);
			op1 = searchOpcode(token);
			sym1 = searchSymbols(token);

			if(op1 != NULL)
			{
				//printf("\n***[AD:%s\tOP:%x\t]***\n",returnCode(op1),returnOpcode(op1));
				lineOp[lineNum] = (returnOpcode(op1)) << 16;
			}
			
			else if((sym1 == NULL) && (isAD(token) == 0))
			{
				addSymbol(token,0);
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

void symbolAddresses(FILE *fp)
{
	char str[80];
	const char s[2] = " ";
	char *token;
	lineNum = 1;
	struct symbol *sym1 = (struct symbol*)malloc(sizeof(struct symbol));

	while(fgets(str,80,fp) != NULL)
	{
		token = strtok(str,s);
		sym1 = searchSymbols(token);
		if(sym1 != NULL)
		{
			setAddress(sym1,lineLoc[lineNum]);
			lineOp[lineNum] = lineOp[lineNum] | lineLoc[lineNum];
		}
		while(token != NULL)
		{
			token = strtok(NULL,s);
			sym1 = searchSymbols(token);
			if(sym1 != NULL)
			{
				setAddress(sym1,lineLoc[lineNum]);
				lineOp[lineNum] = lineOp[lineNum] | lineLoc[lineNum];
			}
		}
		lineNum++;
	}

}

int isAD(char* word)
{
	char *token;
	const char s[2] = " ";
	
	
	token = strtok(assemblyDirectives,s);
	
	if((word == NULL) || (token == NULL))
		return 0;
	if(strcmp(token,word) == 0)
		return 1;

	while(token != NULL)
	{
		token = strtok(NULL,s);

		if(token != NULL)
		{
			if(strcmp(token,word) == 0)
				return 1;
		}
	}
	return 0;
}
