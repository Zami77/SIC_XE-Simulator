void lineByLine(FILE *fp);
void populateOpcode(FILE*);
int isAD(char* word);
void symbolAddresses(FILE *fp);

typedef struct opcode {
	int opcodeNum;
	char *code;
	struct opcode *next;
} opcode;

struct opcode* createOpcodeList(char* code,int opcode);
struct opcode* addOpcode(char* code,int opcode);
struct opcode* searchOpcode(char* code);
int deleteOpcode(char* code);
void printOpcodes(void);
int returnOpcode(struct opcode *op);
char* returnCode(struct opcode *op);

typedef struct symbol{
	char *symName;
	int address;
	struct symbol *next;
}symbol;

struct symbol* createSymbolTable(char* symName,int add);
struct symbol* addSymbol(char* symName,int add);
struct symbol* searchSymbols(char* symName);
void printSymbolTable(void);
int isSymbol(char* symName);
void setAddress(struct symbol *sym,int ad);


int lineLoc[1000];
int lineOp[1000];
int lineNum;
int startLocation;
char *progName;
char assemblyDirectives[30];
