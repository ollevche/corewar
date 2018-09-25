/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_design.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivasysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 22:06:29 by sivasysh          #+#    #+#             */
/*   Updated: 2018/09/22 22:06:29 by sivasysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	design_1(void)
{
	init_color(1, 168 * 3, 33 * 3, 107 * 3);
	init_color(2, 247 * 3, 219 * 3, 105 * 3);
	init_color(3, 236 * 3, 27 * 3, 75 * 3);
	init_color(4, 46 * 3, 149 * 3, 152 * 3);
	init_color(11, 168 * 3 + 200, 33 * 3 + 200, 107 * 3 + 200);
	init_color(12, 247 * 3 + 200, 219 * 3 + 200, 105 * 3 + 200);
	init_color(13, 236 * 3 + 200, 27 * 3 + 200, 75 * 3 + 200);
	init_color(14, 46 * 3 + 200, 149 * 3 + 200, 152 * 3 + 200);
}

static void	design_2(void)
{
	init_color(21, 0, 500, 453);
	init_color(22, 256, 333, 470);
	init_color(23, 830, 673, 556);
	init_color(24, 136, 560, 570);
	init_color(31, 0 + 200, 500 + 200, 453 + 200);
	init_color(32, 256 + 200, 333 + 200, 470 + 200);
	init_color(33, 830 + 170, 673 + 170, 556 + 170);
	init_color(34, 136 + 200, 560 + 200, 570 + 200);
}

static void	design_3(void)
{
	init_color(41, 670, 503, 456);
	init_color(42, 443, 226, 220);
	init_color(43, 250, 186, 166);
	init_color(44, 746, 560, 510);
	init_color(51, 670 + 200, 503 + 200, 456 + 200);
	init_color(52, 443 + 200, 226 + 200, 220 + 200);
	init_color(53, 250 + 200, 186 + 200, 166 + 200);
	init_color(54, 746 + 200, 560 + 200, 510 + 200);
}

static void	design_4(void)
{
	init_color(61, 826, 590, 496);
	init_color(62, 820, 380, 426);
	init_color(63, 640, 360, 440);
	init_color(64, 360, 303, 410);
	init_color(71, 1000, 590 + 200, 496 + 200);
	init_color(72, 1000, 380 + 200, 426 + 200);
	init_color(73, 640 + 200, 360 + 200, 440 + 200);
	init_color(74, 360 + 200, 303 + 200, 410 + 200);
}

void		init_design(int design, int total_champs)
{
	int player;

	if (design == 0)
		design_1();
	else if (design == 2)
		design_2();
	else if (design == 4)
		design_3();
	else if (design == 6)
		design_4();
	player = 1;
	while (player <= total_champs)
	{
		init_pair(player + (design * 10), player + (design * 10),
			COLOR_BLACK);
		init_pair(player + (design + 1) * 10, player + (design + 1) * 10,
			COLOR_BLACK);
		player++;
	}
}
