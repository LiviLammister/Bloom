CC = gcc
OBJS = main.o moremath.o quad.o tri.o sphere.o v3.o
CFLAGS = -c -lm -Wall

Bloom : $(OBJS)
	$(CC) $(OBJS) -lm -o Bloom

main.o : main.c quad.h sphere.h v3.h
	$(CC) $(CFLAGS) main.c

moremath.o : moremath.c moremath.h
	$(CC) $(CFLAGS) moremath.c

quad.o : quad.c quad.h tri.h v3.h
	$(CC) $(CFLAGS) quad.c

sphere.o : sphere.c sphere.h v3.h
	$(CC) $(CFLAGS) sphere.c

tri.o : tri.c v3.h
	$(CC) $(CFLAGS) tri.c

v3.o : v3.c v3.h
	$(CC) $(CFLAGS) v3.c 

.PHONY : clean
clean :
	rm Bloom $(OBJS) *~
