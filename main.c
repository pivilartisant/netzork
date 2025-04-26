#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

void draw_node_at_end_of_line(int blockSize, int posX, int posY){
    DrawRectangleLines(posX-blockSize/2, posY-blockSize/2, blockSize, blockSize, RAYWHITE);
};

void draw_line_with_node(int posX, int posY, int endPosX,int EndPosY, int blockSize){
    DrawLine(posX, posY, endPosX, EndPosY, RAYWHITE); 
    draw_node_at_end_of_line(blockSize, endPosX, EndPosY);
}

int displace_position(int min, int max){
    unsigned int seed = time(0);
    return rand_r(&seed) % (max - min + 1) + min; 
}

//void draw_centralized_network(int width, int height, int rd_pos_x_left_down, int rd_pos_y_left_down){
void draw_centralized_network(int width, int height){
    int blockSize = 10;
    // center block 
    // from the center block spread different networks ~ 8
    DrawRectangle(width/2-blockSize/2, height/2-blockSize/2, blockSize, blockSize, RAYWHITE);
   
    draw_line_with_node(width/2, height/2, blockSize, height/2, blockSize); // left

    draw_line_with_node(width/2, height/2, width-blockSize,  height/2, blockSize); // rght

    draw_line_with_node(width/2, height/2, width/2, blockSize, blockSize); // up

    draw_line_with_node(width/2, height/2, width/2,  height-blockSize, blockSize); // down

    // diagonales
    draw_line_with_node(width/2, height/2, blockSize, blockSize, blockSize); // up left

    draw_line_with_node(width/2, height/2, blockSize, height-blockSize, blockSize); // down left

    draw_line_with_node(width/2, height/2, width-blockSize, blockSize, blockSize); // up right

    draw_line_with_node(width/2, height/2, width-blockSize, height-blockSize, blockSize); // down right


    // randoms 
    // draw_line_with_node(width/2, height/2, rd_pos_x_left_down, height-blockSize, blockSize); // rnd left x

    // draw_line_with_node(width/2, height/2, blockSize, rd_pos_y_left_down, blockSize); // rnd left y
};

void draw_tryptique(int one_third,int two_third, int height){
    // divide
    DrawLine(one_third, 0, one_third, height, RAYWHITE);
    DrawLine(two_third, 0, two_third, height, RAYWHITE);

    // draw titles
    DrawText("Centralized", 4, height-12, 12, RAYWHITE);
    DrawText("Decentralized", one_third+4, height-12, 12, RAYWHITE);
    DrawText("Distributed", two_third+4, height-12, 12, RAYWHITE);
}

int main(){
    
int window_width = 900;
int one_third = window_width/3;
int two_third = window_width/3*2;
int window_height = 450;

// int rd_pos_x_left_down = displace_position(10, one_third/2);
// int rd_pos_y_left_down = displace_position(window_height/2, window_height-10);


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

    DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 12, RAYWHITE);

        switch (netzorkState)
        {
            case INTRO: {
                DrawText("Welcome to netzork", 0, window_height-24, 24, RAYWHITE);
            } break;
            case PARADIGMS:{
                draw_tryptique(one_third, two_third, window_height);
                // draw_centralized_network(one_third, window_height, rd_pos_x_left_down, rd_pos_y_left_down);
                draw_centralized_network(one_third, window_height);
            } break;
        }
   
    EndDrawing();
}

CloseWindow();
}
