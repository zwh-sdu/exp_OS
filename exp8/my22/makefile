
 
head = Dp.h
src =Dp.cpp
objs = Dp.o
opts =-w -g -c
all: Dp
Dp: $(objs)
	g++ $(objs) -o Dp
Dp.o: $(head) $(src)
	g++ $(opts) $(src)
clean:
	rm Dp *.o
