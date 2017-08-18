CC=gcc
CFLAGS=-g -c
INCLUDE_DIR=`pwd`
INCLUDE_FLAGS=-I $(INCLUDE_DIR)
TARGET=notebook
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`

$(TARGET):*.o
	$(CC) -o $(TARGET) *.o $(GTK_FLAGS) 

*.o:*.c
	$(CC) $(CFLAGS) *.c $(GTK_FLAGS) 

clean:
	rm -rf *.o $(TARGET)


