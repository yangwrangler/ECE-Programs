#################################################################################
# ECE 437 Operating System PA03 Makefile
# Professor: Dr. Shu
# Created by: Panayioti Kitsos, Ryan Vasek
# Date: September 28, 2017
#
# make all: compiles and links all files
# make test: runs executable for prob1
# make clean: cleans up .o and *~ files
#
################################################################################	
CC = gcc
#CFLAGS = -std=gnu99 -g -O -c
CFLAGS = -g -Wall -Werror -c
OBJ = main.o fib_seq.o

################################  Make All  ####################################

# Compiles all files
all: main fib_seq
	$(CC) $(OBJ) -o myfib

# Compiles object files
main: main.c
	$(CC) $(CFLAGS) $@.c

fib_seq: fib_seq.c
	$(CC) $(CFLAGS) $@.c

################################ Test ##########################################

test: myfib
	./myfib -F 3 -S 2

#############################  Clean  ##########################################

clean:
	$(RM) *.o *~ myfib* $(SO)
