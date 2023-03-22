DIR = `basename $(CURDIR)`

NAME1 = 3a
NAME2 = 3b
NAME3 = 3c
NAME4 = ig
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o
EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o
EXEC3 = $(NAME3).x
OBJS3 = $(NAME3).o
EXEC4 = $(NAME4).x
OBJS4 = $(NAME4).o


CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	 $(LD) -o $@  $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	 $(LD) -o $@ $(LFLAGS) $^

.PHONY: 3a
3a: $(EXEC1) 
	./$(EXEC1) $(option) $(signr)

.PHONY: 3b
3b: $(EXEC2) $(EXEC1) 
	./$(EXEC2) $(option) $(signr)

.PHONY: 3c
3c: $(EXEC3) $(EXEC1) $(EXEC4)
	./$(EXEC3) $(option) $(signr)
	
.PHONY: clean

EXECS = $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

clean:                                                     
	rm -f *.o  *~ $(EXECS)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


