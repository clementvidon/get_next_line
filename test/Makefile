NAME		= get_next_line

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -Wconversion
CFLAGS		:= $(CFLAGS)
CPPFLAGS	= -I..

SRCS		= main.c \
			  ../get_next_line.c \
			  ../get_next_line_utils.c
OBJS		:= $(SRCS:%.c=%.o)

RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

san_addr: CC := gcc
san_addr: CFLAGS := $(CFLAGS) -fsanitize=address,undefined,signed-integer-overflow
san_addr: $(NAME)

update:
	@git pull
	@git submodule update --init

norm:
	@norminette ../*.[ch] | grep -v "OK" || true

test:
	@bash gnltester.sh || true

malloc_test: $(OBJS)
	@clang -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) \
		-Lft_mallocator -lmallocator

.PHONY: all clean fclean re san_addr update norm test malloc_test
