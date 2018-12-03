/**@<pseudocode.h>::**/
#pragma once
#include <ctype.h>
#include <stdio.h>

void mklabel(size_t lblindx);
/* Pseudo Control Instructions */
void gofalse(size_t lblindx);
void jump(size_t lblindx);

/* Pseudo move and stack Instructions */
void move(char *src, char *dest);
void push(char *reg);
void pop(char *reg); 


/* Pseudo ALU Instructions */
/* Binary Operations */
/* Adition and Subtract */
void iadd(char *src, char *dest);
void isub(char *src, char *dest);
void fadd(char *src, char *dest);
void fsub(char *src, char *dest);
void dfadd(char *src, char *dest);
void dfsub(char *src, char *dest);
void orb(char *src, char *dest); /* OR binary*/
/* Multiplication and Division */
void imul(char *src, char *dest);
void idiv(char *src, char *dest, char *rmdr); /* dest / src , rmdr remainder*/
void fmul(char *src, char *dest);
void fdiv(char *src, char *dest);
void dfmul(char *src, char *dest);
void dfdiv(char *src, char *dest);
void andb(char *src, char *dest);
/* Unary Operations */
void ineg(char *dest);
void fneg(char *dest);
void dfneg(char *dest);
void notb(char *dest); 
