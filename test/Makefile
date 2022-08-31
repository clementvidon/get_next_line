# @file     Makefile
# @brief    Simple Makefile for C function tester.
# @author   clemedon (Clément Vidon)

NAME		= get_next_line

#------------------------------------------------#
# INGREDIENTS                                    #
#------------------------------------------------#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
# SRCS      source files
# OBJS      object files

CC			:= clang
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -I ..
SRCS		:= \
	main.c \
	../get_next_line.c \
	../get_next_line_utils.c
OBJS		:= $(SRCS:%.c=%.o)

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command
# CLS       clear the current line

RM			:= rm -rf
VALGRIND	:= valgrind -q --leak-check=yes --show-leak-kinds=all

CLS			:= \r\033[K

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       build all targets
# $(NAME)   build $(NAME) target
# clean     remove objects
# fclean    remove objects and binary
# re        remove objects and binary and rebuild all

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CLS)$(NAME) created."

%.o: %.c
	@echo -n "$(CLS)Building $(NAME)..."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

#------------------------------------------------#
#   CUSTOM RECIPES                               #
#------------------------------------------------#
# san           memory corruption debugging
# ansi          ANSI c89 compliance
# every         explore new warnings
# info          standard build output
# run           run the program

.PHONY: sana ansi everything info run

sana: CC		:= gcc
sana: RULE		:= sana
sana: CFLAGS	+= -g -fsanitize=address,undefined,signed-integer-overflow
sana: $(NAME)

ansi: CFLAGS	+= -W -Wcast-qual -Wcomma -Wconversion -Wsign-conversion -Wwrite-strings -pedantic -std=c89
ansi: RULE		:= ansi
ansi: $(NAME)

every: CFLAGS	+= -Weverything
every: RULE		:= everything
every: $(NAME)

info: fclean
	@make --dry-run | grep -v "echo.*\".*\"\|\[.*\]"

run: $(NAME)
	$(if $(p), @$(VALGRIND) ./$(NAME) $(p) || true, \
		@echo "$(CLS)Usage: make run p=\"<params>\"")
