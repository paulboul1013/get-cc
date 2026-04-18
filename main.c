#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

//initalize global variables
static void init(){
    Line=1;
    Putback='\n';
}

//print usage message 
static void usage(char *prog){
    fprintf(stderr,"Usage: %s infile\n",prog);
    exit(1);
}

//list of printable tokens
char *tokstr[]={"+","-","*","/","intlit"};

//loop scanning lexeme tokens in the input file
//print each founded token
static void scanfile(){
    struct token T;

    while(scan(&T)){
        printf("Token %s",tokstr[T.token]);
        if (T.token==T_INTLIT){
            printf(",value %d",T.intvalue);
        }
        printf("\n");
    }
}

int main(int argc,char *argv[]) {

    if (argc!=2){
        usage(argv[0]);
    }

    init();

    if ((Infile=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"can't open %s: %s\n",argv[1],strerror(errno));
        exit(1);
    }

    scanfile();
    exit(0);
    
}