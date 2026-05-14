//function prototypes for compiler interface
int scan(struct token *t);
struct ASTnode *binexpr(int ptp);
int interpretAST(struct ASTnode *n);
struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);

//cg.c
void freeall_registers(void);
int alloc_register(void);
void free_register(int reg);
int cgload(int value);
int cgadd(int r1, int r2);
int cgmul(int r1, int r2);
int cgsub(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
void cgpreamble(void);
void cgpostamble(void);

//gen.c
void generatecode(struct ASTnode *n);