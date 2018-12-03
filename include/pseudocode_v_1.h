/**@<pseudocode.h>::**/
#pragma once
#include <ctype.h>
#include <stdio.h>

void mklabel(size_t lblindx);
/* Pseudo Control Instructions */
void gofalse(size_t lblindx);
void jump(size_t lblindx);

/* Pseudo move and stack Instructions */
void move(void);
void push(void);
void pop(void); 


/* Pseudo ALU Instructions */
/* Binary Operations */
/* Adition and Subtract */
void iadd(void);
void isub(void);
void fadd(void);
void fsub(void);
void dfadd(void);
void dfsub(void);
void orb(void); /* OR binary*/
/* Multiplication and Division */
void imul(void);
void idiv(void); /* dest / src , rmdr remainder*/
void fmul(void);
void fdiv(void);
void dfmul(void);
void dfdiv(void);
void andb(void);
/* Unary Operations */
void ineg(void);
void fneg(void);
void dfneg(void);
void notb(void); 
