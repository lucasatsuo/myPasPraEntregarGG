/**@<parser.c>::**/
#include <parser.h>
size_t loopcount = 1;
/***************************************************************************

Definicoes sintaticas para uma versao simplificada de um compilador Pascal.
Para o curso de Compiladores.
De acordo com as seguintes gramaticas EBNF.

Start symbol:: mypas

Production Rules::

mypas -> PROGRAM ID ; header body .
***************************************************************************/
void mypas(void)
{
    match(PROGRAM); 
    match(ID); 
    match(';'); 
    header(); 
    body();
    match('.');
}
/***************************************************************************
Declarative scope::

header -> varmodel { procmodel | funcmodel }
***************************************************************************/
/* Abstrai FIRST(subroutine) */
flag_t issubroutine(void){
    switch(lookahead){
        case PROCEDURE:
        case FUNCTION:
            return lookahead;
    }
    return 0;
}

void header(void){
    varmodel();
    while(issubroutine()){
        if(lookahead == PROCEDURE)
            procmodel();
        else if(lookahead == FUNCTION)
            funcmodel();
    }
}
/***************************************************************************

varmodel -> [ VAR  vargroup { vargroup } ]

***************************************************************************/
void varmodel(void){
    if(lookahead == VAR){
        match(VAR);
        vargroup();
        while(lookahead == ID){
            vargroup();
        }
    }
}
/***************************************************************************

vargroup -> varlist : pretype ;

***************************************************************************/
int primvar,ultvar;
void vargroup(void){
    varlist();
    match(':');
    int grouptype = pretype();
    for (int i=primvar; i<=ultvar; i++){ symtab[i].type=grouptype; }
    match(';');
    // for (int i=primvar; i<=ultvar; i++){ printf("%s %d\n",symtab[i].objname,symtab[i].type);}
}
/***************************************************************************

varlist -> ID { , ID }

***************************************************************************/
void varlist(void){
    primvar = symtab_append(lexeme,0);
    match(ID);
    ultvar = primvar;
    while(lookahead == ','){
        match(',');
        ultvar = symtab_append(lexeme,0);
        match(ID);
    }
}
/***************************************************************************

pretype -> BOOLEAN | INTEGER | REAL | DOUBLE

***************************************************************************/
int pretype(void){
    switch(lookahead){
        case BOOLEAN:
            match(BOOLEAN);
            return 4;
        case INTEGER:
            match(INTEGER);
            return 1;
        case REAL:
            match(REAL);
            return 2;
        default:
            match(DOUBLE);
            return 3;
    }
}
/***************************************************************************

procmodel -> PROCEDURE ID formalparms ; header body ;

***************************************************************************/
void procmodel(void){
    match(PROCEDURE);
    match(ID);
    formalparms();
    match(';');
    header();
    body();
    match(';');
}
/***************************************************************************

funcmodel -> FUNCTION ID formalparms : pretype ; header body ;

***************************************************************************/
void funcmodel(void){
    match(FUNCTION);
    match(ID);
    formalparms();
    match(':');
    pretype();
    match(';');
    header();
    body();
    match(';');
}
/***************************************************************************

formalparms -> [ ( arglist ) ]

***************************************************************************/
void formalparms(void){
    if(lookahead == '('){
        match('(');
        arglist();
        match(')');
    }
}
/***************************************************************************

arglist -> argmodel { ; argmodel }

***************************************************************************/
void arglist(void){
    argmodel();
    while(lookahead == ';'){
        match(';');
        argmodel();
    }

}
/***************************************************************************

argmodel -> [ VAR ] varlist : pretype

***************************************************************************/
void argmodel(void){
    if(lookahead == VAR){
        match(lookahead);
    }
    varlist();
    match(':');
    pretype();
}
/***************************************************************************
Imperative scope::

body -> BEGIN stmtlist END
***************************************************************************/
void body(void){
    match(BEGIN);
    stmtlist();
    match(END);
}
/***************************************************************************

stmtlist -> stmt { ; stmt }

***************************************************************************/
void stmtlist(void){
    stmt();
    while(lookahead == ';'){
        match(';');
        stmt();
    }
}
/***************************************************************************
stmt ->   body
| ifstmt
| whlstmt
| repstmt
| smpexpr
| <empty>
***************************************************************************/
void stmt(void){
    switch(lookahead){
        // MyPascal keywords:
        case BEGIN:
            body();
            break;
        case IF:
            ifstmt();
            break;
        case WHILE:
            whlstmt();
            break;
        case REPEAT:
            repstmt();
            break;
            // either the first of a simple expression or an empty statement:
        default:
            switch(lookahead){ /* abstrai FIRST(smpexpr) */
                case '+': case '-': case NOT: // unary operators
                case '(': case ID: case UINT: case FLTP:
        case TRUE: case FALSE:
                    smpexpr(0);
                break;
                default:
                    ;
            }
    }
}
/***************************************************************************

expr -> smpexpr [ relop smpexpr ]

relop ->  = 
    | > 
    | ">="  // GEQ
    | < 
    | "<="  // LEQ 
    | "<>"  // NEQ


***************************************************************************/
int expr(void){
    /**/int typel, typer;/**/ 
    /* a smpexpr da esquerda comeca com tipo herdado void 
    * no caso de haver uma relop, o tipo sintetizado de smpexpr esquerdo
    * e passado para o smpexpr da direita */
    /**/typel = smpexpr(0);/**/
    switch(lookahead){
        case '=':
        case '>':
        case '<':
        case GEQ:
        case LEQ:
        case NEQ:
            match(lookahead);
            typer = smpexpr(typel);
        default:
            ;   
    }
}
/**
* retorna o tipo minimo para um operador unario
*/
int getmintype(int op){
    int mintype=0;
    switch(op){
        case '+':
        case '-':
            mintype = 1; break;
        case NOT:
            mintype = 4;
    }
    return mintype;
}

