#include "defs.h"
#include "data.h"
#include "decl.h"

//operator precedence for each token
static int OpPrec[] = {0,10,10,20,20, 0};
//                     EOF + - * /   INTLIT

//check that have a binary operator and return its precedence
static int op_precedence(int tokentype){
    int prec=OpPrec[tokentype];
    if (prec==0){
        fprintf(stderr,"syntax error on line %d, token %d\n",Line,tokentype);
        exit(1);
    }
    return prec;
}

//convert a token into an AST operation
static int arithop(int tok){
    switch (tok){
        case T_PLUS:
            return A_ADD;
        case T_MINUS:
            return A_SUBTRACT;
        case T_STAR:
            return A_MULTIPLY;
        case T_SLASH:
            return A_DIVIDE;
        default:
            fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
            exit(1);
    }
}

//parse a primary factor and return an AST node representing it
static struct ASTnode *primary(void){
    struct ASTnode *n;

    //for an INTLIT token, make a leaf AST node for it
    switch (Token.token){
        case T_INTLIT:
            n = mkastleaf(A_INTLIT, Token.intvalue);
            scan(&Token);
            return n;
        default:
            fprintf(stderr, "syntax error on line %d\n", Line);
            exit(1);
    }
}

//return an AST tree whose root is a binary operator
struct ASTnode *binexpr(int ptp){
    struct ASTnode *n, *left, *right;
    int tokentype;

    //get the integer literal on the left
    //fetch the next token at the same time
    left = primary();

    //if no tokens left, return just the left node
    tokentype=Token.token;
    if (tokentype == T_EOF){
        return left;
    }

    //while the precedence of this token is 
    //more than that of the previous token precedence
    while (op_precedence(tokentype) > ptp) {
        //fetch in the next integer literal
        scan(&Token);

        //recursively call binexpr() with the 
        //precedence of our token to build a sub-tree
        right=binexpr(OpPrec[tokentype]);

        //join that sub-tree with ours, convert the token
        //into an AST operation at the same time
        left=mkastnode(arithop(tokentype),left,right,0);

        //update the details of the current token
        //if no tokens left, return just the left node
        tokentype=Token.token;
        if (tokentype==T_EOF) {
            return left;
        }
    }

    return left;
}

struct ASTnode *multiplicative_expr(void) {
    struct ASTnode *left,*right;
    int tokentype;

    //get integer literal on the left
    //fetch next token at the same time
    left=primary();

    //if no tokens left,return the left node
    tokentype=Token.token;
    if (tokentype==T_EOF) {
        return left;
    }

    //loop working on token at our level of precedence
    while (1) {
        //fetch in the next integer literal
        scan(&Token);

        //get the right sub-tree at a higher precedence than us
        right=multiplicative_expr();

        //join the two sub-trees with our low-precedence operator
        left = mkastnode(arithop(tokentype),left,right,0);

        //and get the next token at our precedence
        tokentype=Token.token;
        if (tokentype==T_EOF) {
            break;
        }
    }

    return left;
}

//Return an AST tree whose root is a '+' or '-' binary operator
struct ASTnode *additive_expr(void) {
    struct ASTnode *left,*right;
    int tokentype;
    
    //get the left sub-tree at a higher precedence than us
    left=multiplicative_expr();

    //if no tokens left ,return just the left node
    tokentype=Token.token;
    if (tokentype==T_EOF) {
        return left;
    }

    
    //loop working on token at level of precedence
    while (1) {
        //fetch in the next integer literal 
        scan(&Token);

        //get the right sub-tree at a higher precedence than us
        right=multiplicative_expr();
        
        //join the two sub-trees with our low-precedence operator
        left=mkastnode(arithop(tokentype),left,right,0);

        //and get the next token at our precedence
        tokentype = tokentype;
        if (tokentype==T_EOF) {
            break;
        }
    }

    return left;

}