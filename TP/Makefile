CC = g++
CFLAGS = -std=c++17 -lstdc++fs -Wall
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o
HDRS = $(INC)/msgassert.h $(INC)/Celula.h $(INC)/ListaEncadeada.h $(INC)/IndiceInvertido.h $(INC)/Termo.h $(INC)/Hash.h $(INC)/Documento.h  
CFLAGS = -std=c++17 -Wall -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -g -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/main.o -c $(SRC)/main.cpp 
	
clear:
	rm $(EXE) $(OBJS)