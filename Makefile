# Makefile

CC := gcc
LD := gcc
CFLAGS := -Wall -Werror -Wextra -g -c -fsanitize=address,undefined -I./include
LDFLAGS := -lc -e _main -arch x86_64 -fsanitize=address,undefined

SRCDIR := src
OBJDIR := build
BINDIR := bin
SRCEXT := c

HDRS :=
SRCS := $(addprefix $(SRCDIR)/, main.c)
#SRCS := $(shell find -s $(SRCDIR) -name *.$(SRCEXT))
#OBJS := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%,$(SRC:.c=.o))
OBJS := $(patsubst $(SRCDIR)/%.$(SRCEXT), $(OBJDIR)/%.o, $(SRCS))
NAME := a.out


all : mkdirs $(NAME)

$(NAME) : $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $(BINDIR)/$@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

mkdirs :
	@if [[ ! -e $(OBJDIR) ]]; then mkdir $(OBJDIR); fi
	@if [[ ! -e $(BINDIR) ]]; then mkdir $(BINDIR); fi

.PNOHY : all clean fclean re mkdirs

clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -rf $(BINDIR)


re : fclean all
