CC= 	gcc
EXE= 	crypto_lib

SRC_DIR = ./sources/
INC_DIR = ./headers/
OBJ_DIR = ./objs/

SRCS= $(wildcard $(SRC_DIR)*.c) $(EXE).c
_OBJS= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) 
OBJS= $(_OBJS:%.c=$(OBJ_DIR)%.o)

CFLAGS = -I$(INC_DIR) -Wall #-O3
CPPFLAGS = -lm -lgmp

PRGS = $(OBJS) $(EXE) 

.SUFFIXES: 
	
all: $(PRGS)

$(EXE): $(OBJS) # $(CC) $(CFLAGS) -c $@.c -o $@.o
	$(CC) $(CFLAGS) -o $@ $^ $(CPPFLAGS)


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)$(EXE).o: $(EXE).c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find ./objs/ -name "*.*" -exec rm -f {} ';'
	
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	-rm -rf $(PRGS)
