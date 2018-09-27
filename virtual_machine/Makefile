#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ollevche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 17:49:31 by ollevche          #+#    #+#              #
#    Updated: 2018/04/23 17:49:32 by ollevche         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	corewar

FLAGS	=	-I./headers -I$(LIBDIR)/headers -Wall -Werror -Wextra

SRCDIR	=	sources/

OBJDIR	=	objects/

LIBDIR	=	../libft/

OPDIR	=	operations/

VISUDIR =	visu/

SRC		=	main.c play_the_game.c read_input.c read_champ.c prepare.c \
			execution.c struct_funcs.c free_funcs.c display_and_log.c \
			util.c \
			$(addprefix $(OPDIR), $(OP)) \
			$(addprefix $(VISUDIR), $(VISU))

OP		=	o_01_live.c o_02_ld.c o_03_st.c o_04_add.c o_05_sub.c o_06_and.c \
			o_07_or.c o_08_xor.c o_09_zjmp.c o_10_ldi.c o_11_sti.c o_12_fork.c \
			o_13_lld.c o_14_lldi.c o_15_lfork.c o_16_aff.c base_ops.c \
			op_tools.c op_tools_more.c

VISU	=	lifecycle_methods.c \
			playback_controls.c \
			init_design.c \
			print_1.c \
			print_2.c \
			print_3.c \
			custom_cycle.c \
			authors_line.c players_line.c \
			alert_windows_1.c \
			alert_windows_2.c \
			lives_bar_1.c \
			lives_bar_2.c \
			scrolling_names_1.c \
			scrolling_names_2.c \
			scrolling_names_3.c \
			rerender_terminal_1.c \
			rerender_terminal_2.c \
			console/console_commands.c \
			console/console_clock.c \
			console/console_controls.c \
			console/console_drawing.c \
			console/console_input.c \
			console/console_keys_1.c \
			console/console_keys_2.c \
			console/console_lifecycle_methods.c \
			console/console_management_1.c \
			console/console_management_2.c \
			console/console_rerender.c \
			default_settings.c \
			music.c

OBJ		=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

LIB		=	libftprintf.a

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBDIR)$(LIB)
	@echo "creating $(NAME) binary"
	@cp $(LIBDIR)$(LIB) ./
	@gcc -o $(NAME) $(OBJ) $(LIB) $(FLAGS) -lncurses

$(OBJ): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "creating $(NAME) object files"
	@gcc -o $@ -c $< $(FLAGS)

$(LIBDIR)$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR):
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)$(OPDIR)
	@mkdir $(OBJDIR)$(VISUDIR)
	@mkdir $(OBJDIR)$(VISUDIR)console

clean:
	@make -C $(LIBDIR) clean
	@echo "removing $(NAME) object files"
	@rm -rf $(OBJ) $(OBJDIR)

fclean:
	@make -C $(LIBDIR) fclean
	@echo "removing $(NAME) object files"
	@rm -rf $(OBJ) $(OBJDIR)
	@echo "removing $(NAME) binary"
	@rm -rf $(NAME) $(LIB)

re: fclean $(NAME)

corclean:
	@echo "removing $(NAME) object files"
	@rm -rf $(OBJ) $(OBJDIR)

recor: corclean $(NAME)
