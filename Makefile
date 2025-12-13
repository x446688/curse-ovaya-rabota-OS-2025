CFLAGS = $(shell pkg-config --cflags --libs gtk+-3.0 openssl)
SRCDIR = src
OBJS = $(SRCDIR)/gui.o $(SRCDIR)/helper.o $(SRCDIR)/web.o
OUT = c2rn
all: $(OBJS)
	@echo "hey"
	cc -o $(OUT) $(OBJS) $(CFLAGS)
main.o: $(SRCDIR)/web.c $(SRCDIR)/helper.c $(SRCDIR)/gui.c 
	cc -c $(CFLAGS)
clean:
	rm $(OBJS) $(OUT)
install:
	test -d /opt/c2rn-gui && echo "Directory exists... Skipping..." || mkdir /opt/c2rn-gui
	cp $(OUT) /opt/c2rn-gui