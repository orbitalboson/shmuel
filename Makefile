CC=gcc
CFLAGS=-c
SOURCE_FOLDER=src
SOURCES=os.c utils.c
OBJECTS=$(SOURCES:.c=.o)
LIB=shmuel.a

all: $(LIB)

$(LIB): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

%.o: $(SOURCE_FOLDER)/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o