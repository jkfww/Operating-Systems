DIR = `basename $(CURDIR)`
NAME1 = serwer
NAME2 = client
NAME3 = lib

EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o
EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o

OBJS3 = $(NAME3).o

HEADS = lib.h

CFLAGS = -Wall -pedantic -std=c99 -O 
LFLAGS = -Wall -pedantic -std=c99 -O 

CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) $(HEADS) -c $< 

$(OBJS1): $(HEADS)
$(OBJS2): $(HEADS)
$(OBJS3): $(HEADS)

.PHONY: all
all: $(EXEC1) 


$(EXEC1): $(OBJS1) $(OBJS3)
	 $(LD) -o $@ $(LFLAGS) $(HEADS) $^ -lrt

$(EXEC2): $(OBJS2) $(OBJS3)
	 $(LD) -o $@ $(LFLAGS) $(HEADS) $^ -lrt



.PHONY: cw8
cw8: $(EXEC1) $(EXEC2)
	xterm -hold -title SERWER -e ./serwer.x &
	xterm -hold -title CLIENT1 -e ./client.x &
	xterm -hold -title CLIENT2 -e ./client.x &
	
	
.PHONY: clean

EXECS = $(EXEC1) $(EXEC2) 

clean:                                                     
	rm -f *.o  *~ $(EXECS) $(HEADS).gch

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


