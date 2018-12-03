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
void move(char *src, char *dest){
	fprintf(object,"\tmov %s, %s\n", src, dest);
}
void push(char *reg){
	fprintf(object,"\tpush %s\n", reg);
}
void pop(char *reg){
	fprintf(object,"\tpop %s\n", reg);
}


/* Pseudo ALU Instructions */
/* Binary Operations */
/* Adition and Subtract */
void iadd(char *src, char *dest){
	fprintf(object, "\tiadd %s, %s\n", src, dest);
}
void isub(char *src, char *dest){
	fprintf(object, "\tisub %s, %s\n", src, dest);
}
void fadd(char *src, char *dest){
	fprintf(object, "\tfadd %s, %s\n", src, dest);
}
void fsub(char *src, char *dest){
	fprintf(object, "\tfsub %s, %s\n", src, dest);
}
void dfadd(char *src, char *dest){
	fprintf(object, "\tdfadd %s, %s\n", src, dest);
}
void dfsub(char *src, char *dest){
	fprintf(object, "\tdfsub %s, %s\n", src, dest);
}
void orb(char *src, char *dest){ /* OR binary*/
	fprintf(object, "\tiadd %s, %s\n", src, dest);
}
/* Multiplication and Division */
void imul(char *src, char *dest){
	fprintf(object, "\timul %s, %s\n", src, dest);
}
void idiv(char *src, char *dest, char *rmdr){ /* dest / src , rmdr remainder*/
	fprintf(object, "\tidiv %s, %s\n", src, dest);
}
void fmul(char *src, char *dest){
	fprintf(object, "\tfmul %s, %s\n", src, dest);
}
void fdiv(char *src, char *dest){
	fprintf(object, "\tfdiv %s, %s\n", src, dest);
}
void dfmul(char *src, char *dest){
	fprintf(object, "\fdfmul %s, %s\n", src, dest);
}
void dfdiv(char *src, char *dest){
	fprintf(object, "\tdfdiv %s, %s\n", src, dest);
}
void andb(char *src, char *dest){
	fprintf(object, "\tandb %s, %s\n", src, dest);
}
/* Unary Operations */
void ineg(char *dest){
	fprintf(object, "\tineg %s, %s\n", src, dest);
}
void fneg(char *dest){
	fprintf(object, "\tfneg %s, %s\n", src, dest);
}
void dfneg(char *dest){
	fprintf(object, "\tdfneg %s, %s\n", src, dest);
}
void notb(char *dest){
	fprintf(object, "\tnotb %s, %s\n", src, dest);
}