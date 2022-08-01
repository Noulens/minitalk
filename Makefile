# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

DONE	=  	@echo "$(_BOLD)$(_GREEN)Compilation done !!! 👌$(_END)"

NAME_CLIENT	=	client

NAME_SERVER =	server

CFILES_CLIENT	=	./srcs_server/main.c\

CFILES_SERVER =	./srcs_client/main.c\

OBJECTS = 	$(CFILES:.c=.o)

LIB_PATH = 	libft/

CC = 		cc

CFLAGS =	-Wall -Wextra -Werror -g

all: subsystem $(NAME) # Make all

subsystem: # Make the libft first then the minilibx
	@echo "$(_BOLD)$(_IYELLOW)$(_PURPLE)Verifying libft status...$(_END)"
	make -C $(LIB_PATH) all
	@echo "$(_BOLD)$(_PURPLE)libft archive generated, nothing else to be done here$(_END)"

$(NAME): $(OBJECTS)
	@echo "$(_BOLD)$(_BLUE)fdf: all object files generated$(_END)"
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB_PATH)libft.a -o $(NAME)
	$(DONE)

clean: # Clean generated object files
	make -C $(LIB_PATH) clean
	rm -f $(OBJECTS)
	@echo "$(_BOLD)$(_YELLOW)All object files removed$(_END)"

fclean: clean # Clean generated object files and and targets
	make -C $(LIB_PATH) fclean
	rm -f $(NAME)
	@echo "$(_BOLD)$(_YELLOW)All generated files removed$(_END)"

re: fclean all

call: all clean # Clean generated object files then clean libft target and object files
	make -C $(LIB_PATH) fclean
	@echo "$(_BOLD)$(_GREEN)Compilation done, object files and archive removed 👌$(_END)"

.PHONY	: all clean fclean re call

.SILENT :
