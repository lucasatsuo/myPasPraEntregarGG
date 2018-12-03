/*@pseudocode.c*/
#include <pseudocode.h>

/* Pseudo Control Instructions */

void mklabel(size_t lblindx){
    fprintf(object,".L%d:\n",lblindx);
}

void jump(size_t lblindx){
	fprintf(object,"\tjump .L%d\n", lblindx);
}

void gofalse(size_t lblindx){
	fprintf(object,"\tgofalse .L%d\n", lblindx);
}

/* Pseudo move and stack Instructions */
/* se julgar necessario criar imov, movb, movl ...*/
void move(void){
	fprintf(object,"\tmov %%acc, (%%sp)\n");
}
void push(void){
	fprintf(object,"\tpush %s\n");
}
void pop(void){
	fprintf(object,"\tpop %s\n");
}


/* Pseudo ALU Instructions */
/* Binary Operations */
/* Adition and Subtract */
void iadd(void){
	fprintf(object, "\taddl %%accl, (%%spl)\n");
}
void isub(void){
	fprintf(object, "\tsubl %%accl, (%%spl)\n");
}
void fadd(void){
	fprintf(object, "\tfadd %%accf, (%%spf)\n");
}
void fsub(void){
	fprintf(object, "\tfsub %%accf, (%%spf)\n");
}
void dfadd(void){
	fprintf(object, "\tdfadd %%accdf, (%%spdf)\n");
}
void dfsub(void){
	fprintf(object, "\tdfsub %%accdf, (%%spdf)\n");
}
void orb(void){ /* OR binary*/
	fprintf(object, "\torb %%accn, (%%spn)\n");
}
/* Multiplication and Division */
void imul(void){
	fprintf(object, "\timull %%accl, (%%spl)\n");
}
void idiv(void, char *rmdr){ /* dest / src , rmdr remainder*/
	fprintf(object, "\tidivl %%accl, (%%spl)\n");
}
void fmul(void){
	fprintf(object, "\tfmul %%accf, (%%spf)\n");
}
void fdiv(void){
	fprintf(object, "\tfdiv %%accf, (%%spf)\n");
}
void dfmul(void){
	fprintf(object, "\fdfmul %%accdf, (%%spdf)\n");
}
void dfdiv(void){
	fprintf(object, "\tdfdiv %%accdf, (%%spdf)\n");
}
void andb(void){
	fprintf(object, "\tandb %%accb, (%%spb)\n");
}
/* Unary Operations */
void ineg(void){
	fprintf(object, "\tnegl %%accl\n");
}
void fneg(void){
	fprintf(object, "\tfneg %%accf\n");
}
void dfneg(void){
	fprintf(object, "\tdfneg %%accdf\n");
}
void notb(void){
	fprintf(object, "\tnotb %%accb\n");
}