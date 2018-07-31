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

FLAGS	=	-Wall -Werror -Wextra -I./headers -I$(LIBDIR)/headers -g

SRCDIR	=	sources/

OBJDIR	=	objects/

LIBDIR	=	../libft/

OPDIR	=	operations/

SRC		=	main.c play_the_game.c read_input.c validation.c preparation.c \
			execution.c struct_funcs.c free_funcs.c \
			$(addprefix $(OPDIR), $(OP))

OP		=	live_01.c

OBJ		=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

LIB		=	libftprintf.a

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBDIR)$(LIB)
	@echo "creating $(NAME) binary"
	@cp $(LIBDIR)$(LIB) ./
	@gcc -o $(NAME) $(OBJ) $(LIB) $(FLAGS)

$(OBJ): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "creating $(NAME) object files"
	@gcc -o $@ -c $< $(FLAGS)

$(LIBDIR)$(LIB):
	@make -C $(LIBDIR)

$(OBJDIR):
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)$(OPDIR)

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
