dames: dames.o main.o
	gcc -o dames dames.o main.o
	mv *.o bin/
	mv dames bin/

test : test.o dames.o
	gcc -o test test.o dames.o
	mv *.o bin/
	mv test bin/

test.o: src/test.c
	gcc -c src/test.c

dames.o: src/dames.c src/dames.h
	gcc -c src/dames.c

main.o: src/main.c
	gcc -c src/main.c

clean :
	rm bin/*.o *~core