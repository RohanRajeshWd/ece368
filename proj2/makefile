
WARNING = 
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 


SRCS = main.c 
OBJS = $(SRCS:%.c=%.o)

huff: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o huff

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3

test1: huff
	./huff inputs/stone > output1
	//diff output1 expected/expected1

test2: huff
	./huff inputs/test2 > output2
	diff output2 expected/expected2

test3: huff
	./huff inputs/test3 > output3
	diff output3 expected/expected3

clean: # remove all machine generated files
	rm -f huff *.o output?



