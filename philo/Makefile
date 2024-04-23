# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 15:19:54 by btan              #+#    #+#              #
#    Updated: 2024/04/24 02:48:24 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES = .

SRCS = philo_utils.c \
	   philo_status.c \
	   philo_take.c \
	   philo_actions.c \
	   main.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES)

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJECTS) $(NAME).a

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

debug-thread: CFLAGS += -g -fsanitize=thread
debug-thread: re

debug-address: CFLAGS += -g -fsanitize=address
debug-address: re

debug-tsan: debug-thread
	TSAN_OPTIONS=second_deadlock_stack=1 ./philo 5 800 200 200 5

drift: drift.c philo_utils.c philo_status.c philo_actions.c
	$(CC) drift.c philo_utils.c philo_status.c philo_actions.c -o drift -g

.PHONY: all clean fclean re
