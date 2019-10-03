PROJ_NM_		=	FT_NM
PROJ_OTO		=	FT_OTOOL

NAME_NM_		=	ft_nm
NAME_OTO		=	ft_otool
NAMES___		=	$(NAME_NM_)	$(NAME_OTO)

NO_TO_BE		=	ON

DIR_OBJ_		=	objs
DIR_SRC_		=	srcs
DIR_INC_		=	includes

CC				=	gcc
FLAGS___		=	-Wall -Werror -Wextra -Wpadded
INCLUDES		=	-I $(DIR_INC_)

SRC_INC_		=	$(shell find $(DIR_INC_) -name '*.h')
SRC_____		=	$(shell find $(DIR_SRC_) -name '*.c')
SRC_REMO		=
DIRS_SRC		=	$(shell find $(DIR_SRC_) -type d)
DIRS_OBJ		=	$(subst $(DIR_SRC_),$(DIR_OBJ_),$(DIRS_SRC))
OBJ_____		=	$(subst $(DIR_SRC_),$(DIR_OBJ_),$(SRC_____:.c=.o))

# LEN_SRC_		=	$(subs $(sort $(foreach src,$(notdir $(SRC_____)),$(strip $(shell echo -n "$(src)" | wc -c))))
# #
# LEN_MAX			=	$(shell echo -e $(subst $(sp),'\n',$2) | sort $1 --key=1,1 -)


all: $(NAME_NM_) $(NAME_OTO)
ifeq ($(NO_TO_BE),OFF)
	@echo > /dev/null
endif

$(NAME_NM_): NAME = $(NAME_NM_)
$(NAME_NM_): PROJ = $(PROJ_NM_)

$(NAME_OTO): NAME = $(NAME_OTO)
$(NAME_OTO): PROJ = $(PROJ_OTO)

$(NAMES___): $(DIRS_OBJ) $(OBJ_____)
	@$(CC) -o $(NAME) $(INCLUDES) $(FLAGS___) $(OBJ_____)
	@printf "[$(PROJ)] $(NAME) compiled.\n"

$(DIR_OBJ_)/%.o: $(DIR_SRC_)/%.c $(SRC_INC_) Makefile
	@printf "[$(PROJ)] Compiling $(notdir $<) to $(notdir $@)            \n"
	@$(CC) $(FLAGS___) $(INCLUDES) -o $@ -c $<

$(DIRS_OBJ):
	@mkdir -p $@

fclean:
	@rm -rf $(DIR_OBJ_)
	@rm -rf $(NAMES___)

# if [[ -d "$(DIR_OBJ_NM_)" && ! -d "$(DIR_OBJ_OTO)" ]]; then	\
# 	printf "[$(PROJECT_NM)]";								\
# elif [[ -d "$(DIR_OBJ_OTO)" && ! -d "$(DIR_OBJ_NM_)" ]]; then		\
# 	printf "[$(PROJECT_NM)]";								\
# else														\
# 	printf "[ALL]";											\
# fi ;	\

#@rm -rf $(DIR_OBJ)
#@printf "[ALL] Obj removed.\n"

# clean:
# 	@rm -rf $(DIR_OBJ)
# #@printf "[ALL] Obj removed.\n"
#
# clean_utils:
# 	@rm -rf $(PATH_OBJ_UTILS)
#
# clean_nm: clean_utils
# 	@rm -rf $(PATH_OBJ_NM)
# #@printf "[$(PROJECT_NM)] Obj removed.\n"
#
# clean_otool: clean_utils
# 	@rm -rf $(PATH_OBJ_OTOOL)
# #@printf "[$(PROJECT_OTOOL)] Obj removed.\n"
#
# fclean: clean fclean_nm fclean_otool
#
# fclean_nm : clean_nm
# 	@rm -f $(NAME_NM)
# #@printf "[$(PROJECT_NM)] \"$(NAME_NM)\" removed.\n"
#
# fclean_otool : clean_otool
# 	@rm -f $(NAME_OTOOL)
# #@printf "[$(PROJECT_NM)] \"$(NAME_NM)\" removed.\n"
#
# re: fclean $(NAME)

.PHONY: all clean_nm clean_otool clean


# help:
# 	@printf "[$(PROJECT)] make \n"
# 	@printf "    		-- compile the project '$(NAME)'\n"
# 	@printf "  $(NAME)	-- compile the project '$(NAME)'\n"
# 	@printf "  clean	-- remove \'$(DIR_OBJ)\' and all \'.o\' files from it\n"
# 	@printf "  fclean	-- $(UND)clean$(RES) and remove '$(NAME)' and '$(LINK)'\n"
# 	@printf "  re		-- $(UND)fclean$(RES) then $(UND)make$(RES)\n"
