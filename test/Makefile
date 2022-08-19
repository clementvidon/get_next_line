# @author   cvidon@42
# @brief    Makefile for C programs that does not require any dependency.

NAME		= get_next_line

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -Wconversion -Wsign-conversion -g
CPPFLAGS	= -I.. -Ilibft_42/include
SRCS		= main.c \
			  ../get_next_line.c \
			  ../get_next_line_utils.c \
			  ../ libft_42/src/str/ft_strchr.c \
			  ../ libft_42/src/str/ft_strlen.c \
			  ../ libft_42/src/str/ft_strdup.c \
			  ../ libft_42/src/str/ft_strjoin.c \
			  ../ libft_42/src/str/ft_substr.c \
			  ../get_next_line_utils.c
OBJS		:= $(SRCS:%.c=%.o)

#------------------------------------------------#
#	SHELL CMDS									 #
#------------------------------------------------#

RM			= rm -f
VALGRIND	= valgrind -q --leak-check=yes --show-leak-kinds=all
AV			= $(nullstring)

#------------------------------------------------#
#	RECIPES										 #
#------------------------------------------------#

.PHONY: all san_addr clean fclean re norm update malloc_test

all: $(NAME)

san_addr: CC := gcc
san_addr: CFLAGS := $(CFLAGS) -fsanitize=address,undefined,signed-integer-overflow
san_addr: $(NAME)

$(NAME): update $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)objects"

clean:
	@$(RM) $(OBJS) && $(ECHO)"$(R)removed$(END) objects\n" || true

fclean: clean
	@$(RM) $(NAME) && $(ECHO)"$(R)removed$(END) $(NAME)\n" || true

re : fclean all

norm:
	@norminette ../*.[ch]| grep -v "OK" || true
	@$(ECHO)"$(G)checked norm$(END)\n"

update:
	@git pull
	@git submodule update --init
	@$(ECHO)"$(G)updated$(END)\n"

malloc_test: $(OBJS)
	@clang -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) \
		-L ft_mallocator -lmallocator

run:
	@./$(NAME) $(AV) || true
valgrind_run:
	@$(VALGRIND) ./$(NAME) $(AV) || true

#------------------------------------------------#
#	STDOUT										 #
#------------------------------------------------#

R		= $(shell tput setaf 1)
G		= $(shell tput setaf 2)
Y		= $(shell tput setaf 3)
B		= $(shell tput setaf 4)
M		= $(shell tput setaf 5)
C		= $(shell tput setaf 6)
W		= $(shell tput setaf 7)
K		= $(shell tput setaf 8)
END		= $(shell tput sgr0)
ECHO	= echo -n "\r\033[K$(NAME): "
