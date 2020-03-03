CFLAGS = -Wall
main:main.o cJSON.o
main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o
cJSON.o: cJSON.c 
	gcc $(CFLAGS) -c cJSON.c -o cJSON.o

clean:
	rm -rvf *.o