/**
* retorna o operador da operacao unaria.
* retorna 0 se nao for uma operacao unaria.
*/
int unaryop(void){ 
    switch(lookahead){
        case '+': 
            match(lookahead);
            return '+';
        case '-':
            match(lookahead);
            return '-';
        case NOT:
            match(lookahead);
            return NOT;
    }
    return 0;
}

/* tabela de promocao   
dado um tipo antigo e um tipo novo, promove o tipo antigo para o tipo novo
retornando o tipo promovido
retorna valores negativos caso nao sejam compativeis
    0  1  2  3  4  newtype
- - - - - - - - - - - - - -
0|  0  1  2  3  4
1| -1  1  2  3 -2
2| -1  2  2  3 -2
3| -1  3  3  3 -2
4| -1 -2 -2 -2  4
oldtype
*/
int promote(int oldtype, int newtype){
    switch(oldtype){
        case 0:
            return newtype;
        case 1:
            switch(newtype){
                case 0: return -1;
                case 1: return 1;
                case 2: return 2;
                case 3: return 3;
                case 4: return -2;
            }
        case 2:
            switch(newtype){
                case 0: return -1;
                case 1: return 1;
                case 2: return 2;
                case 3: return 3;
                case 4: return -2;
            }
        case 3:
            switch(newtype){
                case 0: return -1;
                case 1: case 2: case 3: return 3;
                case 4: return -2;
            }
        case 4:
            switch(newtype){
                case 0: return -1;
                case 1: case 2: case 3: return -2;
                case 4: return 4;
            }
    }
    return -2;
}

/***************************************************************************

smpexpr -> [ isneg ] fact { otimes fact } { oplus fact { otimes fact }}

isneg  -> NOT | + | - 
otimes -> AND | DIV | * | / | MOD
oplus  -> OR | + | -

                              .---<--- (  oplus ) ---<---.
smpexpr:                      |                          |
                              |   .-<- ( otimes ) -<-.   |
                              |   |                  |   |
                              |   |    +--------+    |   |
-->-.-------->--------.--->---'->-'->- | factor | ->-'->-'---->---- end
    |                 |                +--------+
    '->- ( isneg ) ->-'

***************************************************************************/
int haserror = 0;
int smpexpr(int inhertype){
    int factor_t;
    /**/int isunary =/**/ unaryop();
    /**/int negation = isunary; if(negation == '+') negation=0;
    /**/int typematch = iscompatop(negation, inhertype)/**/;
    if(typematch<0) haserror=1;
    /**/int mintype = getmintype(negation); /**/
        /* nesse ponto pode ter ocorrido promocao do tipo herdado e o tipo
        da operacao unaria */
    /**/int currtype = promote(inhertype,mintype); 
    /* Estas flags sao usadas para aproximar a visualizacao do codigo
    com o digrama sintatico */
    flag_t    otimes =  0;
    flag_t    oplus  =  0;

    T_begin: 
    F_begin: 
    factor_t = factor(currtype);
    /** checa se ha operacoes pendentes e executa **/
    /**/if(oplus){ 
        push(currtype); 
        if(haserror == 0)
            macrobinary(oplus,currtype);
        oplus = 0;
    };/**/

    /**/if(negation){
        if(typematch = iscompatop(negation,factor_t)){
            if(haserror == 0)
                macrounary(mintype);
        }
        negation = 0;
    }/**/

    /**/if(otimes){
        push(currtype);
        if(haserror == 0)
            macrobinary(otimes,currtype);
        otimes = 0;
    }/**/

    /* Nesse ponto, esta dentro do laco em torno do factor
    cada vez que encontra um otimes, ou oplus volta para o factor(), igual a gramatica
    o uso do GOTO para otimizacao 
    ifs com otimes e oplus abstraem respectivamente
    { otimes fact } 
    { oplus fact { otimes fact }}
    */
    otimes = lookahead;
    if( otimes == '*' || otimes == '/' || otimes == AND || 
        otimes == DIV || otimes == MOD) {
        /**/typematch = iscompatop(otimes, currtype);/**/
        /**/currtype = promote(currtype,factor_t);/**/
        if(currtype<0 || typematch<0) haserror=1;
        match(otimes);
        goto F_begin;
    } else { otimes=0; }

    oplus = lookahead;
    if( oplus == '+' || oplus == '-' || oplus == OR) {
        /**/typematch = iscompatop(oplus, currtype);/**/
        /**/currtype = promote(currtype,factor_t);/**/ 
        if(currtype<0 || typematch<0) haserror=1;
        match(oplus);
        goto T_begin;
    }

    return currtype;
}

