DIR = `basename $(CURDIR)`
NAME1 = 5a
NAME2 = $(p)
NAME3 = $(k)
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o

CFLAGS = -Wall -pedantic -std=c99  -O
LFLAGS = -Wall -pedantic -std=c99  -O

CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LFLAGS) $^


.PHONY: 5a
5a: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(p) $(k) $(fifo) $(in) $(out)
	diff -s $(in) $(out)
	rm $(fifo)

.PHONY: 5b
5b: $(EXEC2) $(EXEC3)
	mkfifo -m 644 $(fifo)
	xterm -title PRODUCENT -e ./$(EXEC2) $(fifo) $(in) &
	xterm -title KONSUMENT -e ./$(EXEC3) $(fifo) $(out)
	diff -s $(in) $(out)
	rm $(fifo)

.PHONY: clean

EXECS = $(EXEC1) $(EXEC2) $(EXEC3)

clean:                                                     
	rm -f *.o  *~ $(EXECS) producent konsument

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


