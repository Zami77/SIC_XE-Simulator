#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(void)
{
	FILE *progFile,*outputFile,*opcode;
	
	progFile = fopen("input.txt","r");
	opcode = fopen("opcode.txt","r");
	outputFile = fopen("outputFile.txt", "w");
	

	
	//int hexTest = 0x16;
	//hexTest = hexTest << 16;
	//int hexLocTest = 0x1033;
	//unsigned int opcodeTest = hexTest | hexLocTest;
	//printf("Opcode Test:%x",opcodeTest);
	populateOpcode(opcode);
	printf("\n\n-------------------------------------------------\n\n");
	lineByLine(progFile);
	int i = 0;
	for(i = 1; i < lineNum; i++)
	{
		printf("\nLoc:%x\tOp:%.6x",lineLoc[i],lineOp[i]);
	}

	fclose(progFile);
	fclose(outputFile);
	fclose(opcode);
}
