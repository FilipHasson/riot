# CIS*3250 Assignment 2 Makefile

CC      = gcc
CFLAGS  = -Wall -std=c99 -pedantic -g
LDFLAGS = -lncursesw
INCLUDES = -Iinclude

BINDIR   = bin
SRCDIR   = src

SRC = $(SRCDIR)/*.c
RIOT_OBJ = riotExec.o riotIO.o riotMap.o riotUI.o riotUnits.o
TEST_OBJ =


default: riotLink

compile: 
	$(CC) $(CFLAGS) -c $(SRC) $(INCLUDES)

riotLink: compile
	$(CC) $(LDFLAGS) -o $(BINDIR)/riot $(RIOT_OBJ) $(LIBS)

testLink: compiple
	$(CC) $(LDFLAGS) -o $(BINDIR)/test $(TEST_OBJ) $(LIBS)

clean:
	@ rm -f *.o bin/*
