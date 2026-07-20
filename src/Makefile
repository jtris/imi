
CC = cc
CFLAGS = -I. #-ggdb -Wall -Wextra -pedantic
LDFLAGS = 

SRC = main.c cli.c core/format_handler.c format/png/png_format.c format/png/png_chunks.c
OUT = imi

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)

