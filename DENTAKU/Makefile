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

all: $(OUTPUT) $(CIA_OUTPUT)

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

.PHONY: all clean
