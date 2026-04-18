#include "defs.h"
#include "data.h"
#include "decl.h"

//return the position of character c in string s
//return -1 if c is not in s
static int chrpos(char *s,int c){
    char *p;
    
    p=strchr(s,c);
    return p?p-s:-1;
}

//Put back an unwanted character
static void putback(int c){
    Putback=c;
}

//Get next character from the input file
static int next(void){
    int c;

    if (Putback){  //use the character put
        c=Putback;
        Putback=0;
        return c;
    }

    c=fgetc(Infile); //read character from input file
    if (c=='\n'){
        Line++; //line counter
    }

    return c;
}

//skip past input that need to ignore
//i.e whitespace,newlines
static int skip(void){
    int c;

    c=next();
    while (c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='\f'){
        c=next();
    }

    return c;
}

//scan and return an integer literal
static int scanint(int c){
    int k,val=0;

    //convert each character into int type value
    while((k=chrpos("0123456789",c))>=0){
        val=val*10+k;
        c=next();
    }

    //hit non-integer character,return back
    putback(c);
    return val;
    
}


//scan and return the next token found in the input
//return 1 if the token is reconginzed, 0 if tokens left
int scan(struct token *t){
    int c;

    //skip whitespace
    c=skip();

    //decide which token it is the input character
    switch (c){
        case EOF:
            return 0;
        case '+':
            t->token=T_PLUS;
            break;
        case '-':
            t->token=T_MINUS;
            break;
        case '*':
            t->token=T_STAR;
            break;
        case '/':
            t->token=T_SLASH;
            break;
        default:
            
            //detect integer literal
            if (isdigit(c)){
                t->intvalue=scanint(c);
                t->token=T_INTLIT;
                break;
            }

            //unkown token
            printf("unkown token  %c on the line %d\n",c,Line);
            exit(1);
    }

    return 1; //found a token
}


