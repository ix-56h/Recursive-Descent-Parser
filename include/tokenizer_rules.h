/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 03:35:54 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/23 17:34:30 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOK_RULES_H
# define FT_TOK_RULES_H
#include "tokenizer.h"
t_chr_class		get_chr_class[255] = {
	[' '] = CHR_SP,
	['\t'] = CHR_SP,

	['-'] = CHR_OPERATOR,
	['%'] = CHR_OPERATOR,
	['/'] = CHR_OPERATOR,
	['*'] = CHR_OPERATOR,
	['+'] = CHR_OPERATOR,
	['='] = CHR_OPERATOR,

	['('] = CHR_RSUB,
	[')'] = CHR_LSUB,

	['0' ... '9'] = CHR_DIGIT
};

t_toktype	token_chr_rules[TOK_MAX][CHR_MAX] = {
	[TOK_SP] = {[CHR_SP] = 1,},
	[TOK_DIGIT] = {[CHR_DIGIT] = 1,},
	[TOK_OPERATOR] = {[CHR_OPERATOR] = 1, },
	[TOK_LSUB] = {},
	[TOK_RSUB] = {},
};

t_toktype	get_tok_type[CHR_MAX] = {
	[CHR_SP] = TOK_SP,
	[CHR_DIGIT] = TOK_DIGIT,
	[CHR_RSUB] = TOK_RSUB,
	[CHR_LSUB] = TOK_LSUB,
	[CHR_OPERATOR] = TOK_OPERATOR
};

char	DEBUG_TOK[TOK_MAX][11] = {
	[TOK_SP] = "TOK_SP",
	[TOK_EQUAL] = "TOK_EQUAL",
	[TOK_LSUB] = "TOK_LSUB",
	[TOK_RSUB] = "TOK_RSUB",
	[TOK_EOF] = "TOK_EOF",
	[TOK_DIGIT] = "TOK_DIGIT",
	[TOK_PLUS] = "TOK_PLUS",
	[TOK_MINUS] = "TOK_MINUS",
	[TOK_MUL] = "TOK_MUL",
	[TOK_MOD] = "TOK_MOD",
	[TOK_DIVIDE] = "TOK_DIVIDE"
};
#endif
