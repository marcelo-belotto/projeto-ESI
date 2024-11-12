CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm -lcunit

SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(wildcard $(LIB_DIR)/*.h)

TARGET = $(BIN_DIR)/sistema_reservas
TEST_TARGET = $(BIN_DIR)/test_salas

# Add this at the beginning of your Makefile
.PHONY: fix-timestamps

fix-timestamps:
	@find . -type f -exec touch {} +

# Modify your 'all' target to include fix-timestamps
all: fix-timestamps $(TARGET)

# Modify your 'test' target to include fix-timestamps
test: fix-timestamps $(TEST_TARGET)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) main.o

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(TEST_DIR)/salas.test.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(TEST_DIR)/salas.test.o: $(TEST_DIR)/salas.test.c
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@