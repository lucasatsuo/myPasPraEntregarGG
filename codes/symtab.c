#include <symtab.h>

SYMTABMODEL symtab[MAXSYMTBENTRIES];

/** aponta a proxima posicao disponivel **/
size_t symtab_nextentry = 1;

/** procura a posicao da tabela de acordo com o identificador armazenado **/
size_t symtab_lookup(const char *query){
	for(int i = 0; i<MAXSYMTBENTRIES; i++){
		if(strcmp(symtab[i].objname, query) == 0)
			return i;
	}
	return 0;
}

/** symtab_append faz papel de predicado para identificadores ja existentes
retorna valor negativo em caso de overflow  **/
size_t symtab_append(const char *newentry, int type){
	int i = symtab_lookup(newentry);
	if(i==MAXSYMTBENTRIES) return -1;
	if(i != 0) // significa que a entrada ja existe na tabela
		return 0;
	i = symtab_nextentry++;
	strcpy(symtab[i].objname, newentry);
	symtab[i].type = type;
	return i;
}