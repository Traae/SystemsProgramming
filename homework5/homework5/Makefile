CC=gcc
DEPS = my_string.h
OBJS := main.o my_string.o

main: $(OBJS)
	$(CC) -o main *.o $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.s $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm -f main *.o
