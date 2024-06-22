# DENTAKU Makefile

TARGET := DENTAKU
SOURCES := source/main.c source/calculator.c source/graph.c source/ui.c
INCLUDES := -Isource
LIBS := -lctru -lcitro3d

# Directories
BUILD_DIR := build
GRAPHICS_DIR := gfx
ASSETS_DIR := assets

# Filenames
ICON := $(GRAPHICS_DIR)/icon.png
BANNER := $(GRAPHICS_DIR)/banner.png
BACKGROUND := $(GRAPHICS_DIR)/bg.bin
TADA_WAV := $(ASSETS_DIR)/tada.wav

# Output files
OUTPUT := $(TARGET).3dsx
CIA_OUTPUT := $(TARGET).cia

# Tools (assuming they are in PATH, adjust if necessary)
MAKEROM := makerom
3DSX_TOOL := 3dsxtool
SMDHTOOL := smdhtool
WAV_TO_BCSTM := wavtobcstm

# Flags
CFLAGS := -Wall

# Environment variables
export DEVKITPRO := /opt/devkitpro
export PATH := $(DEVKITPRO)/tools/bin:$(PATH)

all: check_libs $(OUTPUT) $(CIA_OUTPUT)

check_libs:
	@echo "Checking if libraries are installed..."
	@$(DEVKITPRO)/tools/bin/pkg-config --exists devkitARM ctrulib citro3d || \
	    (echo "Required libraries are not installed, installing..."; \
	    sudo $(DEVKITPRO)/update.sh && \
	    sudo $(DEVKITPRO)/pacman -S --noconfirm devkitARM ctrulib citro3d)

$(OUTPUT): $(TARGET).elf $(ICON) $(BACKGROUND)
	@echo "Generating $@..."
	@$(3DSX_TOOL) -s 0x2000000 -b "$(TARGET);$(TARGET);$(TARGET)" -i "$(ICON)" $< $@

$(CIA_OUTPUT): $(OUTPUT) $(BANNER) $(TADA_WAV)
	@echo "Generating $@..."
	@$(MAKEROM) -f cia -o $@ -target t -elf $< -rsf $(TARGET).rsf -icon $(ICON) -banner $(BANNER)

$(TARGET).elf: $(SOURCES)
	@echo "Building $@..."
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$@ $^ $(LIBS)

$(BANNER): $(BANNER).png
	@cp $< $@

$(ICON): $(ICON).png
	@cp $< $@

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(OUTPUT) $(CIA_OUTPUT)

.PHONY: all clean check_libs