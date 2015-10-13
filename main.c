#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(void)
{
	FILE *progFile,*outputFile,*opcode,*ADFile;
	
	progFile = fopen("input.txt","r");
	opcode = fopen("opcode.txt","r");
	outputFile = fopen("obj.o", "w");
	ADFile = fopen("AssemblyDirectives.txt","r");
	
	fgets(assemblyDirectives,30,ADFile);

	
	//int hexTest = 0x16;
	//hexTest = hexTest << 16;
	//int hexLocTest = 0x1033;
	//unsigned int opcodeTest = hexTest | hexLocTest;
	//printf("Opcode Test:%x",opcodeTest);
	populateOpcode(opcode);
	//printf("\n\n-------------------------------------------------\n\n");
	lineByLine(progFile);
	//addSymbol("A",0x1003);
	//addSymbol("B",0x1006);
	//int isSym = isSymbol("A");
	//if(isSym)
		//printf("This should print out\n");
	symbolAddresses(progFile);
	printSymbolTable();
	fclose(progFile);
	fclose(outputFile);
	fclose(opcode);
}
