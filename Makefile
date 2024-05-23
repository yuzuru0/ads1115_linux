CC      = gcc
CFLAGS	= -g -O2 -Wall -I.
LDFLAGS =
LIBS    =
PROGRAM = ads1115
OBJS	= ads1115.c i2c_interface.c

all:$(PROGRAM)

$(PROGRAM):	$(OBJS)
			$(CC) $(OBJS) -o $(PROGRAM)

clean:; rm -f *.o $(PROGRAM)
