/**@<mypas.c>::**/
/*
* Authors: Felipe Balascio, Leonardo Kanashiro, Lucas Atsuo
* Group 3
*
* Arquivos parser-only do compilador MyPascal
* 07/11/2018
*
*/
#include <mypas.h>

void main(void){
	source = stdin;
	object = stdout;
	lookahead = gettoken(source);
	mypas();
}