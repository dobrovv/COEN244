CC 	= g++
CFLAGS 	= -Wall -std=c++11
SOURCES = graph.h 
TARGET = gtest

ifeq ($(OS), Windows_NT)
	TARGET 	= ${TARGET}.exe
endif 

all:
	${CC} ${CFLAGS} -o ${TARGET} ${SOURCES}

