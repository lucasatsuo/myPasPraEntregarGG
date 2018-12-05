# myPas
compilador para uma linguagem de programação inspirada em PASCAL

mano bagulho é o seguinte:
TODO LIST


[ok] versão compilável do compilador (remoção dos erros de compilação)

[ok] tem que fazer a entrada de arquivos, argc, argv e pá

[ok] tem que arrumar as macros, pra parte de geração (ação semantica)
macros estão no pseudocode

[ok] no parser tem que arrumar aquelas tabelas
iscompat(), mintype() - se ainda tiver - , e mais os que faltarem

[ok] tem que arrumar o funcionamento do smpexpr()
mas certeza so temos da morte

[ok] adicionar o dicionario de tokens pra arrumar a mostragem de erro dos tokens

se pá é isso.


gcc interface.c keywords.c lexer.c mypas.c parser.c pseudocode.c symtab.c -I../include/

a.exe entrada.pas -o saida

deve gerar um saida.o com os bagulho em assembly