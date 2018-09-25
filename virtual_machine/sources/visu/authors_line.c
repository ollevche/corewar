/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authors_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 20:01:16 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/28 20:01:16 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	author_line_initializing(t_vdata *vdata)
{
	char *authors;
	char *adv;

	authors = "Sasha Levchenkov, Dariy Pozinenko, Vika Blokha, Serzh Ivasyshyn";
	adv = "*** Your advertisement could be here! Call +380(93)416-66-51 ***";
	vdata->authors = newwin(2, 195, 0, 0);
	ft_bzero(vdata->adv_line, AUTHOR_LEN);
	ft_memset(vdata->adv_line, ' ', AUTHOR_LEN - 1);
	ft_strncpy(vdata->adv_line +
		(AUTHOR_LEN - 1 - ft_strlen(adv)), adv, ft_strlen(adv));
	ft_bzero(vdata->author_line, AUTHOR_LEN);
	ft_memset(vdata->author_line, ' ', AUTHOR_LEN - 1);
	ft_strncpy(vdata->author_line +
		(AUTHOR_LEN - 1 - ft_strlen(authors)), authors, ft_strlen(authors));
	box(vdata->authors, 0, 0);
	mvwprintw(vdata->authors, 1, 3, "| ");
	mvwprintw(vdata->authors, 1, 190, " |");
	mvwprintw(vdata->authors, 1, 5, vdata->author_line);
	wrefresh(vdata->authors);
}

void	author_line_scrolling(t_vdata *vdata)
{
	char	letter;

	letter = vdata->author_line[0];
	ft_strcpy(vdata->author_line, vdata->author_line + 1);
	vdata->author_line[AUTHOR_LEN - 2] = letter;
	letter = vdata->adv_line[0];
	ft_strcpy(vdata->adv_line, vdata->adv_line + 1);
	vdata->adv_line[AUTHOR_LEN - 2] = letter;
	mvwprintw(vdata->authors, 1, 5,
		vdata->author_adv_switch ? vdata->adv_line : vdata->author_line);
	wrefresh(vdata->authors);
}
