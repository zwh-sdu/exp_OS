srcs = mypsched.c
objs = mypsched.o
opts = -g -c
all:	psched
psched: $(objs)
	gcc $(objs) -o mypsched 
psched.o:$(srcs)
	gcc $(opts) $(srcs) 
clean:
	rm mypsched *.o

