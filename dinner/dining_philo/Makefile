# Makefile
#
# It uses implicit rules to compile .c files using the
# values assigned to macros CC and CFLAGS
#

CC = gcc
CFLAGS = -g -Wall


thread: dinner.o
	gcc -o dinner dinner.o -lpthread

clean:
	rm -f *.o dinner 
	
