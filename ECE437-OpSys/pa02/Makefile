#################################################################################
# ECE 437 Operating System PA02 Makefile
# Professor: Dr. Shu
# Created by: Panayioti Kitsos
# Date: September 13, 2017
# 
# Problem 2:
# 	$ make all
#	$ make simplemath
#
# Problem 3:
#	$ make all
#	$ make lib_a
#	$ make simpleone_a
#	$ ./simpleone_a
#
# Problem 3:
# 	$ make all
# 	$ make lib_so
#	$ make simpleone_so
#	$ ./simpleone_so
#
################################################################################	
CC = gcc
CFLAGS = -std=gnu99 -g -O -c
CSECFL = -fPIC -I -L
CFLAG3 = -shared
OBJ = simple_math.o my_add.o my_mul.o
LD = ld -r
RM = /bin/rm -f
A = libmymath.a
SO = libmymath.so
LIBS = -lmymath

################################  Make All  ####################################

# Compiles all files to PIC
all: simple_math my_add  my_mul

# The following build object files
simple_math: simple_math.c
	$(CC) $(CFLAGS) $@.c $(CSECFL)

my_add: my_add.c
	$(CC) $(CFLAGS) $@.c $(CSECFL)

my_mul: my_mul.c
	$(CC) $(CFLAGS) $@.c $(CSECFL)

##########################  Simplemath Executable  #############################

# Compiles simplemath executable file
simplemath: $(OBJ)
	$(CC) $(OBJ) -o $@

###########################  Static Math Library  ##############################

# Builds and populates static library (libmymath.a) with object files
lib_a: $(OBJ)
	ar -rcs $(A) my*.o

# Compile/link static library and create simpleone_a executable 
simpleone_a: $(OBJ)
	$(CC) -o $@ simple_math.c $(A)
	$(CC) -o $@ simple_math.c -L/nfs/user/p/pkitsos/Fall2017/ece437/hw2 $(LIBS)

#########################  Shared Math Library  ################################

# Create dynamic shared math library (libmymath.so)
lib_so: $(OBJ)
	$(CC) $(CFLAG3) -o $(SO) $(OBJ)

# Link and generate executable simpleone_so
simpleone_so: $(OBJ)
	$(CC) -o $@ simple_math.o $(SO)
	sudo mv $(SO) /usr/lib/
	sudo ldconfig

#############################  Clean  ##########################################

clean:
	$(RM) *.o simplem* simpleo* lib* $(SO)
