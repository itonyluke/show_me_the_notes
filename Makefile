NAME									=	show

SOURCE_FILES							=	main.cpp \
											error_handler.cpp \
											term_cap.cpp \
											read_input_and_output_the_notes.cpp

SOURCE_FILES_DIR						=	source_files/

OBJECT_FILES_DIR						=	object_files/

INCLUDE_FILES_DIR						=	include_files/

SOURCE_CODE								=	$(addprefix $(SOURCE_FILES_DIR), $(SOURCE_FILES))

OBJECT_FILES							=	$(addprefix $(OBJECT_FILES_DIR), $(SOURCE_FILES:.cpp=.o))

COMPILER								=	clang++

REMOVE_DIRECTORY_ENTRIES				=	rm -rf

COMPILE_FLAGS							=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors -I

JIC_A_OUT								=	a.out

all:	$(NAME)

$(OBJECT_FILES_DIR):
										mkdir object_files

$(OBJECT_FILES_DIR)%.o:					$(SOURCE_FILES_DIR)%.cpp
										$(COMPILER) $(COMPILE_FLAGS) $(INCLUDE_FILES_DIR) -c $< -o $@

$(NAME):								$(OBJECT_FILES_DIR) $(OBJECT_FILES)
										$(COMPILER) $(OBJECT_FILES) -o $(NAME)

clean:
										$(REMOVE_DIRECTORY_ENTRIES) $(OBJECT_FILES_DIR)

fclean:									clean
										$(REMOVE_DIRECTORY_ENTRIES) $(NAME)

re:										fclean all

.PHONY:									all clean fclean re
