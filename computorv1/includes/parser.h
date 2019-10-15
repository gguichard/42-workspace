/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:51:09 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/14 13:17:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "lexer.h"

# define JUMP_NO_ERROR 0
# define JUMP_PARSE_ERROR 1
# define JUMP_UNEXPECTED 2

ast_node_t	*parse_lexemes(lexeme_list_t *lst);

#endif
