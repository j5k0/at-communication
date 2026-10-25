TARGET_EXEC := at-communication
BUILD_DIR := ./build
SRCS := $(wildcard src/*.c src/*/*.c src/*/*/*.c)
OBJS := $(SRCS:src/%.c=build/%.o)
CC := gcc
CFLAGS += -Iinclude -Wall -Wextra -Iinclude -largp
.PHONY: all clean
all: $(TARGET_EXEC)
$(TARGET_EXEC): $(OBJS)
	$(CC) $^ -o $(TARGET_EXEC) $(CFLAGS)

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -r $(TARGET_EXEC) $(BUILD_DIR)