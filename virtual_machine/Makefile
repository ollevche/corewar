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

#-Wall -Werror -Wextra 

NAME	=	corewar

FLAGS	=	-I./headers -I$(LIBDIR)/headers -g # DEL

SRCDIR	=	sources/

OBJDIR	=	objects/

LIBDIR	=	../libft/

OPDIR	=	operations/

VISUDIR =	visu/

SRC		=	main.c play_the_game.c read_input.c read_champ.c prepare.c \
			execution.c struct_funcs.c free_funcs.c \
			$(addprefix $(OPDIR), $(OP)) \
			$(addprefix $(VISUDIR), $(VISU))

OP		=	o_01_live.c o_02_ld.c o_03_st.c o_04_add.c o_05_sub.c o_06_and.c \
			o_07_or.c o_08_xor.c o_09_zjmp.c o_10_ldi.c o_11_sti.c o_12_fork.c \
			o_13_lld.c o_14_lldi.c o_15_lfork.c o_16_aff.c base_ops.c op_tools.c

VISU	=	lifecycle_methods.c playback_controls.c print.c scrolling_names.c \
			custom_cycle.c alert_windows.c terminal_size_changing.c

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
