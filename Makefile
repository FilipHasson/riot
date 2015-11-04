# CIS*3250 Assignment 2 Makefile

CC      = gcc
CFLAGS  = -Wall -std=c99 -pedantic -g
LDFLAGS = -lncurses
INCLUDES = -Iinclude

BINDIR   = bin
SRCDIR   = src

SRC = $(SRCDIR)/*.c
RIOT_OBJ = riotExec.o riotMap.o riotUI.o riotUnits.o
TEST_OBJ = riotTesting.o riotMap.o riotUI.o riotUnits.o


default: riotLink testLink

compile: 
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRC) $(INCLUDES)

riotLink: compile
	$(CC) -o $(BINDIR)/riot $(RIOT_OBJ) $(LDFLAGS)

testLink: compile
	$(CC) -o $(BINDIR)/test $(TEST_OBJ) $(LDFLAGS)

clean:
	rm -r -f *.o bin/*