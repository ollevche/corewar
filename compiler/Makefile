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

NAME	=	asm

FLAGS	=	-Wall -Werror -Wextra -I./headers -I$(LIBDIR)/headers

SRCDIR	=	sources/

OBJDIR	=	objects/

LIBDIR	=	../libft/

SRC		=	main.c read_sfile.c extract_header.c extract_instructions.c \
			struct_funcs.c util.c semantic.c semantic_deep.c to_bytecode.c \
			labels.c writing.c calculate_size.c show_err.c

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

sclean:
	@echo "removing $(NAME) object files"
	@rm -rf $(OBJ) $(OBJDIR)

clean:
	@make -C $(LIBDIR) clean
	@echo "removing $(NAME) object files"
	@rm -rf $(OBJ) $(OBJDIR)

sfclean: sclean
	@echo "removing $(NAME) binary"
	@rm -rf $(NAME)

fclean:
	@make -C $(LIBDIR) fclean
	@echo "removing $(NAME) object files"
	@rm -rf $(OBJ) $(OBJDIR)
	@echo "removing $(NAME) binary"
	@rm -rf $(NAME) $(LIB)

re: fclean $(NAME)

sre: sfclean $(NAME)
