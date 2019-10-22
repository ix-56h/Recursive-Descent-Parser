/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:16 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/22 20:08:08 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOK_H
# define FT_TOK_H
typedef enum	e_toktype {
	TOK_ERROR,
	TOK_SP,
	TOK_EQUAL,
	TOK_SUB,
	TOK_EOF,
	TOK_DIGIT,
	/*
	**	Abstract token
	*/
	TOK_OPERATOR,
	TOK_PLUS,
	TOK_MINUS,
	TOK_MUL,
	TOK_DIVIDE,
	TOK_MAX
}				t_toktype;

typedef enum	e_chr_class {
	CHR_ERROR,
	CHR_SP,
	CHR_DIGIT,
	CHR_OPERATOR,
	CHR_RSUB,
	CHR_LSUB,
	CHR_MAX
}				t_chr_class;

typedef struct		s_tokens {
	t_toktype		tok;
	char			*data;
}					t_tokens;

t_tokens	*get_sequence_token(char *s, int *i, t_toktype toktype, t_chr_class origin_class);
t_tokens	*get_token(char *s, int *i, t_toktype toktype, t_chr_class prev_class);
void		ignore_chr_class(char *s, int *i, t_chr_class chr_class);
int			is_opening_class(t_chr_class chr_class);
t_tokens	*save_token(char *s, int anchor, t_toktype toktype);
t_tokens	*tokenizer(char *s);
#endif
