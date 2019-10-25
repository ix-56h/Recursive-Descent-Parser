#ifndef RDP_H
# define RDP_H
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef	struct	s_flags
{
	unsigned	debug_all:1;
	unsigned	ast_draw:1;
}				t_flags;

t_flags	check_param(char **av);
void	term(char *s, t_tokens *cur);
void	factor(char *s, t_tokens *cur);
void	expr(char *s, t_tokens *cur);
#endif
