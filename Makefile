NAME	:=	ft_ls

###			###			COMPABILITY		###			###
OS		:=	$(shell uname)

###			###			COMPILER		###			###
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS	+=	-MMD
CFLAGS	+=	-g
# CFLAGS	+=	-fsanitize=address

###			###			SOURCES			###			###
VPATH	:=	src/ src/options src/error src/cleanup src/parsing
VPATH	+=	src/sorting src/printing

SRC_F	:=	$(shell find src -name "*.c")
SRC_F	:=	$(notdir $(SRC_F))

###			###			OBJECTS			###			###
OBJ_D	:=	./obj
OBJ_F	:=	$(patsubst %.c,$(OBJ_D)/%.o,$(SRC_F))
DEP_F	:=	$(patsubst %.c,$(OBJ_D)/%.d,$(SRC_F))

###			###			COLORS			###			###
RED		:=	\033[1;31m
GREEN	:=	\033[1;32m
YELL	:=	\033[1;33m
BLUE	:=	\033[1;34m
WHITE	:=	\033[0m

###			###			LIBRARIES		###			###
LIBFT_D	:=	./lib/libft
LIBFT_F	:=	$(LIBFT_D)/libft.a
LIBFT_U	:=	https://www.github.com/Alphacharge/mylibft

LSAN_D	:=	./lib/LeakSanitizer
LSAN_F	:=	$(LSAN_D)/liblsan.a
LSAN_U	:=	https://www.github.com/mhahnFr/LeakSanitizer

LIB		:=	-L $(LIBFT_D) -l ft

###			###			HEADER			###			###
INC_D	:=	./inc
INC_F	:=	-I $(INC_D) -I $(LIBFT_D)

#Linux/Mac Compability for Leaksanitizer
ifeq ($(OS), Darwin)
ifeq ($(shell test -d $(LSAN_D) && test -f $(LSAN_F) && echo exists), exists)
	INC_F	+=	-Wno-gnu-include-next -I $(LSAN_D)/include
	LIB		+=	-L $(LSAN_D) -llsan -lc++
endif
else ifeq ($(OS), Linux)
ifeq ($(shell test -d $(LSAN_D) && test -f $(LSAN_F) && echo exists), exists)
	INC_F	+=	-Wno-gnu-include-next -I $(LSAN_D)/include
	LIB		+=	-rdynamic -L $(LSAN_D) -llsan -ldl -lstdc++
endif
endif

###			###			COMPABILITY		###			###

###			###			RULES			###			###
#make lsan is downloading lsan if its not.
#every make will be with lsan until a clean occurs.

all: message $(LIBFT_F)
	@$(MAKE) -j $(NAME)

lsan: clean_lsan $(OBJ_D) $(LIBFT_F) $(LSAN_F)
	@$(MAKE) -j $(NAME)

gprof: CFLAGS += -pg
gprof: clean
	@$(MAKE) gprof -C $(LIBFT_D)
	@$(MAKE) $(NAME)
	./ft_ls -aR urdu
	gprof ./ft_ls gmon.out > analysis.txt

$(NAME): $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) $(INC_F) -o $(NAME) $(OBJ_F) $(LIB)

$(OBJ_D)/%.o: %.c
	$(CC) $(CFLAGS) $(INC_F) -c $< -o $@

-include $(DEP_F)

$(OBJ_D):
	@git config advice.detachedHead false
	@mkdir -p $@

$(LIBFT_F):
ifneq ($(shell test -d $(LIBFT_D) && echo exists), exists)
	@echo "$(GREEN)Clone libft ...$(WHITE)"
	@git clone -q --branch v1.0.3 --recurse-submodules $(LIBFT_U) $(LIBFT_D)
endif
	@$(MAKE) -j -C $(LIBFT_D)

$(LSAN_F):
ifneq ($(shell test -d $(LSAN_D) && echo exists), exists)
	@echo "$(GREEN)Clone LeakSanitizer ...$(WHITE)"
	@git clone -q --branch v1.4 --recursive $(LSAN_U) $(LSAN_D)
endif
	@echo "$(GREEN)Make LeakSanitizer ...$(WHITE)"
	@$(MAKE) -s -C $(LSAN_D)

message:
	@echo "$(BLUE)------------------------------------------------------------------------------------------"
	@echo "$(BLUE)|$(RED)             ________ _________        ___       ________                               $(BLUE)|"
	@echo "$(BLUE)|$(RED)            |\  _____\\\\\___   ___\     |\  \     |\   ____\                              $(BLUE)|"
	@echo "$(BLUE)|$(RED)            \ \  \__/\|___ \  \_|     \ \  \    \ \  \___|_                             $(BLUE)|"
	@echo "$(BLUE)|$(RED)             \ \   __\    \ \  \       \ \  \    \ \_____  \                            $(BLUE)|"
	@echo "$(BLUE)|$(RED)              \ \  \_|     \ \  \       \ \  \____\|____|\  \                           $(BLUE)|"
	@echo "$(BLUE)|$(RED)               \ \__\       \ \__\       \ \_______\____\_\  \                          $(BLUE)|"
	@echo "$(BLUE)|$(RED)                \|__|        \|__|        \|_______|\_________\                         $(BLUE)|"
	@echo "$(BLUE)|$(RED)                                                   \|_________|                         $(BLUE)|"
	@echo "$(BLUE)|                                                                                        $(BLUE)|"
	@echo "$(BLUE)|                                                                                        $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)   ________      ___    ___    $(YELL)  ________  ________  _______  _________  ________       $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)  |\   __  \    |\  \  /  /|   $(YELL) |\   __  \|\   __  \|\  ___ \|\___   ___\\\\\_____  \      $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)  \ \  \|\ /_   \ \  \/  / /   $(YELL) \ \  \|\  \ \  \|\ /\ \   __/\|___ \  \_|\|___/  /|     $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)   \ \   __  \   \ \    / /    $(YELL)  \ \   _  _\ \   __  \ \  \_|/__  \ \  \     /  / /     $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)    \ \  \|\  \   \/  /  /     $(YELL)   \ \  \\\\\  \\\\\ \  \|\  \ \  \_|\ \  \ \  \   /  /_/__    $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)     \ \_______\__/  / /       $(YELL)    \ \__\\\\\ _\\\\\ \_______\ \_______\  \ \__\ |\________\  $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)      \|_______|\___/ /        $(YELL)     \|__|\|__|\|_______|\|_______|   \|__|  \|_______|  $(BLUE)|"
	@echo "$(BLUE)|$(GREEN)               \|___|/         $(YELL)                                                         $(BLUE)|"
	@echo "$(BLUE)|                                                                                        $(BLUE)|"
	@echo "$(BLUE)------------------------------------------------------------------------------------------$(WHITE)"
	
clean_lsan:
	@rm -rf $(OBJ_D)

clean:
	@rm -rf $(OBJ_D)
	@rm -f $(LSAN_F)
	@make fclean -C $(LIBFT_D)

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)--->$(GREEN)Cleaning $(NAME) .....$(WHITE)"
	@echo "$(RED)All is cleaned$(WHITE)"

re: fclean all

bonus: all

.PHONY: all fclean clean re lsan bonus clean_lsan
