MCU = atmega328p
F_CPU = 8000000UL
TARGET_NAME = firmware

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

PROG = usbasp
PORT = /dev/ttyUSB0
BAUD = 115200

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INC_DIR) -Os -Wall -std=c99

all: $(TARGET).hex

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	@echo "Linking $@..."
	@$(CC) $(CFLAGS) $^ -o $@

$(TARGET).hex: $(TARGET).elf
	@echo "Generating Hex $@..."
	@$(OBJCOPY) -O ihex -R.eeprom $< $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

flash: $(TARGET).hex
	@echo "Flashing with $(PROG)..."
	$(AVRDUDE) -c $(PROG) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<:i

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: all flash clean
