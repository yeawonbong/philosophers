NAME = philo
BONUS_NAME = philo_bonus

SRCS =./philo.c\
./p_init.c\
./p_monitor.c\
./p_threadfunc.c\
./p_time.c\
./p_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = #-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
obj : $(OBJS)

$(OBJS) : $(SRCS)
	$(CC) -pthread $(CFLAGS) -c $(SRCS)

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJS)

re : fclean all