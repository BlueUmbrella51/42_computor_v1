CC=clang++
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c++17
TARGET=computor
RAW=	computor\
		token
# HEADERS=
SRC=$(addsuffix .cpp, $(RAW))
OBJ=$(addsuffix .o, $(RAW))
OBJ_LST=$(addprefix $(OBJ_DIR)/, $(OBJ))
OBJ_DIR=objs
SRC_DIR=src

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJ_LST)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_LST)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp | $(OBJ_DIR) #$(HEADERS)
	@echo $@ $<
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re:	fclean all

debug: fclean
debug: CFLAGS += -g -fsanitize=address
debug: $(TARGET)
