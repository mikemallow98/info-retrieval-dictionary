TARGET_EXEC ?= dictionary

SRC_DIRS ?= ./src
BUILD_DIR ?= ./BUILD

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -o -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)

CC = g++



$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ 

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -w  -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p
