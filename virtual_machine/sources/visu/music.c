/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 20:39:43 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/21 20:39:43 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		music_player(t_vdata *vdata)
{
	static int i = 0;

	noecho();
	if (vdata->music == 1 && i <= 3)
	{
		system("killall afplay");
		vdata->music = 0;
	}
	else if (vdata->music == 0)
	{
		if (i == 0)
			system("afplay media/La_Valse_OST_Ameli.mp3 &");
		else if (i == 1)
			system("afplay media/Hooked_On_A_Feeling.mp3 &");
		else if (i == 2)
			system("afplay media/Game_of_Thrones.mp3 &");
		else
			timeout(0);
		vdata->music = 1;
		i++;
	}
}
