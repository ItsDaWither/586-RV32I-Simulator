CC = gcc
CFLAGS = -Wall -Werror -g
BUILD_DIR = build

SRC = src/riscv.c src/memory.c src/decode.c src/execute.c
OBJ = $(SRC:src/%.c=$(BUILD_DIR)/%.o)
TARGET = riscv

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
