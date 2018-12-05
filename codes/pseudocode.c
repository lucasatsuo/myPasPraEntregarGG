/*@pseudocode.c*/
#include <pseudocode.h>
#include <keywords.h>
#include <tokens.h>
/*       Internal  types                || Class
 ----------------------------------------------
 * VOID: undefined types                || 0
 ----------------------------------------------
 * UINT, INT:    int32 : l-suffix regs  || 1
 * FLTP, REAL:   flt32 : f-suffix regs  || 2
 * DFLT, DOUBLE: flt64 : df-suffix regs || 3
 ----------------------------------------------
 * TRUE, FALSE,
 * BOOLEAN:      int8  : b-suffix regs  || 4
 */

/* Pseudo instrucoes de controle */

void mklooplabel(size_t lblindx){
    fprintf(object,".L%d:\n",lblindx);
}
void mklabel(size_t label){
	fprintf(object, "%s%d:\n", label);
}
void jump(size_t lblindx){
	fprintf(object,"\tjmp .L%d\n", lblindx);
}
void gofalse(size_t lblindx){
	fprintf(object,"\tjz .L%d\n", lblindx);
}

/* Pseudo instrucoes de movimentacao e controle da pilha */
void push(int regtype){
	char *suffix;
	switch(regtype){
		case 1: suffix = "l"; break;
		case 2: suffix = "f"; break;
		case 3: suffix = "df"; break;
		case 4: suffix = "b";
	}
	fprintf(object,"\tpush %%acc%s\n", suffix);
}
void pop(char *regtype){ // tem que ser resolvido
	// char *suffix;
	// switch(regtype){
	// 	case 1: suffix = "l"; break;
	// 	case 2: suffix = "f"; break;
	// 	case 3: suffix = "df"; break;
	// 	case 4: suffix = "b";
	// }
	fprintf(object,"\tpop %%acc%s\n", regtype);
}
void store(char *varoffset, char *suffix){
	fprintf(object, "\tmov %%acc%s, %s\n", suffix, varoffset);
}
void recall(char *varoffset, char *suffix){
	fprintf(object, "\tmov %s, %%acc%s\n", varoffset, suffix);
}

/* Pseudo instrucoes da ULA */
/* Operacoes binarias */
/* Adicao e subtracao */
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
/* Multiplicacao e Divisao */
void imul(void){
	fprintf(object, "\timull %%accl, (%%spl)\n");
}
void idiv(void){ 
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
/* Operacoes unarias */
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


/* Macro instrucoes: binary ops */
/* Macro para criacao das instrucoes binarias */
int macrobinary(int op, int oprndtype){
	switch(op){
		case '+':
			switch(oprndtype){
				case 1: 
					iadd();pop("l"); break;
				case 2: 
					fadd();pop("f"); break;
				case 3:
					dfadd();pop("df"); break;
				default: 
					return -1;
			}
			break;
		case '-':
			switch(oprndtype){
				case 1: 
					isub();pop("l"); break;
				case 2: 
					fsub();pop("f"); break;
				case 3:
					dfsub();pop("df"); break;
				default: 
					return -1;
			}
			break;		
		case OR:
			switch(oprndtype){
				case 4: 
					orb();pop("b"); break;
				default: 
					return -1;
			}
			break;
		case '*':
			switch(oprndtype){
				case 1: 
					imul();pop("l"); break;
				case 2: 
					fmul();pop("f"); break;
				case 3:
					dfmul();pop("df"); break;
				default: 
					return -1;
			}
			break;
		case '/':
			switch(oprndtype){
				case 1: 
					cvltofacc();
					cvltofstk();
					idiv();pop("l"); break;
				case 2: 
					fdiv();pop("f"); break;
				case 3:
					dfdiv();pop("df"); break;
				default: 
					return -1;
			}
			break;
		case DIV:
			switch(oprndtype){
				case 1: 
					idiv(); pop("l"); break;
				default: 
					return -1;
			}
			break;
		case MOD:
			switch(oprndtype){
				case 1: 
					idiv(); pop("l");
					fprintf(object, "\tmov %%rmdr, %%acc\n");
					break;
				default: 
					return -1;
			}
			break;
		case AND:
			switch(oprndtype){
				case 4: 
					andb(); 
					pop("b");
					break;
				default: 
					return -1;
			}
			break;	}
	return 0;
}

/* Macro para criacao das instrucoes unarias */
int macrounary(int oprndtype){
	switch(oprndtype){
		case 1:
			ineg(); break;
		case 2:
			fneg(); break;
		case 3:
			dfneg(); break;
		case 4:
			notb(); break;
		default:
			return -1;
	}
	return 0;
}

/* Operacoes de conversao de tipos */
void cvltofacc(void){
	fprintf(object, "\tcvltof %%accl, %%accf\n");
}
void cvltofstk(void){
	fprintf(object, "\tcvltof %%(spl), %%(spf)\n");
}


