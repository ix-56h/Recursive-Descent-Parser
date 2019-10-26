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

typedef	struct		s_node
{
	struct s_node	*left;
	t_toktype		tok;
	char			*data;
	struct s_node	*right;
}					t_node;

t_flags	check_param(char **av);
void	term(char *s, t_tokens *cur, t_node *node);
void	factor(char *s, t_tokens *cur, t_node *node);
void	expr(char *s, t_tokens *cur, t_node *node);
#endif
