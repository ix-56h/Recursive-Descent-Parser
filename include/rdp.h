#include "tokenizer_rules.h"
#include <stdio.h>
#include <string.h>

typedef	struct	s_flags
{
	unsigned	debug_all:1;
	unsigned	ast_draw:1;
}				t_flags;

t_flags	check_param(char **av);
