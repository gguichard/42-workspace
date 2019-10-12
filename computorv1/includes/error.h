/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:18:14 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/10 16:21:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "lexer.h"

int		print_lexical_errors_if_any(lexeme_list_t *lst);
void	print_parser_error(lexeme_list_t *lst, lexeme_t *err_node
	, const char *info);

#endif
