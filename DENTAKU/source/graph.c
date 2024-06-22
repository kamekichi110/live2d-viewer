#include "./ctrulib/libctru/include/3ds.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "calculator.h"

// 定数
#define GRAPH_WIDTH 400
#define GRAPH_HEIGHT 240
#define X_MIN -10.0
#define X_MAX 10.0
#define Y_MIN -6.0
#define Y_MAX 6.0

// 点を描画するヘルパー関数
void drawPoint(int x, int y) {
    if (x >= 0 && x < GRAPH_WIDTH && y >= 0 && y < GRAPH_HEIGHT) {
        u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
        int index = 3 * (y * GRAPH_WIDTH + x);
        fb[index] = 0xFF;      // R
        fb[index + 1] = 0xFF;  // G
        fb[index + 2] = 0xFF;  // B
    }
}

// 関数のグラフを描画するメイン関数
void drawGraph(const char* expression) {
    for (int i = 0; i < GRAPH_WIDTH; i++) {
        double x = X_MIN + (X_MAX - X_MIN) * ((double)i / (GRAPH_WIDTH - 1));
        
        char exprWithX[256];
        snprintf(exprWithX, sizeof(exprWithX), expression, x);
        
        double y = calculate(exprWithX);

        int pixelX = i;
        int pixelY = (int)((Y_MAX - y) / (Y_MAX - Y_MIN) * (GRAPH_HEIGHT - 1));
        
        drawPoint(pixelX, pixelY);
    }
}
