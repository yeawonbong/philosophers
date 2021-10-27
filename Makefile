NAME = philo.a
OUT = philo

BONUS_NAME = philo_bonus.a
BONUS_OUT = philo_bonus

SRCS =./philo.c\
./p_init.c\
./p_threadfunc.c\
./p_time.c\
./p_utils.c

OBJS = $(SRCS:.c=.o)

# RM = rm -f
CC = gcc -pthread
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	$(AR) $@ $(OBJS)


fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)

re : fclean allå