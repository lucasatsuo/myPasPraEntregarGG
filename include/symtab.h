#include <lexer.h>
#include <string.h>

#pragma once

size_t symtab_lookup(const char *query);
size_t symtab_append(const char *newentry, int type);