/**@parser.h::**/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <mytype.h>
#include <keywords.h>
#include <tokens.h>
#include <interface.h>
#include <pseudocode.h>
#include <symtab.h>

// size_t loopcount = 1;
#define loopalloc loopcount++
extern FILE *source;
extern char lexeme[MAXIDLEN + 1];
extern SYMTABMODEL symtab[MAXSYMTBENTRIES];

int iscompatop(int, int);
void mypas(void);
void header(void); 
void body(void);
void procmodel(void);
void funcmodel(void);
void varmodel(void);
void vargroup(void);
void varlist(void);
int pretype(void);
void procmodel(void);
void funcmodel(void);
void formalparms(void);
void arglist(void);
void argmodel(void);
void body(void);
void stmtlist(void);
void stmt(void);
void ifstmt(void);
int expr(void);
int smpexpr(int);
int factor(int);
void exprlist(void);
void whlstmt(void);
void repstmt(void);

