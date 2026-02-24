# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/23 11:42:39 by thodavid          #+#    #+#              #
#    Updated: 2026/02/24 11:42:53 by thodavid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#####
#Var#
#####
NAME		= PmergeMe
FLAGS		= -Wall -Wextra -Werror -std=c++98 -MMD -MP
DEP			= ($(OBJ):.o=.d)
SRCDIR		= src
OBJDIR		= obj
INCLUDES	= -I.

#####
#Src#
#####
SRC			= main PmergeMe
SRCS		= $(addprefix $(SRCDIR)/,$(addsuffix .cpp,$(SRC)))
OBJ			= $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

#######
#Rules#
#######
all: $(NAME)

$(NAME): $(OBJ)
		c++ $(FLAGS) $(OBJ) -o $(NAME)
		@echo "✅ ready ✅"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
		@mkdir -p $(dir $@)
		c++ $(FLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP)

clean:
		rm -rf $(OBJDIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
