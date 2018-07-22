/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:50:01 by ollevche          #+#    #+#             */
/*   Updated: 2018/07/18 14:50:01 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_FUNCS_H
# define VM_FUNCS_H

# include "vm.h"

/*
**  main.c
*/

void	terminate();

/*
**  read_input.c
*/

t_champ	*read_input(int argc, char **args);
bool	read_champ(t_champ **champs, char *filename);


/*
**  validation.c
*/

bool	reading(t_champ **champs, int fd, char *filename);

/*
**  play_the_game.c
*/

t_champ	*play_the_game(t_champ *champs);


/*
**  util.c
*/

t_champ *new_champ(t_champ **champs);
void    free_champs();

#endif
