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

int sameSymbol(struct symbol *sym1,struct symbol *sym2)
{
	if((strcmp(sym1->symName,sym2->symName)==0) && (sym1->address == sym2->address))
		return 1;
	return 0;
}

struct symbol* getPrev(struct symbol *sym)
{
	if(sameSymbol(sym,symhead))
		return NULL;
	if(sameSymbol(sym,symhead->next))
		return symhead;
	struct symbol *tmpSym = symhead;
	while(tmpSym != NULL)
	{
		if(sameSymbol(sym,tmpSym))
			return tmpSym;
		tmpSym = tmpSym->next;
	}
		return NULL;
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

void deleteSymbol(char* symName)
{
	struct symbol *sym1 = searchSymbols(symName);
	if (sym1 == NULL)
		return;
	struct symbol *tempNext = sym1->next;

	if(sameSymbol(sym1,symhead))
	{
		symhead = tempNext;
		return;
		
	}
	else
	{
		struct symbol *sym1Prev = getPrev(sym1);
		sym1Prev->next = tempNext;
		free(sym1);
		sym1 = NULL;
	}

	return;
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
			//printf("\n%s has been found...\n",symName);
			return ptr;
		}
		else
		{
			ptr = ptr->next;
		}
	}

	//printf("\nSymbol has not been found...\n");
	return NULL;
			
}

void printSymbolTable(void)
{
	printf("\n----------Symbol Table----------\n");
	struct symbol *curSym = symhead;
	while(curSym != NULL)
	{
		if(curSym->address >= 0)
			printf("Symbol:%s\tAddress:%x\n",curSym->symName,curSym->address);
		curSym = curSym->next;
	}
	return;
}

void clearFakeSymbols()
{
	struct symbol *currSym = symhead;
	while(currSym != NULL)
	{
		if(currSym->address < 0)
			deleteSymbol(currSym->symName);
		currSym = currSym->next;
	}
}

void setAddress(struct symbol *sym,int ad)
{
	sym->address = ad;
}

int getAddress(char* symName)
{
	struct symbol *cursym2 = symhead;
	if(symName == NULL)
		return -1;
	while(cursym2 != NULL)
	{
		if((strcmp(symName,cursym2->symName) == 0))
		{
			return cursym2->address;
		}
		else
		{
			cursym2 = cursym2->next;
		}
		
	}
	return -1;
}

int isSymbol(char* symName)
{
	struct symbol *ptr = symhead;
	//char* str = ptr->symName;

	if(symName == NULL)
		return 0;

	while(ptr != NULL)
	{
		//printf("%s vs %s\n",symName,ptr->symName);
		
		if((strcmp(symName,ptr->symName) == 0))
		{
			//printf("\n%s has been found...\n",symName);
			return 1;
		}
		else
		{
			ptr = ptr->next;
		}
	}

	//printf("\nSymbol has not been found...\n");
	return 0;
}

