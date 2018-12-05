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
#include <getopt.h>

void main(int argc, char *argv[]){
	char nomeOutput[50] = "a", *nomeInput = NULL, *extensao;
	int opt = 0;

	if(argc < 2){
		fprintf(stderr, "Nao ha arquivos de entrada .. Finalizando\n");
		exit(0);
	}


	while( (opt = getopt(argc, argv, "o:")) > 0 ) {
		switch(opt){
			case 'o': strcpy(nomeOutput,optarg);
		}
	}

	if ( argv[optind] != NULL ) {
		nomeInput = argv[optind];
	}

	extensao = strchr(nomeInput, '.');

	if(strcmp(extensao,".pas")!=0 && strcmp(extensao,".mypas")!=0 && strcmp(extensao,".mpas")!=0){
		fprintf(stderr, "Extensao invalida no arquivo de entrada .. Finalizando\n");
		exit(0);
	}

	if( (source = fopen(nomeInput, "r")) == NULL){
		fprintf(stderr, "Falha ao abrir %s .. Finalizando\n", nomeInput);
		exit(0);
	}


	if( (object = fopen(strcat(nomeOutput,".o"), "w+")) == NULL){
		fprintf(stderr, "Falha ao criar arquivo objeto .. Finalizando\n");
		exit(0);
	}

	lookahead = gettoken(source);
	mypas();
}