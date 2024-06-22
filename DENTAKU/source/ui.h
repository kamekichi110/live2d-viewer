#ifndef UI_H
#define UI_H

#include <3ds.h>

void drawBackgroundImage();
void drawBottomScreen(PrintConsole *bottomScreen);
void handleInput(char *expression, int *cursorPos);

#endif
