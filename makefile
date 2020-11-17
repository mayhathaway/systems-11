main: main.c
	gcc -o main main.c

run:
	./main

clean:
	rm o.out
	rm main
