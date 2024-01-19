
CC = gcc
CFLAGS = -std=c90
LIBS = -L/opt/homebrew/Cellar/flex/2.6.4_2/lib -lfl

json: scanner.l
	flex scanner.l
	$(CC) $(CFLAGS) lex.yy.c -o json $(LIBS)

clean: 
	rm -f lex.yy.c json

check: json
	./json < tests/step1/$(DATA).json

