#include <stdio.h>
#include "raylib.h"
#include "server.h"
#include "bins.h"
#include "raygui.h"

#define WINDOW_WIDTH 1605
#define WINDOW_HEIGHT 815

void draw_main_window();

int main()
{
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Sparckhack : Team Spartan");
    GuiLoadStyle("styles\\dark\\style_dark.rgs");

    bin_init();
    server_init();

    while(!WindowShouldClose()){
        BeginDrawing();
        draw_main_window();
        EndDrawing();
    }

    server_close();
    CloseWindow();
    return 0;
}