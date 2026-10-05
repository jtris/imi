CC = cc
CFLAGS = -I. -I../src/ -ggdb -Wall -Wextra -pedantic
LDFLAGS = -lm

SRC_DIRS = . ../src/format/ ../src/util/ ../src/core
SRC = $(shell find $(SRC_DIRS) -type f -name '*.c')
OUT = test

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)


