#################################################################################
# ECE 437 Operating System PA03 Makefile
# Professor: Dr. Shu
# Created by: Panayioti Kitsos, Ryan Vasek
# Date: September 28, 2017
#
# Problem 1:
# 	make all: compiles and links all files
# 	make test1: runs executable for prob1 (n=6 m=6)
# 	make test2: runs executable for prob1 (n=6 m=3)
# 	make clean: cleans up .o and *~ files
#
# 	Options:
#		-F => nth sequence
#		-S => computing threshold
#
# Problem 2:
# 	make signals: compiles executable signals
# 	make test3: run executable (signals) for prob2
# 	make clean: cleans up .o and *~ files
#
################################################################################	

CC = gcc
CFLAGS = -g -Wall -Werror -c
CFLAG3 = -g -Wall -Werror -o
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

signals: signals.c
	$(CC) $@.c$ (CFLAG3) signals

################################ Test ##########################################

test1: myfib
	./myfib -F 6 -S 6

test2: myfib
	./myfib -F 6 -S 3

test3: signals
	./sigals | yes

#############################  Clean  ##########################################

clean:
	$(RM) *.o *~ myfib* $(SO)
