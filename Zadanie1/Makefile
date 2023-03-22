DIR = `basename $(CURDIR)`

NAME1 = SOcw1
NAME2 = SOcw2
NAME3 = SOcw3
NAME4 = SOcw4
NAME5 = SOcw5
NAME6 = wypisz

EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o
EXEC4 = $(NAME4)
OBJS4 = $(NAME4).o
EXEC5 = $(NAME5)
OBJS5 = $(NAME5).o
WYPISZ = $(NAME6).c

HEADS = biblioteka.h

CFLAGS = -Wall  -O
LFLAGS = -Wall  -O

CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) $(WYPISZ) $(HEADS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(WYPISZ) $(HEADS) $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(WYPISZ) $(HEADS) $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(WYPISZ) $(HEADS) $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	 $(LD) -o $@ $(WYPISZ) $(HEADS) $(LFLAGS) $^

$(EXEC5): $(OBJS5)
	 $(LD) -o $@ $(WYPISZ) $(HEADS) $(LFLAGS) $^
	 
.PHONY: 1a
1a: $(EXEC1)
	./$(EXEC1)
.PHONY: 1b
1b: $(EXEC2)
	./$(EXEC2)
.PHONY: 1c
1c: $(EXEC3)
	./$(EXEC3)
.PHONY: 1d
1d: $(EXEC4)
	./$(EXEC4)
.PHONY: 1e
1e: $(EXEC5)
	./$(EXEC5)
	
.PHONY: clean

EXECS = $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
clean:                                                     
	rm -f *.o  *~ $(EXECS)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

