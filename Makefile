CC          =   c++
FLAGS       =   -Wall -Wextra -Werror -std=c++98 -Iinc
SRC_DIR     =   src
TEST_DIR    =   tests
OBJ_DIR     =   build

SRCS        =   checkExtension.cpp
TEST_SRCS   =   testCheckExtension.cpp

SRC_FILES   =   $(addprefix $(SRC_DIR)/, $(SRCS))
TEST_FILES  =   $(addprefix $(TEST_DIR)/, $(TEST_SRCS))

OBJS        =   $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_OBJS   =   $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_FILES))

NAME        =   webserv
TEST_NAME   =   tester

all:        $(NAME)

$(NAME):    $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

test:       $(TEST_OBJS) $(OBJS)
	@$(CC) $(TEST_OBJS) $(OBJS) -o $(TEST_NAME)
	@./$(TEST_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean:     clean
	@rm -f $(NAME) $(TEST_NAME)

re:         fclean all