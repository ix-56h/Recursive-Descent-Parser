/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 03:35:54 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/23 15:38:39 by niguinti         ###   ########.fr       */
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
};

t_toktype	get_tok_type[CHR_MAX] = {
	[CHR_SP] = TOK_SP,
	[CHR_DIGIT] = TOK_DIGIT,
	[CHR_RSUB] = TOK_RSUB,
	[CHR_LSUB] = TOK_LSUB,
	[CHR_OPERATOR] = TOK_OPERATOR
};
#endif
