NAME = flisb

# add1
SRCDIR0 = ./src/
SRCDIR1 = ./src/core/
SRCDIR2 = ./src/parse/

# add2
SRCDIR  = $(SRCDIR0)
SRCDIR += $(SRCDIR1)
SRCDIR += $(SRCDIR2)

# add3
SRCS  = $(wildcard $(SRCDIR0)*.cpp)
SRCS += $(wildcard $(SRCDIR1)*.cpp)
SRCS += $(wildcard $(SRCDIR2)*.cpp)

OBJDIR = ./obj/
OBJS = $(SRCS:%.c=$(OBJDIR)%.o)

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
# CFLAGS = -std=c++17

# $(NAME) : $(SRCS)
# 	$(CC) $(CFLAGS) $^ -o $@

all : $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

# add4
$(OBJDIR)%.o : $(SRCDIR0)%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)%.o : $(SRCDIR1)%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)%.o : $(SRCDIR2)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# -L<libdir> -l<lib-unit cut lib>
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

# ret(-1) cause make error.  ||: force ret(0)
test : all
	./$(NAME)||:

bonus : all

.PHONY: all fclean clean re test bonus
