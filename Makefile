CC = gcc
OBJ_NAME = gsd
OBJS = Main.c update_status.c gsd.c parser/parser.c status.c
FLAGS = -lcurl -std=c99

all:
	$(CC) $(FLAGS) $(OBJS) -o $(OBJ_NAME) $$(pkg-config gtk+-2.0 libcurl --cflags --libs)
spanish:
	cp lang/spanish.h lang/lang.h
	$(CC) $(FLAGS) $(OBJS) -o $(OBJ_NAME) $$(pkg-config gtk+-2.0 libcurl --cflags --libs)
english:
	cp lang/english.h lang/lang.h
	$(CC) $(FLAGS) $(OBJS) -o $(OBJ_NAME) $$(pkg-config gtk+-2.0 libcurl --cflags --libs)
french:
	cp lang/french.h lang/lang.h
	$(CC) $(FLAGS) $(OBJS) -o $(OBJ_NAME) $$(pkg-config gtk+-2.0 libcurl --cflags --libs)
clean:
	rm $(OBJ_NAME)

