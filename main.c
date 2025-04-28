#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

int window_width = 900;
int window_height = 450;
int std_blocksize = 10;

typedef struct Node  {
    int POS_X;
    int POS_Y; 
    int SIZE;
    Color COLOR;
} Node;

typedef struct Link {
    int STRT_X;
    int STRT_Y;
    int END_X;
    int END_Y;
    Color COLOR;
} Link;

typedef struct Connexion {
    Node NODE;
    Link LINK;
} Connexion;

typedef struct Centralize {
    Node Origin;
// four ordinal connections 
    Connexion North;
    Connexion East;
    Connexion South;
    Connexion West;
// diagonales
    Connexion North_East;
    Connexion South_East;
    Connexion South_West;
    Connexion North_West;
// randoms 
    Connexion Distortion_A;
    Connexion Distortion_B;
    Connexion Distortion_C;
    Connexion Distortion_D;
    Connexion Distortions[24]; 
} Centralize;

Centralize centralize_structure;


// int displace_position(int min, int max){
//     unsigned int seed = time(0) * rand();
//     // unsigned int seed = time(0);
//     return rand_r(&seed) % (max - min + 1) + min; 
// }

int displace_distortion(int min, int max){
    unsigned int seed = time(0) * rand();
    // unsigned int seed = time(0);
    return rand_r(&seed) % (max - min + 1) + min; 
}


void init_connexion(Connexion* conn, int start_x, int start_y, int end_x, int end_y) {
    conn->LINK.STRT_X = start_x;
    conn->LINK.STRT_Y = start_y;
    conn->LINK.END_X = end_x;
    conn->LINK.END_Y = end_y;
    
    conn->NODE.POS_X = end_x - std_blocksize / 2;
    conn->NODE.POS_Y = end_y - std_blocksize / 2;
    conn->NODE.SIZE = std_blocksize;
}



// Initialize centralize_structure global
void initCentralize(Centralize* centralize_structure, int width, int height){
    // Origin
    centralize_structure->Origin.POS_X = width/2-std_blocksize/2;
    centralize_structure->Origin.POS_Y = height/2-std_blocksize/2;
    centralize_structure->Origin.SIZE = std_blocksize;

    int center_width = width/2;
    int center_height = height/2;

    // North
    init_connexion(&centralize_structure->North,center_width, center_height, width/2, displace_distortion(std_blocksize, height * 0.25));

    // North East
    init_connexion(&centralize_structure->North_East, center_width, center_height, displace_distortion(width* 0.75, width-std_blocksize), displace_distortion(std_blocksize, height* 0.25));
 
    // North West
    init_connexion(&centralize_structure->North_West, center_width, center_height,displace_distortion(std_blocksize, width* 0.25), std_blocksize);

    // East 
    init_connexion(&centralize_structure->East, center_width, center_height, displace_distortion(width* 0.75, width-std_blocksize), center_height);

    // South
    init_connexion(&centralize_structure->South, center_width, center_height, width/2, displace_distortion(height* 0.75, height-std_blocksize));

    // South East
    init_connexion(&centralize_structure->South_East, center_width, center_height, displace_distortion(width* 0.75, width-std_blocksize), displace_distortion(height* 0.75, height-std_blocksize));

    // South West
    init_connexion(&centralize_structure->South_West, center_width, center_height, displace_distortion(std_blocksize, width*0.25), displace_distortion(height* 0.75, height-std_blocksize));
    
    // West
    init_connexion(&centralize_structure->West, center_width, center_height, displace_distortion(std_blocksize, width* 0.25), center_height);

    // Distortions 

    // Distortion_A
    init_connexion(&centralize_structure->Distortion_A, width/2, height/2,displace_distortion(width/2, width),displace_distortion(std_blocksize, height/2));
   
    // Distortion_B
    init_connexion(&centralize_structure->Distortion_B, width/2, height/2, displace_distortion(width/2, width),displace_distortion(height/2, height-std_blocksize));

    // Distortion_C
    init_connexion(&centralize_structure->Distortion_C, width/2, height/2,displace_distortion(std_blocksize, width/2),displace_distortion(std_blocksize, height/2));
    
    // Distortion_D
    init_connexion(&centralize_structure->Distortion_D, width/2, height/2,displace_distortion(std_blocksize, width/2), displace_distortion(height/2, height-std_blocksize));

    int length = sizeof(centralize_structure->Distortions)/ sizeof(centralize_structure->Distortions[0]);

    int i;

    for (i = 0 ; i < length; i ++){
        init_connexion(&centralize_structure->Distortions[i], center_width, center_height,displace_distortion(std_blocksize, width), displace_distortion(std_blocksize, height));
    }
}


void draw_node_at_end_of_line(int blockSize, int posX, int posY){
    DrawRectangleLines(posX-blockSize/2, posY-blockSize/2, blockSize, blockSize, RAYWHITE);
};

void draw_line_with_node(int posX, int posY, int endPosX,int EndPosY, int blockSize){
    DrawLine(posX, posY, endPosX, EndPosY, RAYWHITE); 
    draw_node_at_end_of_line(blockSize, endPosX, EndPosY);
}

