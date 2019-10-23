/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/23 14:00:57 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_tokens	*save_token(char *s, int anchor, t_toktype toktype)
{
}

void	ignore_wspace(char *s, int *i)
{
	while (s[*i] && get_chr_class[(unsigned char)s[*i]] == CHR_SP)
		(*i)++;
}

t_toktype	get_operator(char *s, t_toktype toktype)
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

t_tokens	*get_token(char *s, int *i, t_toktype toktype, t_chr_class prev_class)
{
	t_chr_class chr_class = 0;
	int anchor = 0;
	
	chr_class = get_chr_class[(unsigned char)s[*i]];
	while (s[*i] && token_chr_rules[toktype][(chr_class = get_chr_class[(unsigned char)s[*i]])])
	{
		// 2 * 222
		//printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[*i], anchor);
		anchor++;
		(*i)++;
	}
	//printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[toktype], anchor, s + (*i - anchor));
	return (save_token(s + (*i - anchor), anchor, toktype));
}

t_tokens	*get_next_token(char *s)
{
	t_chr_class		chr_class = 0;
	t_toktype		toktype = 0;
	t_tokens		*token = NULL;
	static	int		i = 0;

	if (s[i] == '\0')
		return (save_token(NULL, 0, TOK_EOF));
	if (!(chr_class = get_chr_class[(unsigned char)s[i]]))
		return (NULL);
	if (chr_class == CHR_SP)
	{
		ignore_wspace(s, &i);
		//eat();
		return (get_next_token(s));
	}
	if (!(toktype = get_tok_type[chr_class]))
		return (NULL);
	else
		token = get_token(s, &i, toktype, chr_class);
	if (ABSTRACT_TOKEN[token->tok] && !(token->tok = get_true_toktype(token->data, token->tok)))
		return (NULL);
	return (token);
}

int main(int argc, char *argv[])
{
	t_tokens	*tok;
	
	(void)argc;
	tok = get_next_token(argv[1]);
	while (tok && tok->tok != TOK_EOF)
	{
		//printf("{%s, \"%s\"}\n", DEBUG_TOKEN[tok->tok], tok->data);
		tok = get_next_token(argv[1]);
	}
	if (!tok)
		printf("Syntax error\n");
	return 0;
}
