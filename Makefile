# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/11/07 02:01:27 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_LEM_IPC	=	lemipc

NAME		=   lemipc
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc
FLAGS_O		= -Wall -Wextra -Werror

SRCDIR_LEM_IPC		=	srcs/
OBJDIR_LEM_IPC		=	objs/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_LEM_IPC	=	\
					main.c				\
					segment.c			\
					semaphore.c			\
					lemipc.c			\
					utils/ipc.c			\
					utils/number.c		\
					map.c				\
					player.c			\
					team.c				\
					lists/teams.c		\

SRCS_LEM_IPC			=	$(addprefix $(SRCDIR_LEM_IPC), $(SRCBASE_LEM_IPC))
OBJS_LEM_IPC			=	$(addprefix $(OBJDIR_LEM_IPC), $(SRCBASE_LEM_IPC:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_LEM_IPC) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make re -C libft/ &&														\
		make LEM_IPC && 																\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";				\
	fi

$(OBJDIR_LEM_IPC):
	mkdir -p $(OBJDIR_LEM_IPC)
	mkdir -p $(dir $(OBJS_LEM_IPC))

$(OBJDIR_LEM_IPC)%.o : $(SRCDIR_LEM_IPC)%.c | $(OBJDIR_LEM_IPC)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

LEM_IPC: $(OBJDIR_LEM_IPC) $(OBJS_LEM_IPC)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_LEM_IPC) $(OBJS_LEM_IPC) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_LEM_IPC)"

clean:
	@rm -rf $(OBJDIR_LEM_IPC)
	@make -C $(LIBFT_DIR) clean
	echo "\r\033[38;5;124m📕  CLEAN $(OBJDIR_LEM_IPC)\033[0m\033[K";

fclean:		clean
	@rm -rf $(NAME_LEM_IPC)
	@make -C $(LIBFT_DIR) fclean
	echo "\r\033[38;5;124m📕  FCLEAN $(NAME_LEM_IPC)\033[0m\033[K";

-include $(OBJS:.o=.d)
