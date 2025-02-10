CC = gcc
CFLAGS = -Wall -Werror -g
BUILD_DIR = build

SRC = riscv.c memory.c decode.c execute.c
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
TARGET = riscv

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
