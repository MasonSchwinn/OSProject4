CC        = gcc -fopenmp

#
# Modify TOPDIR if you use your own include files and library files
#

PROGRAM   = hello			# name of the binary
SRCS      = omp.c		# source file
OBJS      = $(SRCS:.c=.o)		# object file

#
# Targets
#

default: all

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LDFLAGS)

clean:
	/bin/rm -f $(OBJS) $(PROGRAM)
