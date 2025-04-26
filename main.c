#include "raylib.h"
#include "stdio.h"
#include "string.h"

void draw_tryptique(int one_third,int two_third, int height){
    DrawLine(one_third, 0, one_third, height, RAYWHITE);
    DrawLine(two_third, 0, two_third, height, RAYWHITE);
    DrawText("Centralized", 4, height-24, 24, RAYWHITE);
    DrawText("Decentralized", one_third+4, height-24, 24, RAYWHITE);
    DrawText("Distributed", two_third+4, height-24, 24, RAYWHITE);
}

int main(){
    
int window_width = 900;
int one_third = window_width/3;
int two_third = window_width/3*2;
int window_height = 450;


InitWindow(window_width, window_height,"netzork");

typedef enum NetzorkState {INTRO = 0, PARADIGMS} NetzorkState;

NetzorkState netzorkState = INTRO;

int frameCounter = 0;

SetTargetFPS(60); // sets targetFPS
    
while (!WindowShouldClose())
{
    frameCounter ++;    // Count frames

    // update 
    switch (netzorkState)
    {
        case INTRO:
            {
                if(frameCounter > 120){
                    netzorkState = PARADIGMS;
                }
            }
            break;
        case PARADIGMS:
            break;
    }


    // draw
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText(TextFormat("Frames: %d", frameCounter), 0, 0, 12, RAYWHITE);

        switch (netzorkState)
        {
            case INTRO: {
                DrawText("Welcome to netzork", 0, window_height-24, 24, RAYWHITE);
            } break;
            case PARADIGMS:{
                draw_tryptique(one_third, two_third, window_height);
            } break;
        }
   
    EndDrawing();
}

CloseWindow();
}
