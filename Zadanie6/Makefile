DIR = `basename $(CURDIR)`
NAME1 = cw6
NAME2 = potomny
NAME3 = funkcje
NAME4 = lib
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
HEADS = $(NAME4).h

CFLAGS = -Wall -pedantic -std=c99 -pthread -O
LFLAGS = -Wall -pedantic -std=c99 -pthread -O

CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) $(HEADS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) 


$(EXEC1): $(OBJS1) $(OBJS3) 
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(OBJS3)
	 $(LD) -o $@ $(LFLAGS) $^

.PHONY: cw6
cw6: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(pr) $(p) $(k)
	
	


.PHONY: clean

EXECS = $(EXEC1) $(EXEC2)

clean:                                                     
	rm -f *.o  *~ $(EXECS)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


