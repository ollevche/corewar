/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrolling_names2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:31:57 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/22 18:31:58 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	create_window_for_the_name(t_scroll_name *name, int x, int y)
{
	static int color = 1;

	name->window = newwin(1, MAX_NAME_LEN + 2 + 10, x, y);
	nodelay(name->window, FALSE);
	nodelay(name->window, FALSE);
	wattron(name->window, COLOR_PAIR(color));
	mvwprintw(name->window, 0, 0, "Player %d: %s", color, name->displayed_name);
	wattroff(name->window, COLOR_PAIR(color));
	wrefresh(name->window);
	color++;
}

void		scrolling_name(t_vdata *vdata, t_uchar *player_name, int x, int y)
{
	t_scroll_name *name;

	name = (t_scroll_name *)ft_memalloc(sizeof(t_scroll_name));
	if (vdata->scrolling_names)
		name->next = vdata->scrolling_names;
	vdata->scrolling_names = name;
	name->full_name = (char *)player_name;
	name->displayed_name = ft_strnew(MAX_NAME_LEN);
	if ((name->full_name_len = ft_strlen(name->full_name)) < MAX_NAME_LEN)
	{
		ft_memset(name->displayed_name, ' ', MAX_NAME_LEN);
		ft_strncpy(name->displayed_name, name->full_name, name->full_name_len);
		name->hidden_len = MAX_NAME_LEN;
		name->hidden_name = ft_strdup(name->displayed_name);
	}
	else
	{
		name->hidden_len = name->full_name_len - MAX_NAME_LEN + 1;
		name->hidden_name = ft_strnew(name->hidden_len);
		ft_strncpy(name->displayed_name, name->full_name, MAX_NAME_LEN);
		ft_strcpy(name->hidden_name, name->full_name + MAX_NAME_LEN);
		name->hidden_name[name->hidden_len - 1] = ' ';
	}
	create_window_for_the_name(name, x, y);
}

void		refresh_scroll_names(t_vdata *vdata)
{
	t_scroll_name	*name;
	int				color;

	color = vdata->total_champs;
	name = vdata->scrolling_names;
	while (color >= 1)
	{
		wattron(name->window, COLOR_PAIR(color + vdata->design * 10));
		mvwprintw(name->window, 0, 0,
			"Player %d: %s", color, name->displayed_name);
		wattroff(name->window, COLOR_PAIR(color + vdata->design * 10));
		wrefresh(name->window);
		name = name->next;
		color--;
	}
}

void		scrolling_controls(t_vdata *vdata, int x, int y)
{
	t_scrolling_controls *sc;

	sc = (t_scrolling_controls *)ft_memalloc(sizeof(t_scrolling_controls));
	sc->seconds = 150;
	sc->window = newwin(6, 45, x, y);
	sc->direction = LEFT_D;
	sc->key = 0;
	box(sc->window, 0, ' ');
	mvwprintw(sc->window, 2, 2, "[R] Scrolling direction: ");
	mvwprintw(sc->window, 3, 2, "[P] Scrolling type:");
	wattron(sc->window, COLOR_PAIR(GRAY) | A_BOLD);
	mvwprintw(sc->window, 0, 11, "Name scrolling controls");
	mvwprintw(sc->window, 2, 3, "R");
	mvwprintw(sc->window, 3, 3, "P");
	mvwprintw(sc->window, 3, 22, "auto ");
	mvwprintw(sc->window, 2, 27, "%s",
		sc->direction == LEFT_D ? "to left " : "to right");
	wattroff(sc->window, COLOR_PAIR(GRAY) | A_BOLD);
	refresh();
	wrefresh(sc->window);
	vdata->scrolling_controls = sc;
}

void		scrolling_finalizing(t_vdata *vdata)
{
	t_scroll_name *name;

	name = vdata->scrolling_names;
	while (name)
	{
		ft_strdel(&name->displayed_name);
		ft_strdel(&name->hidden_name);
		delwin(name->window);
		free(name);
		name = name->next;
	}
	delwin(vdata->scrolling_controls->window);
	free(vdata->scrolling_controls);
}
