#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	
	lineByLine(progFile);
	
	rewind(progFile);
	symbolAddresses(progFile);
	

	printSymbolTable();

	rewind(progFile);
	setSymbolAddresses(progFile);
	

	lineOp[lineNum-1] = 0;//End of the file has a 0 opcode
	rewind(progFile);
	writeObjFile(progFile,outputFile);
	fclose(progFile);
	fclose(outputFile);
	fclose(opcode);
}
