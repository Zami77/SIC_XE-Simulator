#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"



symbol *symhead = NULL;
symbol *symcurr = NULL;

struct symbol* createSymbolTable(char* symName,int add)
{
	struct symbol* sym = (struct symbol*)malloc(sizeof(struct symbol));

	if(sym == NULL)
		return NULL;

	sym->address = add;
	sym->symName = malloc(strlen(symName)+1);
	strcpy(sym->symName,symName);

	symhead = sym;
	symcurr = sym;
	return sym;
}

struct symbol* addSymbol(char* symName,int add)
{
	int isSym = isSymbol(symName);
	if(isSym)
		printf("is same");

	if(symhead == NULL)
		return (createSymbolTable(symName,add));
	
	struct symbol *sym = (struct symbol*)malloc(sizeof(struct symbol));

	if(sym == NULL)
		return NULL;
	if(symName == NULL)
		return NULL;

	sym->address = add;
	sym->symName = malloc(strlen(symName)+1);
	strcpy(sym->symName,symName);
	sym->next = NULL;

	symcurr->next = sym;
	symcurr = sym;
	return sym;
}

struct symbol* searchSymbols(char* symName)
{
	struct symbol *ptr = symhead;

	if(symName == NULL)
		return NULL;

	while(ptr != NULL)
	{
		
		if((strcmp(symName,ptr->symName)) == 0)
		{
			printf("\n%s has been found...\n",symName);
			return ptr;
		}
		else
		{
			ptr = ptr->next;
		}
	}

	printf("\nSymbol has not been found...\n");
	return NULL;
			
}

void printSymbolTable(void)
{
	printf("\n----------Symbol Table----------\n");
	struct symbol *curSym = symhead;
	while(curSym != NULL)
	{
		printf("Symbol:%s\tAddress:%x\n",curSym->symName,curSym->address);
		curSym = curSym->next;
	}
	return;
}

void setAddress(struct symbol *sym,int ad)
{
	sym->address = ad;
}

int isSymbol(char* symName)
{
	struct symbol *ptr = symhead;
	//char* str = ptr->symName;

	if(symName == NULL)
		return 0;

	while(ptr != NULL)
	{
		printf("%s vs %s\n",symName,ptr->symName);
		
		if((strcmp(symName,ptr->symName)) == 0)
		{
			printf("\n%s has been found...\n",symName);
			return 1;
		}
		else
		{
			ptr = ptr->next;
		}
	}

	printf("\nSymbol has not been found...\n");
	return 0;
}

