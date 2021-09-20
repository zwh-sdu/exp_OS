src = mypipe.c
obj = mypipe.o
opt = -g -c

all:	mypipe
mypipe: $(obj)
	gcc $(obj) -l pthread -o mypipe
mypipe.o:$(src)
	gcc $(opt) $(src) 
clean:
	rm mypipe *.o           
