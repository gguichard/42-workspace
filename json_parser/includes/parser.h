/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:11:49 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/16 13:38:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

typedef union u_json_value	t_json_value;
typedef struct s_json_token	t_json_token;

# define JSON_MAX_DEPTH 500

# define JSON_UNKNOWN 0
# define JSON_STRING 1
# define JSON_INTEGER 2
# define JSON_FLOAT 3
# define JSON_OBJECT 4
# define JSON_ARRAY 5
# define JSON_BOOLEAN 6
# define JSON_NULL 7

/*
** Union contenant la structure d'une valeur JSON.
**
** i represente un entier en cas de type JSON_INTEGER ou bien un une valeur
** vrai/faux en cas de token JSON_BOOLEAN.
**
** f represente un nombre a virgule flottante pour le type JSON_FLOAT.
**
** *str est, comme son nom l'indique, la chaine de caractere d'un token
** JSON_STRING.
**
** *child est utilise pour pointer vers le premier element d'un tableau/objet
** en cas de token JSON_OBJECT ou JSON_ARRAY.
**/

union			u_json_value
{
	int				i;
	double			f;
	char			*str;
	t_json_token	*child;
};

/*
** Structure contenant les informations d'un token JSON apres parsing.
**
** type permet de connaitre le type du token et donc de recuperer la bonne
** valeur depuis l'union u_json_value.
**
** key represente l'identifiant de la valeur. Elle peut etre NULL dans le
** cas d'un element de tableau.
**
** prev et next permettent de ce deplacer de la meme facon que dans une liste
** chainee pour les valeurs d'un JSON_OBJECT ou JSON_ARRAY.
**
** value stocke, comme son nom l'indique, la valeur du token. Cette derniere
** etant representee dans un union, il faut connaitre le type du token (via
** le champ type) afin de recuperer la valeur appropriee.
*/

struct			s_json_token
{
	int				type;
	char			*key;
	t_json_token	*prev;
	t_json_token	*next;
	t_json_value	value;
};

void			debug_lexemes(t_list *lst);
void			debug_tokens(t_json_token *token, int tab);

int				check_for_unknown_lexeme_type(t_list *lst);
int				expect_json_sep(t_list **lst, const char *sep);
void			*del_json_token(t_json_token *token);
void			del_json_token_childs(t_json_token *token);
t_json_token	*eat_json_lexemes(t_list **lst, int depth_level);
t_json_token	*read_json_key_pair(t_list **lst, int depth_level);

t_json_token	*parse_json(const char *data);

#endif
