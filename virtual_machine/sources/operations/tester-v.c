/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester-v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpozinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:55:55 by dpozinen          #+#    #+#             */
/*   Updated: 2018/08/29 11:55:55 by dpozinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_funcs.h"

# define OP g_optab[carry->op_code]

int		set_arg_types(int coding_byte, int *args, int size);
int		get_pc_move(int arg, int label_size);

void	print_carry_info(t_carry *carry, t_session *game)
{
	int		atypes[3];
	int		adv = 1;

	printf("ADV ");
	if (OP.codage)
	{
		int coding_byte = ft_byte_to_uint(0, 0, 0, MAPVAL(PC, 1));
		int valid = set_arg_types(coding_byte, atypes, OP.nb_params);
		while (valid--)
			adv += get_pc_move(atypes[valid], OP.label_size);
		adv += valid + OP.codage + 1;
	}
	else
		adv += get_pc_move(OP.params_type[0], OP.label_size);
	printf("%d ", adv);
	printf("(0x%04x -> 0x%04x) ", carry->pc, carry->pc + adv);
	int i = 0;
	while (i < adv)
	{
		printf("%02x ", MAP[move_pc(PC,i)]);
		i++;
	}
	printf("\n");
}

void	get_log_str(t_carry *carry, t_session *game, bool print_ctd)
{
	if (print_ctd)
		printf("Cycle to die is now %d\n", game->cycle_to_die);
	while (carry)
	{
		if (carry->inactive == 0 && (carry->op_code != 9 || !carry->carry))
			if (carry->op_code >= 1 && carry->op_code <= OP_COUNT)
				print_carry_info(carry, game);
		carry = carry->next;
	}
}
