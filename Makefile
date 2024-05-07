SRCS			=	pipex.c	\
					path.c	\

INCLUDES		=	-Iincludes								\
					-Ilibft/includes

LD_FLAGS		=	-Llibft -lft -ltermcap

NAME			=	pipex
OBJS			=	$(addprefix srcs/, $(SRCS:.c=.o))

CC				=	clang
RM				=	@rm -f

LIBFT			=	libft/libft.a

FLAGS			=	-Wall -Werror -Wextra $(INCLUDES)#-fsanitize=address -g

.c.o:
					@$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):			$(LIBFT) start_message $(OBJS)
					@if [ "$?" = "start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

$(LIBFT):
					@make -s -C libft -f Makefile


all:				$(NAME)

bonus:				re

clean:
					@make -s -C libft -f Makefile clean
					@echo "\033[0;33mCleaning \033[1;31m$(NAME)\033[0;33m's objects\033[0m"
					$(RM) $(OBJS)

fclean:				clean
					@make -s -C libft -f Makefile fclean
					@echo "\033[0;33mRemoving \033[1;31m$(NAME)\033[0;33m.\033[0m"
					$(RM) $(NAME)

start_message:
					@echo "\033[0;33mMaking \033[1;31m$(NAME)\033[0;33m\t\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"

re:					fclean $(LIBFT) start_message $(OBJS)
					@if [ "$?" = "fclean start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

.PHONY:				all clean fclean re