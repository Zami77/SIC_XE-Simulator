#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct opcode {
	int opcodeNum;
	char *code;
	struct opcode *next;
} opcode;

opcode *head = NULL;
opcode *curr = NULL;


struct opcode* createOpcodeList(char* code,int opcodeNum)
{
	printf("Beggining opcode linked list...\n");
	struct opcode *op = (struct opcode*)malloc(sizeof(struct opcode));

	if(NULL == op)
	{
		printf("\nOpcode list creation failure\n");
		return NULL;
	}
	
	//puttint the paramters into the first opcode node
	op->opcodeNum = opcodeNum;
	op->code = malloc(strlen(code)+1);
	strcpy(op->code,code);

	head = op;
	curr = op;
	return op;

}

struct opcode* addOpcode(char* code,int opcodeNum)
{
	printf("\n--Adding Node--\nAD:%s\tOP:%x\n",code,opcodeNum);
	if(head == NULL)
	{
		return (createOpcodeList(code,opcodeNum));
	}

	struct opcode *op = (struct opcode*)malloc(sizeof(struct opcode));

	if(op == NULL)
	{
		printf("\nNode creation fail\n");
		return NULL;
	}

	op->opcodeNum = opcodeNum;
	op->code = malloc(strlen(code)+1);
	strcpy(op->code,code);
	op->next = NULL;

	curr->next = op;
	curr = op;

	return op;
}

struct opcode* searchOpcode(char* code)
{
	struct opcode *ptr = head;

	if(code == NULL)
		return NULL;
	
	printf("\nSearching for %s...\n",code);

	while(ptr != NULL)
	{
		
		if((strcmp(code,ptr->code)) == 0)
		{
			printf("\n%s has been found...\n",code);
			return ptr;
		}
		else
		{
			ptr = ptr->next;
		}
	}

	printf("\nOpcode has not been found...\n");
	return NULL;
			
}

struct opcode* getPrevious(struct opcode* op)
{
	if(op == head)
	{
		return NULL;
	}
	struct opcode* curr = op;
	struct opcode* prev = NULL;

	while(curr != NULL)
	{
		prev = curr;
		curr = curr->next;
	}

	return prev;
}


int deleteOpcode(char* code)
{
	struct opcode *prev = NULL;
	struct opcode *del = NULL;

	del = searchOpcode(code);
	prev = getPrevious(del);
	printf("\n--In Delete Function--\n");

	if(del == NULL)
	{
		return -1;
	}
	else
	{	
		if(prev != NULL)
			prev->next = del->next;
		if(del == curr)
			curr = prev;
		else if(del == head)
		{
			head = del->next;
		}
		
	}
	free(del);
	del = NULL;
	return 0;
}

void printOpcodes(void)
{
	struct opcode *curCode = head;

	printf("\n-----Assembly Directives/Opcodes-----\n");

	while(curCode != NULL)
	{
		printf("AD:%s\tOP:%x\n",curCode->code,curCode->opcodeNum);
		curCode = curCode->next;
	}

	return;
}

int returnOpcode(struct opcode *op)
{
	
	return op->opcodeNum;
}
char* returnCode(struct opcode *op)
{
	return op->code;
}

