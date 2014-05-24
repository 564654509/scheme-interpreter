
CC = gcc
CFLAG = -O3 -ansi -pedantic -std=c99 
HEADER = header.h
LDFLAG = -lgc -lpthread
OBJ = alloc.o boolean.o char.o control.o env.o eval.o global.o \
	  input.o interp.o list.o number.o output.o pair.o port.o  \
	  string.o symbol.o syntax.o system.o vector.o \
	  
all : alloc.o boolean.o char.o control.o env.o eval.o global.o  \
      input.o interp.o list.o number.o output.o pair.o port.o string.o  \
      symbol.o syntax.o system.o vector.o interp clean

interp : $(OBJ)
	$(CC) -o interp $(OBJ) $(LDFLAG)
alloc.o : alloc.c $(HEADER)
	$(CC) $(CFLAG) -c alloc.c
boolean.o  : boolean.c $(HEADER)
	$(CC) $(CFLAG) -c boolean.c
char.o : char.c $(HEADER)
	$(CC) $(CFLAG) -c char.c
control.o : control.c $(HEADER)
	$(CC) $(CFLAG) -c control.c
env.o : env.c $(HEADER)
	$(CC) $(CFLAG) -c env.c
eval.o : eval.c $(HEADER)
	$(CC) $(CFLAG) -c eval.c	
global.o : global.c $(HEADER)
	$(CC) $(CFLAG) -c global.c
input.o : input.c $(HEADER)
	$(CC) $(CFLAG) -c input.c
interp.o : interp.c $(HEADER)
	$(CC) $(CFLAG) -c interp.c
list.o : list.c $(HEADER)
	$(CC) $(CFLAG) -c list.c
number.o : number.c $(HEADER)
	$(CC) $(CFLAG) -c number.c
output.o : output.c $(HEADER)
	$(CC) $(CFLAG) -c output.c
pair.o : pair.c $(HEADER)
	$(CC) $(CFLAG) -c pair.c
port.o : port.c $(HEADER)
	$(CC) $(CFLAG) -c port.c
string.o : string.c $(HEADER)
	$(CC) $(CFLAG) -c string.c
symbol.o : symbol.c $(HEADER)
	$(CC) $(CFLAG) -c symbol.c
syntax.o : syntax.c $(HEADER)
	$(CC) $(CFLAG) -c syntax.c
system.o : system.c $(HEADER)
	$(CC) $(CFLAG) -c system.c
vector.o : vector.c $(HEADER)
	$(CC) $(CFLAG) -c vector.c
clean :
	rm -f *.o

