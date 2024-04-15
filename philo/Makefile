# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 15:19:54 by btan              #+#    #+#              #
#    Updated: 2024/04/15 16:47:36 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES = .

SRCS = philo_utils.c \
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

debug-thread: CFLAGS += -fsanitize=thread
debug-thread: re

debug-address: CFLAGS += -fsanitize=address
debug-address: re

.PHONY: all clean fclean re