//void draw_centralized_network(int width, int height, int rd_pos_x_left_down, int rd_pos_y_left_down){
void draw_centralized_network(Centralize* centralize_structure){
    // Origin
    DrawRectangle(
        centralize_structure->Origin.POS_X, 
        centralize_structure->Origin.POS_Y,
        centralize_structure->Origin.SIZE, 
        centralize_structure->Origin.SIZE, 
        RAYWHITE);

    // North
    draw_line_with_node(
        centralize_structure->North.LINK.STRT_X, 
        centralize_structure->North.LINK.STRT_Y, 
        centralize_structure->North.LINK.END_X, 
        centralize_structure->North.LINK.END_Y, 
        std_blocksize
    );

    // East
    draw_line_with_node(
        centralize_structure->East.LINK.STRT_X, 
        centralize_structure->East.LINK.STRT_Y, 
        centralize_structure->East.LINK.END_X, 
        centralize_structure->East.LINK.END_Y, 
        std_blocksize
    );

    // South
    draw_line_with_node(
        centralize_structure->South.LINK.STRT_X, 
        centralize_structure->South.LINK.STRT_Y, 
        centralize_structure->South.LINK.END_X, 
        centralize_structure->South.LINK.END_Y, 
        std_blocksize
    );
   
    // West
    draw_line_with_node(
        centralize_structure->West.LINK.STRT_X, 
        centralize_structure->West.LINK.STRT_Y, 
        centralize_structure->West.LINK.END_X, 
        centralize_structure->West.LINK.END_Y, 
        std_blocksize
    );
    // diagonales

    // // North East
    draw_line_with_node(
        centralize_structure->North_East.LINK.STRT_X, 
        centralize_structure->North_East.LINK.STRT_Y, 
        centralize_structure->North_East.LINK.END_X, 
        centralize_structure->North_East.LINK.END_Y, 
        std_blocksize
    );

    // // North West
    draw_line_with_node(
        centralize_structure->North_West.LINK.STRT_X, 
        centralize_structure->North_West.LINK.STRT_Y, 
        centralize_structure->North_West.LINK.END_X, 
        centralize_structure->North_West.LINK.END_Y, 
        std_blocksize
    );

    // South East
    draw_line_with_node(
        centralize_structure->South_East.LINK.STRT_X, 
        centralize_structure->South_East.LINK.STRT_Y, 
        centralize_structure->South_East.LINK.END_X, 
        centralize_structure->South_East.LINK.END_Y, 
        std_blocksize
    );
   
    // South West
    draw_line_with_node(
        centralize_structure->South_West.LINK.STRT_X, 
        centralize_structure->South_West.LINK.STRT_Y, 
        centralize_structure->South_West.LINK.END_X, 
        centralize_structure->South_West.LINK.END_Y, 
        std_blocksize
    );


    // randoms 
    draw_line_with_node(
        centralize_structure->Distortion_A.LINK.STRT_X,
        centralize_structure->Distortion_A.LINK.STRT_Y, 
        centralize_structure->Distortion_A.LINK.END_X, 
        centralize_structure->Distortion_A.LINK.END_Y, 
        std_blocksize
    );

    draw_line_with_node(
        centralize_structure->Distortion_B.LINK.STRT_X,
        centralize_structure->Distortion_B.LINK.STRT_Y, 
        centralize_structure->Distortion_B.LINK.END_X, 
        centralize_structure->Distortion_B.LINK.END_Y, 
        std_blocksize
    );

    draw_line_with_node(
        centralize_structure->Distortion_C.LINK.STRT_X,
        centralize_structure->Distortion_C.LINK.STRT_Y, 
        centralize_structure->Distortion_C.LINK.END_X, 
        centralize_structure->Distortion_C.LINK.END_Y, 
        std_blocksize
    );

    draw_line_with_node(
        centralize_structure->Distortion_D.LINK.STRT_X,
        centralize_structure->Distortion_D.LINK.STRT_Y, 
        centralize_structure->Distortion_D.LINK.END_X, 
        centralize_structure->Distortion_D.LINK.END_Y, 
        std_blocksize
    );

    int length = sizeof(centralize_structure->Distortions)/ sizeof(centralize_structure->Distortions[0]);

    int i;

    for (i = 0 ; i < length; i ++){
        draw_line_with_node(centralize_structure->Distortions[i].LINK.STRT_X, centralize_structure->Distortions[i].LINK.STRT_Y, centralize_structure->Distortions[i].LINK.END_X, centralize_structure->Distortions[i].LINK.END_Y, std_blocksize);
    }

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
    
int centralize_x_limit = window_width/3;
int two_third = window_width/3*2;

initCentralize(&centralize_structure,centralize_x_limit, window_height);

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
        //SetTargetFPS(1);
        if (IsKeyPressed(KEY_R))
                {
					initCentralize(&centralize_structure, centralize_x_limit, window_height);
                }
            SetTargetFPS(3);
            initCentralize(&centralize_structure, centralize_x_limit, window_height);
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
                draw_tryptique(centralize_x_limit, two_third, window_height);
                draw_centralized_network(&centralize_structure);
            } break;
        }
   
    EndDrawing();
}

CloseWindow();
}
