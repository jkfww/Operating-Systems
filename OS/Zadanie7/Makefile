DIR = `basename $(CURDIR)`
NAME1 = cw7
NAME2 = producer
NAME3 = consumer
NAME4 = lib
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o

#do bibliotek
EXEC1s  = $(NAME1)s.x
EXEC1d1  = $(NAME1)d1.x
EXEC1d2  = $(NAME1)d2.x

LIB_NAME = MojeFunkcje
LIB_DIR = ./lib

# Biblioteka statyczna 
LIB_STAT = lib$(LIB_NAME).a
# Biblioteka dynamiczna
LIB_SHAR = lib$(LIB_NAME).so

# Pliki skompilowane wchodzace do biblioteki
LIB_OBJS = $(OBJS4)

HEADS = lib.h

CFLAGS = -Wall -pedantic -std=gnu99 -pthread  -O -fPIC
LFLAGS = -Wall -pedantic -std=gnu99 -pthread  -O 

CO = gcc
LD = $(CO)

# Program-archiwizer do tworzenia bibliotek statycznych
AR = ar
ARFLAGS = rsv

#-----------------------------------------------------------------------------------------------------------

%.o: %.c %.h
	$(CO) $(CFLAGS) $(HEADS) -c $< 

# Tworzenie bibliteki statycznej
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

# Tworzenie biblioteki dzielonej
$(LIB_SHAR): $(LIB_OBJS)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

#-----------------------------------------------------------------------------------------------------------

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC1s) $(EXEC1d1) $(EXEC1d2)

$(EXEC1): $(OBJS1) $(OBJS4) 
	$(LD) -o $@ $(LFLAGS) $(HEADS) $^ -lrt

$(EXEC2): $(OBJS2) $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $(HEADS) $^ -lrt

$(EXEC3): $(OBJS3) $(OBJS4) 
	$(LD) -o $@ $(LFLAGS)  $(HEADS) $^ -lrt

$(EXEC1s): $(OBJS1) $(OBJS4) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) $(HEADS) -lrt
      
$(EXEC1d1): $(OBJS1) $(OBJS4) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR) -lrt

$(EXEC1d2): $(OBJS1) $(OBJS4) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -lrt

#-----------------------------------------------------------------------------------------------------------

.PHONY: cw7s
cw7s: $(EXEC2) $(EXEC3) $(OBJS4) $(EXEC1s)
	./$(EXEC1s) $(p) $(c) $(in) $(out)
	diff -s $(in) $(out)

.PHONY: cw7d1
cw7d1: $(EXEC2) $(EXEC3) $(OBJS4) $(EXEC1d1)
	./$(EXEC1d1) $(p) $(c) $(in) $(out)
	diff -s $(in) $(out)

.PHONY: cw7d2
cw7d2: $(EXEC2) $(EXEC3) $(OBJS4) $(EXEC1d2) 
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1d2) $(p) $(c) $(in) $(out)
	diff -s $(in) $(out)

.PHONY: cw7
cw7:  $(EXEC2) $(EXEC3) $(OBJS4) $(EXEC1)
	./$(EXEC1) $(p) $(c) $(in) $(out)
	diff -s $(in) $(out)
	
	
.PHONY: clean

EXECS = $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC1s) $(EXEC1d1) $(EXEC1d2)

clean:                                                     
	rm -f *.o  *~ $(EXECS) $(HEADS).gch

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


