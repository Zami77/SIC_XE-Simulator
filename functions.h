void lineByLine(FILE *fp);
void populateOpcode(FILE*);

typedef struct opcode {
	int opcode;
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


int lineLoc[1000];
int lineOp[1000];
int lineNum;
int startLocation;
char *progName;
