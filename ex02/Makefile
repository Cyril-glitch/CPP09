NAME = PmergeMe

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ_DIR = obj
BIN_DIR = bin

SRC = src/main.cpp 

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

VPATH = src

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re it val

it : $(NAME)
	./PmergeMe 9 8 7 6 5 4 3 2 1

3000 : $(NAME)
	./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(BIN_DIR)
	rm -rf $(NAME)

re: fclean all