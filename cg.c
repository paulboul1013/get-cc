#include "defs.h"
#include "data.h"
#include "decl.h"
static char *reglist[4]={"%r8","%r9","%r10","%r11"};



int cgload(int value) {
    //get a new register
    int r=alloc_register();

    //print the code to init
    fprintf(Outfile,"\tmovq\t$%d, %s\n",value,reglist[r]);
    return r;
}

//add two registers together and return the number of the register with the result
int cgadd(int r1,int r2) {
    fprintf(Outfile,"\taddq\t%s, %s\n",reglist[r1],reglist[r2]);
    free_register(r1);
    return r2;
}


//multiply two registers together and return 
// the number of the register with the result
int cgmul(int r1,int r2) {
    fprintf(Outfile,"\timulq\t%s, %s\n",reglist[r1],reglist[r2]);
    free_register(r1);
    return r2;
}

//subtract the second register from the first and
//return the number of the register with the result
int cgsub(int r1,int r2) {
    fprintf(Outfile,"\tsubq\t%s, %s\n",reglist[r2],reglist[r1]);
    free_register(r2);
    return r1;
}

//divide the first register by the second and
//return the number of the register with the result
int cgdiv(int r1,int r2) {
    fprintf(Outfile,"\tmovq\t%s,%%rax\n",reglist[r1]);
    fprintf(Outfile,"\tcqo\n"); //  sign-extend RAX into RDX:RAX
    fprintf(Outfile,"\tidivq\t%s\n",reglist[r2]);
    fprintf(Outfile,"\tmovq\t%%rax,%s\n",reglist[r1]);
    free_register(r2);
    return r1;
}

void cgprintint(int r){
    fprintf(Outfile,"\tmovq\t%s, %%rdi\n",reglist[r]);
    fprintf(Outfile,"\tcall\tprintint\n");
    free_register(r);
}
