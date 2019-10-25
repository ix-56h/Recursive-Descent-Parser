#include "rdp.h"

void	factor(char *s, t_tokens *cur)
{
	if (cur->tok == TOK_DIGIT)
		*cur = get_next_token(s);
	else if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		expr(s, cur);
	}
	else
	{
		printf("Syntax error : %s\n", cur->data);
		free(cur->data);
		exit(1);
	}
	free(cur->data);
}

void	term(char *s, t_tokens *cur)
{
	factor(s, cur);
	while (cur->tok == TOK_MUL || cur->tok == TOK_DIVIDE)
	{
		if (cur->tok == TOK_MUL)
			*cur = get_next_token(s);
		else if (cur->tok == TOK_DIVIDE)
			*cur = get_next_token(s);
		else
		{
			printf("Syntax error : %s\n", cur->data);
			free(cur->data);
			exit(1);
		}
		free(cur->data);
	}
}

void	expr(char *s, t_tokens *cur)
{
	term(s, cur);

	while (cur->tok == TOK_PLUS || cur->tok == TOK_MINUS)
	{
		if (cur->tok == TOK_PLUS)
			get_next_token(s);
		else if (cur->tok == TOK_MINUS)
			get_next_token(s);
		else
		{
			printf("Syntax error : %s\n", cur->data);
			free(cur->data);
			exit(1);
		}
		free(cur->data);
	}
}

int main(int ac, char **av)
{
	char *input = av[1];
	t_flags	f;
	t_tokens	tok;

	if (ac < 2)
	{
		printf("Usage: ./rdp \"2*8+(1 - 2)\" [-debug=all] [-ast=draw]\n");
		return (0);
	}
	f = check_param(av + 2);
	if (f.debug_all)
		printf("f.d = %u\nf.a = %u\n", f.debug_all, f.ast_draw);
	tok = get_next_token(input);
	expr(input, &tok);
	return 0;
}
