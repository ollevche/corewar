/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_and_log.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 17:41:22 by ollevche          #+#    #+#             */
/*   Updated: 2018/09/10 17:41:23 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

void	display_contestants(t_champ *champs, t_arg *arg)
{
	if (arg->is_visual)
		return ;
	ft_printf("Introducing contestants...\n");
	while (champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		champs->id, champs->code_len, champs->name, champs->comment);
		champs = champs->next;
	}
}

void	display_winner(t_champ *winner, t_arg *arg)
{
	if (arg->is_visual)
		return ;
	ft_printf("Player %d (%s) won !\n", winner->id, winner->name);
}

void	display_usage(void)
{
	ft_printf("USAGE:\n\
\t./corewar [-log] [-dump CYCLE] [-n CHAMP_ID] CHAMP_NAMES [-v]\n\
FLAGS:\n\
\t[-log]\t\tshows log (cycles + PC movements)\n\
\t[-dump N]\tdumps memory after N cycles\n\
\t[-n N]\t\tsets N as the next champ id\n\
\t[-v]\t\tenables visualization mode\n");
	terminate(NULL);
}

void	log_cycles(t_session *game, t_arg *arg, bool game_over)
{
	if (!arg->log || arg->is_visual)
		return ;
	if (game->last_ctd && game->last_ctd == game->cycle - 1)
		ft_printf("Cycle to die is now %d\n", game->cycle_to_die);
	else if (game_over)
		return ;
	ft_printf("It is now cycle %d\n", game->cycle);
}

void	log_operation(t_session *game, int new_pc, int old_pc)
{
	int adv;
	int i;

	if (!game->arg->log || game->arg->is_visual)
		return ;
	ft_printf("ADV ");
	adv = new_pc - old_pc;
	if (adv < 0)
		adv += MEM_SIZE;
	ft_printf("%d ", adv);
	ft_printf("(0x%04x -> 0x%04x) ", old_pc, old_pc + adv);
	i = 0;
	while (i < adv)
	{
		ft_printf("%02x ", MAP[move_pc(old_pc, i)]);
		i++;
	}
	ft_printf("\n");
}
