DIR = `basename $(CURDIR)`

NAME1 = cw4
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o

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


.PHONY: cw4
cw4: $(EXEC1) 
	./$(EXEC1) $(in) $(out)
	diff -s $(in) $(out)

	
.PHONY: clean

EXECS = $(EXEC1)

clean:                                                     
	rm -f *.o  *~ $(EXECS)

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


