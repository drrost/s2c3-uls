###############################################################################
#                             Editable options                                #
###############################################################################
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I./inc

# Folders
SRC=src
OBJ=obj

BINARY = libmx.a

CFILES = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)
OBJ_DIR = obj

###############################################################################

all: uninstall ${BINARY}

${BINARY}:
	@mkdir -p ${OBJ_DIR}
	@${CC} ${CFLAGS} ${CFILES} -c
	@mv *.o ${OBJ_DIR}
	@ar -rc ${BINARY} ${OBJ_DIR}/*.o
	@rm -f ${OBJ_DIR}/*.o
uninstall:
	@rm -rf ${BINARY}
clean:
	@rm -rf ${OBJ_DIR}
reinstall: all

###############################################################################
