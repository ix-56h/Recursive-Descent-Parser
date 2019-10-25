#include "rdp.h"

t_chr_class		get_chr_class[255] = {
	[' '] = CHR_SP,
	['\t'] = CHR_SP,

	['-'] = CHR_OPERATOR,
	['%'] = CHR_OPERATOR,
	['/'] = CHR_OPERATOR,
	['*'] = CHR_OPERATOR,
	['+'] = CHR_OPERATOR,
	['='] = CHR_OPERATOR,

	['('] = CHR_RPAREN,
	[')'] = CHR_LPAREN,

	['0' ... '9'] = CHR_DIGIT
};

t_toktype	token_chr_rules[TOK_MAX][CHR_MAX] = {
	[TOK_SP] = {[CHR_SP] = 1,},
	[TOK_DIGIT] = {[CHR_DIGIT] = 1,},
	[TOK_OPERATOR] = {[CHR_OPERATOR] = 1, },
	[TOK_LPAREN] = {},
	[TOK_RPAREN] = {},
};

t_toktype	get_tok_type[CHR_MAX] = {
	[CHR_SP] = TOK_SP,
	[CHR_DIGIT] = TOK_DIGIT,
	[CHR_RPAREN] = TOK_RPAREN,
	[CHR_LPAREN] = TOK_LPAREN,
	[CHR_OPERATOR] = TOK_OPERATOR
};

char	DEBUG_TOK[TOK_MAX][11] = {
	[TOK_SP] = "TOK_SP",
	[TOK_EQUAL] = "TOK_EQUAL",
	[TOK_LPAREN] = "TOK_LPAREN",
	[TOK_RPAREN] = "TOK_RPAREN",
	[TOK_EOF] = "TOK_EOF",
	[TOK_DIGIT] = "TOK_DIGIT",
	[TOK_PLUS] = "TOK_PLUS",
	[TOK_MINUS] = "TOK_MINUS",
	[TOK_MUL] = "TOK_MUL",
	[TOK_MOD] = "TOK_MOD",
	[TOK_DIVIDE] = "TOK_DIVIDE"
};

t_tokens	save_token(char *s, int anchor, t_toktype toktype)
{
	t_tokens ret;
	ret.tok = toktype;
	ret.data = strndup(s, anchor);
	return ret;
}

void	ignore_wspace(char *s, int *i)
{
	while (s[*i] && get_chr_class[(unsigned char)s[*i]] == CHR_SP)
		(*i)++;
}

t_toktype	get_operator(char *s)
{
	if (!strcmp(s, "+"))
		return (TOK_PLUS);
	if (!strcmp(s, "-"))
		return (TOK_MINUS);
	if (!strcmp(s, "*"))
		return (TOK_MUL);
	if (!strcmp(s, "/"))
		return (TOK_DIVIDE);
	return (0);
}

t_tokens	get_token(char *s, int *i, t_toktype toktype)
{
	t_chr_class	chr_class;
	int			anchor;

	anchor = 1;
	//printf("i = %d\nanchor = %d chr = %c\n", *i, anchor, s[*i]);
	while (s[*i] && token_chr_rules[toktype][(chr_class = get_chr_class[(unsigned char)s[*i]])])
	{
		//printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[*i], anchor);
		anchor++;
		(*i)++;
	}
	//printf("i = %d\nanchor = %d chr = %c\n", *i, anchor, s[*i]);
	//printf("{%s, \"%.*s\"}\n", DEBUG_TOK[toktype], anchor, s + (*i - anchor));
	return (save_token(s + (*i - anchor), anchor, toktype));
}

t_tokens	get_next_token(char *s)
{
	t_chr_class		chr_class = 0;
	t_toktype		toktype = 0;
	t_tokens		token;
	static	int		i = 0;

	if (s[i] == '\0')
		return (save_token(NULL, 0, TOK_EOF));
	if (!(chr_class = get_chr_class[(unsigned char)s[i]]))
		return (save_token(s, 0, TOK_ERROR));
	if (chr_class == CHR_SP)
	{
		ignore_wspace(s, &i);
		return (get_next_token(s));
	}
	toktype = get_tok_type[chr_class];
	i++;
	token = get_token(s, &i, toktype);
	if (token.tok == TOK_OPERATOR && !(token.tok = get_operator(token.data)))
	{
		token.tok = TOK_ERROR;
		return (token);
	}
	return (token);
}

/*int main(int argc, char *argv[])
{
	t_tokens	tok;

	(void)argc;
	tok = get_next_token(argv[1]);
	while (tok.tok != TOK_EOF && tok.tok != TOK_ERROR)
	{
		printf("{%s, \"%s\"}\n", DEBUG_TOK[tok.tok], tok.data);
		tok = get_next_token(argv[1]);
	}
	if (tok.tok == TOK_ERROR)
		printf("Syntax ERROR\n");
	return 0;
}*/
