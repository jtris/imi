CC = cc
CFLAGS = -I../src/ -I. -ggdb -Wall -Wextra -pedantic
LDFLAGS = -lm

SRC_DIRS = . ../src/format/ ../src/util/ ../src/core
INDIVIDUAL_FILES = ../src/cli.c

SRC = $(shell find $(SRC_DIRS) -type f -name '*.c') $(INDIVIDUAL_FILES)
OUT = test

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)


