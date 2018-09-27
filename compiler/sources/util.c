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

#define IS_COMMENT(C) (C == COMMENT_CHAR1 || C == COMMENT_CHAR2)

char	*cut_word(char *line)
{
	int		len;
	char	*word;

	word = NULL;
	len = count_nwspaces(line);
	if (len > 0)
		word = ft_strndup(line, len);
	return (word);
}

int		skip_wspaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && IS_WSPACE(line[i]))
		i++;
	return (i);
}

int		count_nwspaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && !IS_WSPACE(line[i]))
		i++;
	return (i);
}

bool	is_empty(char *line)
{
	int i;

	i = skip_wspaces(line);
	return (line[i] == 0);
}

void	trim_comments(char *line)
{
	char	*comstart;

	comstart = line;
	while (*comstart && *comstart != '"' && !IS_COMMENT(*comstart))
		comstart++;
	if (*comstart == '"')
	{
		comstart++;
		while (*comstart && *comstart != '"')
			comstart++;
	}
	while (*comstart && !IS_COMMENT(*comstart))
		comstart++;
	if (IS_COMMENT(*comstart))
		*comstart = '\0';
}
