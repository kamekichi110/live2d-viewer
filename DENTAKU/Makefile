# 3DS homebrew Makefile for DENTAKU

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

# Tools
MAKEROM := makerom
3DSX_TOOL := 3dsxtool
SMDHTOOL := smdhtool
WAV_TO_BCSTM := wavtobcstm

# Flags
CFLAGS := -Wall

all: check_libs $(OUTPUT) $(CIA_OUTPUT)

# Check if libraries are installed and build if not
check_libs:
	@echo "Checking if libraries are installed..."
	@dpkg -s devkitARM >/dev/null 2>&1 || (echo "devkitARM is not installed, installing..."; sudo apt-get install devkitARM)
	@dpkg -s ctrulib >/dev/null 2>&1 || (echo "ctrulib is not installed, installing..."; sudo apt-get install ctrulib)
	@dpkg -s citro3d >/dev/null 2>&1 || (echo "citro3d is not installed, installing..."; sudo apt-get install citro3d)
	@echo "All required libraries are installed."

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
