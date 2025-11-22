CFLAGS = $(shell pkg-config --cflags --libs gtk4 openssl)
OBJS = gui.o helper.o web.o
all: $(OBJS)
	@echo "hey"
	cc -o main $(OBJS) $(CFLAGS)
main.o: web.c helper.c gui.c 
	cc -c  $(CFLAGS)
clean:
	rm $(OBJS)