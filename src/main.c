#include "rdp.h"

t_node	*save_node(t_node *left, t_tokens tok, t_node *right)
{
	return ((t_node*)0);
}

void	factor(char *s, t_tokens *cur, t_node *node)
{
	printf("fac -> %s\n", DEBUG_TOK[cur->tok]);
	if (cur->tok == TOK_DIGIT)
		*cur = get_next_token(s);
	else if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		expr(s, cur, node);
		printf("fac2 -> %s\n", DEBUG_TOK[cur->tok]);
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
	while (cur->tok == TOK_MUL || cur->tok == TOK_DIVIDE)
	{
		printf("term -> %s\n", DEBUG_TOK[cur->tok]);
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

	while (cur->tok == TOK_PLUS || cur->tok == TOK_MINUS)
	{
		printf("expr -> %s\n", DEBUG_TOK[cur->tok]);
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
	t_flags		f;
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
