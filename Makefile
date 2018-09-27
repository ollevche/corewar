#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ollevche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/27 14:27:40 by ollevche          #+#    #+#              #
#    Updated: 2018/09/27 14:27:40 by ollevche         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ASM = asm
ASMDIR = compiler/

VM = corewar
VMDIR = virtual_machine/

all: $(VM) $(ASM)

$(ASM):
	@make -C $(ASMDIR)
	@cp $(ASMDIR)$(ASM) ./
	@echo "copied $(ASM)"

$(VM):
	@make -C $(VMDIR)
	@cp $(VMDIR)$(VM) ./
	@echo "copied $(VM)"

clean:
	@make clean -C $(ASMDIR)
	@make clean -C $(VMDIR)

fclean: clean
	@make fclean -C $(ASMDIR)
	@make fclean -C $(VMDIR)
	@rm -rf $(ASM) $(VM)
	@echo "removed $(ASM) and $(VM) copies"

re: fclean all
