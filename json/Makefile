RULES=$(PROG).y $(PROG).l

CC = gcc
CCFLAGS = -std=c90
LIBS = -L/opt/homebrew/Cellar/flex/2.6.4_2/lib -lfl

$(PROG): $(RULES)
	bison -d $(PROG).y
	flex $(PROG).l
	$(CC) $(CCFLAGS) $(PROG).tab.c lex.yy.c -o $(PROG) $(LIBS)


clean: 
	rm -f $(PROG).tab.*

check: $(PROG)
	./$(PROG)

