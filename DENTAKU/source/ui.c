#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
static const char *buttons = "0123456789+-*/()=sin cos tan log ln sqrt ^ , .";
static const int buttonCount = 26;
static const int buttonWidth = 30;
static const int buttonHeight = 20;

void drawBackgroundImage() {
    FILE* bgFile = fopen("gfx/bg.bin", "rb");
    if (bgFile) {
        u8* bgData = (u8*)malloc(400 * 240 * 3); // 400x240 RGB
        fread(bgData, 1, 400 * 240 * 3, bgFile);
        fclose(bgFile);
        u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
        memcpy(fb, bgData, 400 * 240 * 3);
        free(bgData);
    } else {
        printf("\x1b[10;1HFailed to load background image!");
    }
}

void drawButton(int x, int y, const char *text, bool selected) {
    u8* fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
    int index;

    for (int i = 0; i < buttonHeight; i++) {
        for (int j = 0; j < buttonWidth; j++) {
            index = 3 * ((y + i) * 320 + (x + j));
            if (selected) {
                fb[index] = 0; // R
                fb[index + 1] = 0xFF; // G
                fb[index + 2] = 0; // B
            } else {
                fb[index] = 0; // R
                fb[index + 1] = 0; // G
                fb[index + 2] = 0; // B
            }
        }
    }

    printf("\x1b[%d;%dH%s", y / 8 + 1, x / 8 + 1, text);
}

void drawBottomScreen(PrintConsole *bottomScreen) {
    consoleSelect(bottomScreen);
    printf("\x1b[1;1HEnter your expression:");
    for (int i = 0; i < buttonCount; i++) {
        int x = (i % 5) * (buttonWidth + 5) + 20;
        int y = (i / 5) * (buttonHeight + 5) + 40;
        drawButton(x, y, buttons + i * 2, false);
    }
    printf("\x1b[9;1H[Graph] [Reset]");
}

void handleInput(char *expression, int *cursorPos) {
    hidScanInput();
    u32 kDown = hidKeysDown();

    if (kDown & KEY_A) {
        // Calculate the expression
        printf("Calculating: %s\n", expression);
    } else if (kDown & KEY_B) {
        // Clear the expression
        *cursorPos = 0;
        expression[0] = '\0';
    } else if (kDown & KEY_Y) {
        // Delete one character
        if (*cursorPos > 0) {
            (*cursorPos)--;
            expression[*cursorPos] = '\0';
        }
    } else if (kDown & KEY_X) {
        // Append a character
        for (int i = 0; i < buttonCount; i++) {
            if (kDown & (1 << (KEY_A + i))) {
                expression[*cursorPos] = buttons[i];
                (*cursorPos)++;
                expression[*cursorPos] = '\0';
                break;
            }
        }
    }
}
