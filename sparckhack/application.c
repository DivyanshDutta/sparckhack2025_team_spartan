#include <stdio.h>
#include "raylib.h"
#include "server.h"
#include "bins.h"
#include "raygui.h"
#include "style_dark.h"

#define WINDOW_WIDTH 1605
#define WINDOW_HEIGHT 815

void draw_main_window();
void main_window_init();

static void init()
{
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Sparckhack : Team Spartan");
    //GuiLoadStyle("styles\\dark\\dark (2).rgs");
    SetWindowIcon(LoadImage("ui\\rat.png"));
    GuiLoadStyleDark();

    bin_init();
    server_init();
}

int main()
{
    init();
    main_window_init();

    while(!WindowShouldClose()){
        BeginDrawing();
        draw_main_window();
        EndDrawing();
    }

    server_close();
    CloseWindow();
    return 0;
}