#!/usr/make -f
# Author: Felipe Balascio, Leonardo Kanashiro, Lucas Atsuo
# First version: Wed Nov 7 2018
# Makefile for code directory of the MyPas project
#

projectname=mypas
projectdir=../
includedir=$(projectdir)include/
execdir=$(projectdir)bin/

execpath=$(execdir)$(projectname)

CC=gcc

cfiles=\
		mypas.c\
		lexer.c\
		parser.c\
		keywords.c\
		interface.c\
		pseudocodec\
		symtab.c

ofiles=\
       mypas.o\
       lexer.o\
       parser.o\
       keywords.o\
       interface.o

CFLAGS=-g -I$(includedir)

$(execpath): $(ofiles)
	$(CC)	-o $@	$^

clean:
	$(RM) $(ofiles)

mostlyclean: clean
	$(RM) *.tmp *~



