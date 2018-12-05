#include <symtab.h>

#define MXASLINE 80

typedef struct __symtab_model__ {
	char objname[MAXIDLEN+1];
	char assmcod[MXASLINE+1];  /* tabela com o nome da variavel com o rotulo ou o offset correspondente no assembly */
	int type; /** registra os tipos internos: 0 void, 1 int32, 2 flt32, 3 flt64, 4 boolean == 1 byte **/
} SYMTABMODEL;

#define MAXSYMTBENTRIES 0x10000

SYMTABMODEL symtab[MAXSYMTBENTRIES];

/** symtab next available descriptor: **/
size_t symtab_nextentry = 1;

/** symtab lookup **/
size_t symtab_lookup(const char *query){
	for(int i = 0; i<MAXSYMTBENTRIES; i++){
		if(strcmp(symtab[i].objname, query) == 0)
			return i;
	}
	return 0;
}

/** symtab append is also a predicate function**/
/** returns negative on table overflow**/
size_t symtab_append(const char *newentry, int type){
	int i = symtab_lookup(newentry);
	if(i != 0) // means that the entry already exists 
		return 0;
	i = symtab_nextentry++;
	strcpy(symtab[i].objname, newentry);
	symtab->type = type;
	return i;
}