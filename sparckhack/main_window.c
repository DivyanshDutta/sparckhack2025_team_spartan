#include "raylib.h"
#include "server.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void ButtonRestart();
static void ButtonNext();
static void ButtonBack();
static void ButtonSave();
static void ButtonStop();

Image bin;
Texture2D texture;

extern void main_window_init()
{
    bin = LoadImage("ui\\dustbin.png");
    ImageResize(&bin,90,90);
    texture = LoadTextureFromImage(bin);
    UnloadImage(bin);
}

void drawbins()
{}

extern void draw_main_window()
{
    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    Rectangle ScrollPanel001ScrollView = { 0, 0, 0, 0 };
    Vector2 ScrollPanel001ScrollOffset = { 0, 0 };
    Vector2 ScrollPanel001BoundsOffset = { 0, 0 };
    bool TextBox007EditMode = false;
    char TextBox007Text[128] = "0001";
    bool TextBox008EditMode = false;
    char TextBox008Text[128] = "BIN_TYPE_MIXED";
    bool TextBox009EditMode = false;
    char TextBox009Text[128] = "50.0 ";
    bool TextBox010EditMode = false;
    char TextBox010Text[128] = "32.0 C";
    bool TextBox011EditMode = false;
    char TextBox011Text[128] = "90.0 ";
    bool TextBox012EditMode = false;
    char TextBox012Text[128] = "25.468913 N";
    bool TextBox013EditMode = false;
    char TextBox013Text[128] = "56.123468 E";
    bool TextBox027EditMode = false;
    char TextBox027Text[128] = "192.168.1.1";
    bool TextBox028EditMode = false;
    char TextBox028Text[128] = "25517";
    bool TextBox030EditMode = false;
    char TextBox030Text[128] = "openstreetmap.org";
    //----------------------------------------------------------------------------------

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 
            //ClearBackground((Color){.r=40,.g=40,.b=40,.a=0});

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            GuiScrollPanel((Rectangle){ 0, 0, 1288 - ScrollPanel001BoundsOffset.x, 816 - ScrollPanel001BoundsOffset.y }, NULL, (Rectangle){ 0, 0, 1288, 816 }, &ScrollPanel001ScrollOffset, &ScrollPanel001ScrollView);
            GuiGroupBox((Rectangle){ 1304, 16, 288, 416 }, "Bin Detail View");
            if (GuiButton((Rectangle){ 1376, 672, 144, 24 }, "Restart Server")) ButtonRestart(); 
            GuiGroupBox((Rectangle){ 1304, 448, 288, 304 }, "Controls");
            if (GuiTextBox((Rectangle){ 1424, 40, 144, 24 }, TextBox007Text, 128, TextBox007EditMode)) TextBox007EditMode = !TextBox007EditMode;
            if (GuiTextBox((Rectangle){ 1424, 88, 144, 24 }, TextBox008Text, 128, TextBox008EditMode)) TextBox008EditMode = !TextBox008EditMode;
            if (GuiTextBox((Rectangle){ 1424, 136, 144, 24 }, TextBox009Text, 128, TextBox009EditMode)) TextBox009EditMode = !TextBox009EditMode;
            if (GuiTextBox((Rectangle){ 1424, 184, 144, 24 }, TextBox010Text, 128, TextBox010EditMode)) TextBox010EditMode = !TextBox010EditMode;
            if (GuiTextBox((Rectangle){ 1424, 232, 144, 24 }, TextBox011Text, 128, TextBox011EditMode)) TextBox011EditMode = !TextBox011EditMode;
            if (GuiTextBox((Rectangle){ 1424, 280, 144, 24 }, TextBox012Text, 128, TextBox012EditMode)) TextBox012EditMode = !TextBox012EditMode;
            if (GuiTextBox((Rectangle){ 1424, 328, 144, 24 }, TextBox013Text, 128, TextBox013EditMode)) TextBox013EditMode = !TextBox013EditMode;
            GuiLabel((Rectangle){ 1320, 40, 120, 24 }, "Bin Id");
            GuiLabel((Rectangle){ 1320, 88, 120, 24 }, "Bin Type");
            GuiLabel((Rectangle){ 1320, 136, 120, 24 }, "Fill Level");
            GuiLabel((Rectangle){ 1320, 184, 120, 24 }, "Temprature");
            GuiLabel((Rectangle){ 1320, 232, 120, 24 }, "Humidity");
            GuiLabel((Rectangle){ 1320, 280, 120, 24 }, "Laattitude");
            GuiLabel((Rectangle){ 1320, 328, 120, 24 }, "Longitude");
            GuiLine((Rectangle){ 1320, 368, 240, 16 }, NULL);
            if (GuiButton((Rectangle){ 1488, 392, 72, 24 }, "NEXT")) ButtonNext(); 
            if (GuiButton((Rectangle){ 1320, 392, 72, 24 }, "BACK")) ButtonBack(); 
            if (GuiButton((Rectangle){ 1400, 392, 80, 24 }, "SAVE")) ButtonSave(); 
            if (GuiButton((Rectangle){ 1376, 712, 144, 24 }, "Stop Server")) ButtonStop(); 
            GuiLabel((Rectangle){ 1320, 480, 96, 24 }, "Server IP");
            GuiLabel((Rectangle){ 1320, 528, 96, 24 }, "Server Port");
            if (GuiTextBox((Rectangle){ 1416, 480, 152, 24 }, TextBox027Text, 128, TextBox027EditMode)) TextBox027EditMode = !TextBox027EditMode;
            if (GuiTextBox((Rectangle){ 1416, 528, 152, 24 }, TextBox028Text, 128, TextBox028EditMode)) TextBox028EditMode = !TextBox028EditMode;
            GuiLabel((Rectangle){ 1320, 576, 96, 24 }, "Map Server");
            if (GuiTextBox((Rectangle){ 1416, 576, 152, 24 }, TextBox030Text, 128, TextBox030EditMode)) TextBox030EditMode = !TextBox030EditMode;
            GuiPanel((Rectangle){ 1304, 768, 288, 40 }, NULL);
            GuiLabel((Rectangle){ 1312, 776, 272, 24 }, "Processing.....");
            GuiLabel((Rectangle){ 8, 0, 120, 24 }, "Bin List View");
            //----------------------------------------------------------------------------------

    drawbins();
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
static void ButtonRestart()
{
    server_close();
    server_init();
}
static void ButtonNext()
{
    // TODO: Implement control logic
}
static void ButtonBack()
{
    // TODO: Implement control logic
}
static void ButtonSave()
{
    // TODO: Implement control logic
}
static void ButtonStop()
{
    server_close();
}

