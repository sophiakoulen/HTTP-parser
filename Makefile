NAME = program
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

CLASSES = HTTPRequest HTTPHeaders
SRCS = main.cpp $(addsuffix .cpp, $(CLASSES)) utils.cpp
OBJS = $(SRCS:.cpp=.o)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
