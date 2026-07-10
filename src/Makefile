
CC = cc
CFLAGS = -ggdb -Wall -Wextra -pedantic
LDFLAGS = 

SRC = main.c cli.c
OUT = imi

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)

