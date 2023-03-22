DIR = `basename $(CURDIR)`

NAME1 = socw2
NAME2 = $(argument)
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o


CFLAGS = -Wall  -O
LFLAGS = -Wall  -O

CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	 $(LD) -o $@  $(LFLAGS) $^

.PHONY: cw2
cw2: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2)

	
.PHONY: clean

EXECS = $(EXEC1) $(EXEC2) 

clean:                                                     
	rm -f *.o  *~ $(EXECS)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


