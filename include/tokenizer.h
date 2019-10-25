#ifndef TOKENIZER_H
# define TOKENIZER_H
typedef enum	e_toktype {
	TOK_ERROR,
	TOK_SP,
	TOK_EQUAL,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_EOF,
	TOK_DIGIT,
	/*
	**	Abstract token
	*/
	TOK_OPERATOR,
	TOK_PLUS,
	TOK_MINUS,
	TOK_MUL,
	TOK_MOD,
	TOK_DIVIDE,
	TOK_MAX
}				t_toktype;

typedef enum	e_chr_class {
	CHR_ERROR,
	CHR_SP,
	CHR_DIGIT,
	CHR_OPERATOR,
	CHR_RPAREN,
	CHR_LPAREN,
	CHR_MAX
}				t_chr_class;

typedef struct		s_tokens {
	t_toktype		tok;
	char			*data;
}					t_tokens;

extern t_chr_class		get_chr_class[255];
extern t_toktype	token_chr_rules[TOK_MAX][CHR_MAX];
extern t_toktype	get_tok_type[CHR_MAX];
extern char	DEBUG_TOK[TOK_MAX][11];

t_tokens	get_sequence_token(char *s, int *i, t_toktype toktype, t_chr_class origin_class);
t_tokens	get_token(char *s, int *i, t_toktype toktype);
t_toktype	get_operator(char *s);
void		ignore_chr_class(char *s, int *i, t_chr_class chr_class);
int			is_opening_class(t_chr_class chr_class);
t_tokens	save_token(char *s, int anchor, t_toktype toktype);
t_tokens	tokenizer(char *s);
t_tokens	get_next_token(char *s);
#endif
