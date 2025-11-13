CFLAGS = $(shell pkg-config --cflags --libs gtk4)
OBJS = main.o
all: $(OBJS)
	@echo "hey"
	cc -o main $(OBJS) $(CFLAGS)
main.o: main.c
	cc -c main.c $(CFLAGS)
clean:
	rm $(OBJS)
