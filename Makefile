CC = cc
CFLAGS = $(shell pkg-config --cflags --libs gtk+-3.0 openssl)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0 openssl)
SRCDIR = src
OBJS = $(SRCDIR)/gui.o $(SRCDIR)/main.o $(SRCDIR)/web.o
OUT = c2rn
all: $(OUT)
$(OUT): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
$(SRCDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/gui.h $(SRCDIR)/web.h
	$(CC) -c $(CFLAGS) -c $< -o $@
$(SRCDIR)/gui.o: $(SRCDIR)/gui.c $(SRCDIR)/gui.h
	$(CC) $(CFLAGS) -c $< -o $@
$(SRCDIR)/web.o: $(SRCDIR)/web.c $(SRCDIR)/web.h
	$(CC) -c $(CFLAGS) -c $< -o $@
clean:
	rm $(OBJS) $(OUT)
install:
	test -d /opt/c2rn-gui || mkdir /opt/c2rn-gui
	cp $(OUT) /opt/c2rn-gui
.PHONY: all clean install