/**@<mypas.c>::**/
/*
* Authors: Felipe Balascio, Leonardo Kanashiro, Lucas Atsuo
* Group 3
*
* Arquivos parser-only do compilador MyPascal
* 07/11/2018
*
*/

/*
mypas input.pas [ -o output ]

mypas input.pas
 >> cria a.o

mypas input.pas -o saida
 >> cria saida.o

*/

#include <mypas.h>

void main(int argc, char *argv[]){
	char **inputName, **outputName;
	FILE *input, *output;

	if(argc<2){
		printf("Nao ha arquivos de entrada .. Finalizando\n");
		exit(0);
	}else{
		inputName = &argv[1];
		if(input = fopen(*inputName, "r") ){

		}else{
			printf("Nao foi possivel abrir %s .. Finalizando", *inputName);
			exit(0);
		}
		if(strcmp(argv[2],"-o") == 0){
			if(argc>3){
				outputName = &argv[3];
				if((output = fopen(strcat(*outputName,".o"), "w+"))==NULL){
					printf("Erro ao criar o arquivo objeto .. Finalizando\n");
					exit(0);
				}
			}
		}else{
		}
	}



	source = stdin;
	object = stdout;
	lookahead = gettoken(source);
	mypas();
}