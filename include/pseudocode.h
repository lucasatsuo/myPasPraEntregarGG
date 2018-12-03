/**@<pseudocode.h>::**/
#pragma once
#include <ctype.h>
#include <stdio.h>

/* Parser to pseudocode interface*/
void store(void);
void recall(void);
int macrounary(void);
int macrobinary(void);
void mklabel(size_t lblindx);
void mklooplabel(size_t lblindx);
void gofalse(size_t lblindx);
void jump(size_t lblindx);
void push(int regtype);
void pop(int regtype); 
/* Pseudo ALU Instructions */
/* Binary Operations */
void move(void);
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
void cvltofacc(void);
void cvltofstk(void);
/* Unary Operations */
void ineg(void);
void fneg(void);
void dfneg(void);
void notb(void); 
