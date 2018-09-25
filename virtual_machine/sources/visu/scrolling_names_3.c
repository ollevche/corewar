/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrolling_names3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:39:44 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/22 18:39:44 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	scroll_to_left(t_scroll_name *name, int color, int design)
{
	char sign_1;
	char sign_2;

	sign_1 = name->displayed_name[0];
	sign_2 = name->hidden_name[0];
	ft_strcpy(name->displayed_name, name->displayed_name + 1);
	ft_strcpy(name->hidden_name, name->hidden_name + 1);
	name->displayed_name[MAX_NAME_LEN - 1] = sign_2;
	name->hidden_name[name->hidden_len - 1] = sign_1;
	wattron(name->window, COLOR_PAIR(color + design * 10));
	mvwprintw(name->window, 0, 0, "Player %d: %s", color, name->displayed_name);
	wattroff(name->window, COLOR_PAIR(color + design * 10));
	wrefresh(name->window);
}

void	scroll_to_right(t_scroll_name *name, int color, int design)
{
	char sign_1;
	char sign_2;

	sign_1 = name->displayed_name[MAX_NAME_LEN - 1];
	sign_2 = name->hidden_name[name->hidden_len - 1];
	ft_memmove(name->displayed_name + 1,
		name->displayed_name, MAX_NAME_LEN - 1);
	ft_memmove(name->hidden_name + 1, name->hidden_name, name->hidden_len - 1);
	name->displayed_name[0] = sign_2;
	name->hidden_name[0] = sign_1;
	wattron(name->window, COLOR_PAIR(color + design * 10));
	mvwprintw(name->window, 0, 0, "Player %d: %s", color, name->displayed_name);
	wattroff(name->window, COLOR_PAIR(color + design * 10));
	wrefresh(name->window);
}

void	direction_key_listener(t_scrolling_controls *sc)
{
	if (sc->key == 114)
	{
		sc->direction = (sc->direction == LEFT_D ? RIGHT_D : LEFT_D);
		mvwprintw(sc->window, 2, 27, "%s",
			sc->direction == LEFT_D ? "to left " : "to right");
		wrefresh(sc->window);
	}
}

void	scroll_manually_keys_listener(
	t_scrolling_controls *sc, t_scroll_name
	*scrolling_names, int total_champs, int design)
{
	int				color;
	t_scroll_name	*name;

	color = total_champs;
	if (sc->seconds != 150 && (sc->key == 46 || sc->key == 44))
	{
		name = scrolling_names;
		while (name)
		{
			sc->key == 46 ?
			scroll_to_right(name, color, design) :
			scroll_to_left(name, color, design);
			name = name->next;
			color--;
		}
	}
}
