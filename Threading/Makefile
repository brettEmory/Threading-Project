CC=gcc
CFLAGS=-std=c99 -pthread
LIBS=-lpthread
TARGET1=createThreads
TARGET2=parallel1
TARGET3=parallel2
TARGET4=parallel3
ZIP_FILE=lab3.zip

# The 'all' target will build all programs
all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

$(TARGET1): $(TARGET1).c
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c $(LIBS)

$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).c $(LIBS)

$(TARGET3): $(TARGET3).c
	$(CC) $(CFLAGS) -o $(TARGET3) $(TARGET3).c $(LIBS)

$(TARGET4): $(TARGET4).c
	$(CC) $(CFLAGS) -o $(TARGET4) $(TARGET4).c $(LIBS)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

# You can also add a run target for convenience
run1: $(TARGET1)
	./$(TARGET1) > output_createThreads.txt

run2: $(TARGET2)
	./$(TARGET2) > output_parallel1.txt

run3: $(TARGET3)
	./$(TARGET3) > output_parallel2.txt

run4: $(TARGET4)
	./$(TARGET4) > output_parallel3.txt
zip:
	zip $(ZIP_FILE) $(TARGET1).c $(TARGET2).c $(TARGET3).c $(TARGET4).c Makefile README

