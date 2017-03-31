CFLAGS+= -pedantic -Wall -Werror -std=c99 -O3
LIBS+= -lm

program: main.c 
	${CC} main.c -o program ${CFLAGS} ${LIBS}
	
zip:
	zip hw04-us.zip main.c
	
clean:
	rm -f *.o
	rm -f program
	rm -f hw04-us.zip

.PHONY: zip clean