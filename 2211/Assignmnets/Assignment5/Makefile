CC = gcc
CFLAGS = -Wall -std=c11

SRCS = snackaroo.c snackaroo_dish.c snackaroo_driver.c
OBJS = $(SRCS:.c=.o)
TARGET = snackaroo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)