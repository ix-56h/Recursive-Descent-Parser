#include "rdp.h"

t_flags		f;

t_node	*save_node(t_node *left, t_tokens tok, t_node *right)
{
	t_node	*node = NULL;

	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->left = left;
	node->right = right;
	node->tok = tok.tok;
	node->data = tok.data;
	return (node);
}

void	factor(char *s, t_tokens *cur, t_node *node)
{
	(f.debug_all ? printf("factor -> %s\n", DEBUG_TOK[cur->tok]) : 0);
	if (cur->tok == TOK_DIGIT)
		*cur = get_next_token(s);
	else if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		expr(s, cur, node);
		(f.debug_all ? printf("factor lparen -> %s\n", DEBUG_TOK[cur->tok]) : 0);
		if (cur->tok == TOK_RPAREN)
			*cur = get_next_token(s);
		else
		{
			printf("1Syntax error : %s\n", DEBUG_TOK[cur->tok]);
			exit(1);
		}
	}
	else
	{
		printf("2Syntax error : %s\n", DEBUG_TOK[cur->tok]);
		free(cur->data);
		exit(1);
	}
	free(cur->data);
}

void	term(char *s, t_tokens *cur, t_node *node)
{
	factor(s, cur, node);
	(f.debug_all ? printf("term -> %s\n", DEBUG_TOK[cur->tok]) : 0);
	while (cur->tok == TOK_MUL || cur->tok == TOK_DIVIDE)
	{
		(f.debug_all ? printf("term -> %s\n", DEBUG_TOK[cur->tok]) : 0);
		if (cur->tok == TOK_MUL)
			*cur = get_next_token(s);
		else if (cur->tok == TOK_DIVIDE)
			*cur = get_next_token(s);
		else
		{
			printf("3Syntax error : %s\n", DEBUG_TOK[cur->tok]);
			free(cur->data);
			exit(1);
		}
		factor(s, cur, node);
	}
}

void	expr(char *s, t_tokens *cur, t_node *node)
{
	term(s, cur, node);
	(f.debug_all ? printf("expr -> %s\n", DEBUG_TOK[cur->tok]) : 0);
	while (cur->tok == TOK_PLUS || cur->tok == TOK_MINUS)
	{
		(f.debug_all ? printf("expr -> %s\n", DEBUG_TOK[cur->tok]) : 0);
		if (cur->tok == TOK_PLUS)
			*cur = get_next_token(s);
		else if (cur->tok == TOK_MINUS)
			*cur = get_next_token(s);
		else
		{
			printf("4Syntax error : %s\n", DEBUG_TOK[cur->tok]);
			free(cur->data);
			exit(1);
		}
		term(s, cur, node);
	}
}

int main(int ac, char **av)
{
	char		*input = av[1];
	t_tokens	tok;
	t_node		*node;

	if (ac < 2)
	{
		printf("Usage: ./rdp \"2*8+(1 - 2)\" [-debug=all] [-ast=draw]\n");
		return (0);
	}
	f = check_param(av + 2);
	if (f.debug_all)
		printf("f.d = %u\nf.a = %u\n", f.debug_all, f.ast_draw);
	tok = get_next_token(input);
	expr(input, &tok, node);
	return 0;
}
