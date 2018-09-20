/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 13:19:09 by ollevche          #+#    #+#             */
/*   Updated: 2018/08/04 13:19:09 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*cut_word(char *line)
{
	int		len;
	char	*word;

	word = NULL;
	len = count_nwspaces(line);
	if (len > 0)
		word = ft_strndup(line, len); // strndup leak on len == 0
	return (word);
}

int		skip_wspaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	return (i);
}

int		count_nwspaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\t' && line[i] != ' ')
		i++;
	return (i);
}

bool	is_empty(char *line)
{
	int i;

	i = skip_wspaces(line);
	return (line[i] == 0);
}

void	trim_comments(char *line) // NOTE: check free func for the line
{
	char *comment_start;

	if (!line)
		return ;
	comment_start = ft_strchr(line, COMMENT_CHAR1);
	if (comment_start)
		*comment_start = '\0';
	comment_start = ft_strchr(line, COMMENT_CHAR2);
	if (comment_start)
		*comment_start = '\0';
}
