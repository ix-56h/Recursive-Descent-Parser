#include "rdp.h"

t_flags		f;

t_node	*save_node(t_node *left, t_tokens tok, t_node *right)
{
	t_node	*node = NULL;
	static int	cur_key = 0;

	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->left = left;
	node->right = right;
	node->key = cur_key;
	node->tok = tok.tok;
	node->data = tok.data;
	cur_key++;
	return (node);
}

t_node	*factor(char *s, t_tokens *cur)
{
	t_node	*node = NULL;
	(f.debug_all ? printf("factor -> %s\n", DEBUG_TOK[cur->tok]) : 0);
	if (cur->tok == TOK_DIGIT)
	{
		node = save_node(NULL, *cur, NULL);
		*cur = get_next_token(s);
	}
	else if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		node = expr(s, cur);
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
	return (node);
}

t_node	*term(char *s, t_tokens *cur)
{
	t_node *node = factor(s, cur);
	t_tokens tmp_tok = *cur;
	// for the next parser, need to make a eat func and not use gnt with static index for the code sake

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
		node = save_node(node, tmp_tok, factor(s, cur));
	}
	return (node);
}

t_node	*expr(char *s, t_tokens *cur)
{
	t_node	*node = term(s, cur);
	t_tokens tok;
	// for the next parser, need to make a eat func and not use gnt with static index for the code sake
	
	(f.debug_all ? printf("expr -> %s\n", DEBUG_TOK[cur->tok]) : 0);
	while (cur->tok == TOK_PLUS || cur->tok == TOK_MINUS)
	{
		tok = *cur;
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
		node = save_node(node, tok, term(s, cur));
	}
	return (node);
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
	node = expr(input, &tok);
	if (f.ast_draw)
	{
		FILE *stream = fopen("tree.dot", "w");
		if (!stream)
			exit(0);
		bst_print_dot(node, stream);
	}
	return 0;
}
