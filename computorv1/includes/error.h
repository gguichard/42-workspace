/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:18:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/14 11:15:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <setjmp.h>
# include "lexer.h"

typedef struct
{
	const char	*message;
	jmp_buf		buf;
} jmp_error_t;

int		print_lexical_errors_if_any(lexeme_list_t *lst);
void	print_parser_error(lexeme_list_t *lst, lexeme_t *err_node
	, const char *info);

#endif
