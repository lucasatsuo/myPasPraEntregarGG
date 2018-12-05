#include <lexer.h>
#include <string.h>

#pragma once
#define MXASLINE 80
#define MAXSYMTBENTRIES 0x10000

typedef struct __symtab_model__ {
	char objname[MAXIDLEN+1];
	char assmcod[MXASLINE+1];
	float value;
	int type; /** registra os tipos internos: 0 void, 1 int32, 2 flt32, 3 flt64, 4 boolean == 1 byte **/
} SYMTABMODEL;

size_t symtab_lookup(const char *query);
size_t symtab_append(const char *newentry, int type);