/***************************************************************************
 Tabela de compatibilidade
 predicado que retorna o menor tipo 
 se tiver o tipo errado retorna -1
***************************************************************************/
int iscompatop(int oper, int currenttype){
    switch(oper){
        case '+':
        case '-':
        case '*':
        case '/':
        switch(currenttype){
            case 0:
            case 1:
            case 2:
            case 3:
                return 1; 
                break;
            default:
                return -1;
        }
        case OR:
        case AND:
        switch(currenttype){
            case 4:
                return 4;
                break;
            default:
                return -1;
        }

    }
}
/***************************************************************************
factor ->   ID [ ASGN expr | ( exprlist ) ] 
  | UINT
  | FLTP
  | TRUE
  | FALSE
  | ( expr )
***************************************************************************/
int factor(int inherited_t)
{
    int actual_t;
    char variable[100];
    switch (lookahead){
        case ID:
        strcpy(variable,lexeme);
        match(ID);
            if(lookahead == ASGN){ // a := expr
                match(ASGN);
                int type = expr(); 
                int i = symtab_lookup(variable);
                symtab[i].type = type;
                actual_t = type; 
            } else if(lookahead == '(') {
                match('(');
                exprlist();
                match(')');
            } else{
                /* Salva o valor do lexeme no acumulador */
//                symtab[symtab_lookup(lexeme)].assmcode = gencode(lexeme,type) ;
                actual_t = symtab[symtab_lookup(lexeme)].type;
            }

        return actual_t;
            break;
        case UINT:
            match(lookahead);
//          symtab[symtab_lookup(lexeme)].assmcode = gencode(lexeme,type) ;
            return actual_t = 1;
        case FLTP:
//          symtab[symtab_lookup(lexeme)].assmcode = gencode(lexeme,type) ;
            match(lookahead);
            return actual_t = 2;
        case TRUE:
        case FALSE:
            match(lookahead);
            break;
        default:
        match('('); expr(); match(')'); 
    }
}
/***************************************************************************

exprlist -> expr { , expr }

***************************************************************************/
void exprlist(void){
    expr();
    while(lookahead==','){
        match(',');
        expr();
    }

}
/***************************************************************************

ifstmt -> IF expr THEN stmt [ ELSE stmt ]

***************************************************************************/
void ifstmt(void){
    /**0*/size_t lblelse, lblendif;/*0**/

    match(IF); expr(); match(THEN); 
    /**1*/gofalse(lblelse=lblendif=loopalloc);/*1**/
    stmt();
    if(lookahead == ELSE){
        match(ELSE); 
        /**2 a*/ jump(lblendif=loopalloc); /*2 a**/
        /**2 b*/ mklooplabel(lblelse); /*2 b**/
        stmt();
    }
    /**3*/ mklooplabel(lblendif); /*3**/
}
/***************************************************************************

whlstmt ->    || <whlstmt>.as <- 
WHILE expr DO || 1) ".L<<whlhead = loopcount++>>:"
stmt          ||            <expr>.as
              || 2)         "gofalse .L<<whltail = loopcount++>>"
              ||            <stmt>.as
              || 3)           "jump .L<<whlhead>>"
              || 4) ".L<<whltail>>:"
***************************************************************************/
void whlstmt(void){
    /**0*/size_t whlhead, whltail;/*0**/

    match(WHILE);  /**1*/mklooplabel(whlhead=loopalloc);/*1**/
    expr(); /**2*/gofalse(whltail=loopalloc);/*2**/
    match(DO); 
    stmt(); /**3*/jump(whlhead);/*3**/
            /**4*/mklooplabel(whltail);/*4**/
}
/***************************************************************************

repstmt ->       || <repstmt>.as <-
    REPEAT       || 1) ".L<<replbl = loopcount++>>:"
        stmtlist ||         <stmtlist>.as
    UNTIL expr   ||         <expr>.as
                 || 2)      "gofalse .L"<<replbl>>

***************************************************************************/
void repstmt(void){
    /**0*/size_t replbl; /*0**/
    match(REPEAT);
    /**1*/ mklooplabel(replbl=loopalloc);/*1**/
    stmtlist();
    match(UNTIL);
    expr();
    /**2*/ gofalse(replbl);/*2**/
}
