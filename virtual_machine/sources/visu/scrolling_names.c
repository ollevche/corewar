/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrolling_names.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 00:28:31 by sivasysh          #+#    #+#             */
/*   Updated: 2018/08/21 00:28:32 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

static void		scroll_to_left(t_scroll_name *name)
{
	char sign_1;
	char sign_2;

	sign_1 = name->displayed_name[0];
	sign_2 = name->hidden_name[0];
	ft_strcpy(name->displayed_name, name->displayed_name + 1);
	ft_strcpy(name->hidden_name, name->hidden_name + 1);
	name->displayed_name[MAX_NAME_LEN - 1] = sign_2;
	name->hidden_name[name->hidden_len - 1] = sign_1;
	mvwprintw(name->window, 1, 1, name->displayed_name);
	refresh();
	wrefresh(name->window);
}

static void		scroll_to_right(t_scroll_name *name)
{
	char sign_1;
	char sign_2;

	sign_1 = name->displayed_name[MAX_NAME_LEN - 1];
	sign_2 = name->hidden_name[name->hidden_len - 1];
	ft_memmove(name->displayed_name + 1, name->displayed_name, MAX_NAME_LEN - 1);
	ft_memmove(name->hidden_name + 1, name->hidden_name, name->hidden_len - 1);
	name->displayed_name[0] = sign_2;
	name->hidden_name[0] = sign_1;
	mvwprintw(name->window, 1, 1, name->displayed_name);
	refresh();
	wrefresh(name->window);
}

static void		create_window_for_the_name(t_scroll_name *name, int x, int y)
{
	name->window = newwin(3, MAX_NAME_LEN + 2, x, y);
	nodelay(name->window, FALSE);
	//box(name->window, 0, ' ');
	wborder(name->window, 0, 0, 1, 1, 1, 1, 1, 1);
	
	wattron(name->window, COLOR_PAIR(14));
	nodelay(name->window, FALSE);
	mvwprintw(name->window, 1, 1, name->displayed_name);
	refresh();
	wrefresh(name->window);
}

void			scrolling_name(t_vdata *vdata, char *player_name, int x, int y)
{
	t_scroll_name *name;

	name = (t_scroll_name *)ft_memalloc(sizeof(t_scroll_name));
	if (vdata->scrolling_names)
		name->next = vdata->scrolling_names;
	vdata->scrolling_names = name;
	name->full_name = player_name;
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

void			scrolling_controls(t_vdata *vdata, int x, int y)
{
	t_scrolling_controls *sc;

	sc = (t_scrolling_controls *)ft_memalloc(sizeof(t_scrolling_controls));

	sc->seconds = 150;
	sc->window = newwin(6, 45, x, y);
	sc->direction = LEFT_D;
	sc->key = 0;
	wattron(sc->window, COLOR_PAIR(141));
	box(sc->window, 0, ' ');
	mvwprintw(sc->window, 2, 2, "[R] Scrolling direction: ");
	mvwprintw(sc->window, 3, 2, "[P] Scrolling type:");
	wattron(sc->window, COLOR_PAIR(141) | A_BOLD);
	mvwprintw(sc->window, 0, 11, "Name scrolling controls");
	mvwprintw(sc->window, 2, 3, "R");
	mvwprintw(sc->window, 3, 3, "P");
	mvwprintw(sc->window, 3, 22, "auto ");
	mvwprintw(sc->window, 2, 27, "%s", sc->direction == LEFT_D ? "to left " : "to right");
	wattroff(sc->window, A_BOLD);
	//nodelay(sc->window, FALSE);
	refresh();
	wrefresh(sc->window);
	vdata->scrolling_controls = sc;
}

static void		direction_key_listener(t_scrolling_controls *sc)
{
	if (sc->key == 114) // R key
	{
		sc->direction = (sc->direction == LEFT_D ? RIGHT_D : LEFT_D);
		wattron(sc->window, COLOR_PAIR(141) | A_BOLD);
		mvwprintw(sc->window, 2, 27, "%s", sc->direction == LEFT_D ? "to left " : "to right");
		wattroff(sc->window, A_BOLD);
		wrefresh(sc->window);
	}
}

static void		scroll_manually_keys_listener(t_scrolling_controls *sc, t_scroll_name *scrolling_names)
{
	t_scroll_name *name;
	if (sc->seconds != 150 && (sc->key == 46 || sc->key == 44)) // < > keys
	{
		name = scrolling_names;
		while (name)
		{
			sc->key == 46 ? scroll_to_right(name) : scroll_to_left(name);
			name = name->next;
		}
	}
}


static void		pause_key_listener(t_vdata *vdata)
{
	if (vdata->scrolling_controls->key == 112) // P key
	{
		if (vdata->scrolling_controls->seconds)
		{
			vdata->scrolling_controls->seconds = 0;
			wresize(vdata->scrolling_controls->window, 8, 45);
			box(vdata->scrolling_controls->window, 0, ' ');
			mvwprintw(vdata->scrolling_controls->window, 4, 2, "[<] Scroll manually to left");
			mvwprintw(vdata->scrolling_controls->window, 5, 2, "[>] Scroll manually to right");
			wattron(vdata->scrolling_controls->window, COLOR_PAIR(141) | A_BOLD);
			mvwprintw(vdata->scrolling_controls->window, 0, 11, "Name scrolling controls");
			mvwprintw(vdata->scrolling_controls->window, 3, 22, "manual");
			mvwprintw(vdata->scrolling_controls->window, 4, 3, "<");
			mvwprintw(vdata->scrolling_controls->window, 5, 3, ">");
			wattroff(vdata->scrolling_controls->window, A_BOLD);
			wrefresh(vdata->scrolling_controls->window);
		}
		else
		{
			vdata->scrolling_controls->seconds = 150;
			mvwprintw(vdata->scrolling_controls->window, 4, 2, "                            ");
			mvwprintw(vdata->scrolling_controls->window, 5, 2, "                            ");
			wborder(vdata->scrolling_controls->window, 1, 1, 1, 1, 1, 1, 1, 1);
			wrefresh(vdata->scrolling_controls->window);
			wresize(vdata->scrolling_controls->window, 6, 45);
			box(vdata->scrolling_controls->window, 0, ' ');
			wattron(vdata->scrolling_controls->window, COLOR_PAIR(141) | A_BOLD);
			mvwprintw(vdata->scrolling_controls->window, 0, 11, "Name scrolling controls");
			mvwprintw(vdata->scrolling_controls->window, 3, 22, "auto  ");
			wattroff(vdata->scrolling_controls->window, A_BOLD);
			wrefresh(vdata->scrolling_controls->window);
		}		
	}
}

 void			scrolling_of_the_names(t_vdata *vdata)
 {
	struct timeval time;
	gettimeofday(&time, NULL);
	t_scroll_name *name;
	if (vdata->scrolling_controls->seconds && ((time.tv_usec / 1000) - vdata->time) >= vdata->scrolling_controls->seconds)
	{
		name = vdata->scrolling_names;
		while (name)
		{
			if (vdata->scrolling_controls->direction)
				scroll_to_left(name);
			else
				scroll_to_right(name);
			name = name->next;
		}
		vdata->time = (time.tv_usec / 1000);
		wrefresh(vdata->scrolling_controls->window);
	}
	direction_key_listener(vdata->scrolling_controls);
	pause_key_listener(vdata);
	scroll_manually_keys_listener(vdata->scrolling_controls, vdata->scrolling_names);
}

void			scrolling_finalizing(t_vdata *vdata)
{
	t_scroll_name *name;

	name = vdata->scrolling_names;
	while (name)
	{
		ft_strdel(&name->displayed_name);
		ft_strdel(&name->hidden_name);
		delwin(name->window);
		name = name->next;
	}
	delwin(vdata->scrolling_controls->window);
}
