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
	int				key;
}					t_node;

t_flags	check_param(char **av);
t_node	*term(char *s, t_tokens *cur);
t_node	*factor(char *s, t_tokens *cur);
t_node	*expr(char *s, t_tokens *cur);
void	bst_print_dot(t_node *tree, FILE *stream);
#endif
