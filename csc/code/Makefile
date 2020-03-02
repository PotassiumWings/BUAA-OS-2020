main.o: main.c fibo.o
	gcc -c main.c -o main.o -I ../include -lm

fibo.o: fibo.c
	gcc -c fibo.c -o fibo.o -I ../include -lm

clean:
	rm *.o
