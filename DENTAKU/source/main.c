#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./ctrulib/libctru/include/3ds.h"
#include "ui.h"
#include "graph.h"
#include "calculator.h"

#define VERSION "v1.0.0"
#define AUTHOR "sirokuma_8110F"
#define APP_NAME "DENTAKU"

void drawTopScreen(PrintConsole *topScreen) {
    consoleSelect(topScreen);
    printf("\x1b[1;1H%s", APP_NAME);
    printf("\x1b[2;1H%s", VERSION);
    printf("\x1b[3;1H%s", AUTHOR);

    // 日付と時間
    time_t unixTime = time(NULL);
    struct tm* timeStruct = gmtime((const time_t *)&unixTime);
    printf("\x1b[5;1H%04d-%02d-%02d %02d:%02d:%02d", 
        timeStruct->tm_year + 1900, 
        timeStruct->tm_mon + 1, 
        timeStruct->tm_mday, 
        timeStruct->tm_hour, 
        timeStruct->tm_min, 
        timeStruct->tm_sec);
    
    // バッテリー残量
    u8 batteryLevel = 0;
    PTMU_GetBatteryLevel(&batteryLevel);
    printf("\x1b[6;1HBattery: %d%%", batteryLevel);

    // 背景画像
    drawBackgroundImage();
}

int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    PrintConsole topScreen;
    consoleInit(GFX_TOP, &topScreen);
    
    PrintConsole bottomScreen;
    consoleInit(GFX_BOTTOM, &bottomScreen);

    char expression[256] = "";
    int cursorPos = 0;

    // メインループ
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) break;

        // 上画面の描画
        drawTopScreen(&topScreen);
        
        // 下画面のUI描画
        drawBottomScreen(&bottomScreen);

        // 入力処理
        handleInput(expression, &cursorPos);

        // 式を表示
        consoleSelect(&bottomScreen);
        printf("\x1b[5;1HExpression: %s", expression);

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
