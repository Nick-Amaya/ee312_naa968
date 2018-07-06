
TARGET       := a2.bin
OBJECTS      := src/assignment2.o 
TEST_TARGET  := a2.test.bin 
TEST_OBJECTS := test/test.o test/a2i.o test/i2a.o

$(TARGET): $(OBJECTS)
	gcc -Wall -o $(TARGET) $(OBJECTS)

$(TEST_TARGET): $(TEST_OBJECTS)
	gcc -Wall -o $(TEST_TARGET) $(TEST_OBJECTS)

assignment2.o: src/assignment2.c
test.o: test/test.c
a2i.o: test/a2i.c
i2a.o: test/i2a.c

.PHONY: clean
clean:
	rm $(TARGET) $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)
