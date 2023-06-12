NAME = program
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

CLASSES = HTTPRequest
SRCS = main.cpp $(addsuffix .cpp, $(CLASSES))
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
