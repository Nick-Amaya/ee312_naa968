
TARGET       := a2.bin
OBJECTS      := src/app/i2a.o src/app/a2i.o src/app/app.o
TEST_TARGET  := a2.test.bin 
TEST_OBJECTS := test/a2i.o test/i2a.o test/test.o 
INCLUDES     := -I"$(shell pwd)/inc"
GCC_FLAGS    := -Wall -Wextra -ggdb $(INCLUDES)

all: build run
test: build-test run-test

build: $(OBJECTS)
	gcc $(GCC_FLAGS) -o $(TARGET) $(OBJECTS) src/assignment-2.o

run: $(TARGET)
	./$(TARGET)

build-test: $(OBJECTS) $(TEST_OBJECTS)
	gcc $(GCC_FLAGS) -o $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)

run-test:
	./$(TEST_TARGET)

# -c Flag: Compile but do not link! Only want to link in the last step.
src/assignment-2.o: src/assignment-2.c
	gcc $(GCC_FLAGS) -c -o $@ $^

test/test.o: test/test.c
	gcc $(GCC_FLAGS) -c -o $@ $^

test/a2i.o: test/a2i.c
	gcc $(GCC_FLAGS) -c -o $@ $^

test/i2a.o: test/i2a.c
	gcc $(GCC_FLAGS) -c -o $@ $^

src/app/app.o: src/app/app.c
	gcc $(GCC_FLAGS) -c -o $@ $^

src/app/a2i.o: src/app/a2i.c
	gcc $(GCC_FLAGS) -c -o $@ $^

src/app/i2a.o: src/app/i2a.c
	gcc $(GCC_FLAGS) -c -o $@ $^

.PHONY: clean
clean:
	$(RM) $(TARGET) $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)
