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
} Centralize;

Centralize centralize_structure;


int displace_position(int min, int max){
    unsigned int seed = time(0);
    return rand_r(&seed) % (max - min + 1) + min; 
}


// Initialize centralize_structure global
void initCentralize(Centralize* centralize_structure, int width, int height){
    // Origin
    centralize_structure->Origin.POS_X = width/2-std_blocksize/2;
    centralize_structure->Origin.POS_Y = height/2-std_blocksize/2;
    centralize_structure->Origin.SIZE = std_blocksize;
    // North
    centralize_structure->North.LINK.STRT_X = width/2;
    centralize_structure->North.LINK.STRT_Y = height/2;
    centralize_structure->North.LINK.END_X = centralize_structure->North.LINK.STRT_X;
    centralize_structure->North.LINK.END_Y = std_blocksize;
    // North Node
    centralize_structure->North.NODE.POS_X = centralize_structure->North.LINK.END_X - std_blocksize / 2;
    centralize_structure->North.NODE.POS_Y = centralize_structure->North.LINK.END_Y - std_blocksize / 2;
    centralize_structure->North.NODE.SIZE = std_blocksize;
    // North East
    centralize_structure->North_East.LINK.STRT_X = width/2;
    centralize_structure->North_East.LINK.STRT_Y = height/2;
    centralize_structure->North_East.LINK.END_X = width - std_blocksize;
    centralize_structure->North_East.LINK.END_Y = std_blocksize;
    // North East Node
    centralize_structure->North_East.NODE.POS_X = centralize_structure->North_East.LINK.END_X - std_blocksize / 2;
    centralize_structure->North_East.NODE.POS_Y = centralize_structure->North_East.LINK.END_Y - std_blocksize / 2;
    centralize_structure->North_East.NODE.SIZE = std_blocksize;
    // North West
    centralize_structure->North_West.LINK.STRT_X = width/2;
    centralize_structure->North_West.LINK.STRT_Y = height/2;
    centralize_structure->North_West.LINK.END_X = std_blocksize;
    centralize_structure->North_West.LINK.END_Y = std_blocksize;
    // North West Node
    centralize_structure->North_West.NODE.POS_X = centralize_structure->North_West.LINK.END_X - std_blocksize / 2;
    centralize_structure->North_West.NODE.POS_Y = centralize_structure->North_West.LINK.END_Y - std_blocksize / 2;
    centralize_structure->North_West.NODE.SIZE = std_blocksize;

    // East 
    centralize_structure->East.LINK.STRT_X = width/2;
    centralize_structure->East.LINK.STRT_Y = height/2;
    centralize_structure->East.LINK.END_X = width - std_blocksize;
    centralize_structure->East.LINK.END_Y = centralize_structure->East.LINK.STRT_Y;
    // East Node 
    centralize_structure->East.NODE.POS_X = centralize_structure->East.LINK.END_X - std_blocksize / 2;
    centralize_structure->East.NODE.POS_Y = centralize_structure->East.LINK.END_Y - std_blocksize / 2;
    centralize_structure->East.NODE.SIZE = std_blocksize;

    // South
    centralize_structure->South.LINK.STRT_X = width/2;
    centralize_structure->South.LINK.STRT_Y = height/2;
    centralize_structure->South.LINK.END_X = centralize_structure->South.LINK.STRT_X;
    centralize_structure->South.LINK.END_Y = height - std_blocksize;
    // South Node
    centralize_structure->South.NODE.POS_X = centralize_structure->South.LINK.END_X - std_blocksize / 2;
    centralize_structure->South.NODE.POS_Y = centralize_structure->South.LINK.END_Y - std_blocksize / 2;
    centralize_structure->South.NODE.SIZE = std_blocksize;
    // South East
    centralize_structure->South_East.LINK.STRT_X = width/2;
    centralize_structure->South_East.LINK.STRT_Y = height/2;
    centralize_structure->South_East.LINK.END_X = width - std_blocksize;
    centralize_structure->South_East.LINK.END_Y = height - std_blocksize;
    // South East Node
    centralize_structure->South_East.NODE.POS_X = centralize_structure->South_East.LINK.END_X - std_blocksize / 2;
    centralize_structure->South_East.NODE.POS_Y = centralize_structure->South_East.LINK.END_Y - std_blocksize / 2;
    centralize_structure->South_East.NODE.SIZE = std_blocksize;
    // South West
    centralize_structure->South_West.LINK.STRT_X = width/2;
    centralize_structure->South_West.LINK.STRT_Y = height/2;
    centralize_structure->South_West.LINK.END_X = std_blocksize;
    centralize_structure->South_West.LINK.END_Y = height - std_blocksize;
    // South West Node
    centralize_structure->South_West.NODE.POS_X = centralize_structure->South_West.LINK.END_X - std_blocksize / 2;
    centralize_structure->South_West.NODE.POS_Y = centralize_structure->South_West.LINK.END_Y - std_blocksize / 2;
    centralize_structure->South_West.NODE.SIZE = std_blocksize;
    
    // West
    centralize_structure->West.LINK.STRT_X = width/2;
    centralize_structure->West.LINK.STRT_Y = height/2;
    centralize_structure->West.LINK.END_X = std_blocksize;
    centralize_structure->West.LINK.END_Y =  centralize_structure->West.LINK.STRT_Y;
    // West Node
    centralize_structure->West.NODE.POS_Y = centralize_structure->West.LINK.END_Y - std_blocksize / 2;
    centralize_structure->West.NODE.POS_X = centralize_structure->West.LINK.END_X - std_blocksize / 2;
    centralize_structure->West.NODE.SIZE = std_blocksize;

    // Distortions 

    // Distortion_A
    centralize_structure->Distortion_A.LINK.STRT_X = width/2;
    centralize_structure->Distortion_A.LINK.STRT_Y = height/2;
    centralize_structure->Distortion_A.LINK.END_X = displace_position(width/2, width);
    centralize_structure->Distortion_A.LINK.END_Y = displace_position(std_blocksize, height/2);

    // Distortion_B
    centralize_structure->Distortion_B.LINK.STRT_X = width/2;
    centralize_structure->Distortion_B.LINK.STRT_Y = height/2;
    centralize_structure->Distortion_B.LINK.END_X = displace_position(width/2, width);
    centralize_structure->Distortion_B.LINK.END_Y = displace_position(height/2, height-std_blocksize);

    // Distortion_C
    centralize_structure->Distortion_C.LINK.STRT_X = width/2;
    centralize_structure->Distortion_C.LINK.STRT_Y = height/2;
    centralize_structure->Distortion_C.LINK.END_X = displace_position(std_blocksize, width/2);
    centralize_structure->Distortion_C.LINK.END_Y = displace_position(std_blocksize, height/2);

    // Distortion_D
    centralize_structure->Distortion_D.LINK.STRT_X = width/2;
    centralize_structure->Distortion_D.LINK.STRT_Y = height/2;
    centralize_structure->Distortion_D.LINK.END_X = displace_position(std_blocksize, width/2);
    centralize_structure->Distortion_D.LINK.END_Y = displace_position(height/2, height-std_blocksize);

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
        if (IsKeyPressed(KEY_R))
                {
					initCentralize(&centralize_structure, centralize_x_limit, window_height);
                }
            // initCentralize(&centralize_structure, centralize_x_limit, window_height);
            //centralize_structure.Distortion_A.LINK.END_X = displace_position(0, 100);
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
                // draw_centralized_network(one_third, window_height, rd_pos_x_left_down, rd_pos_y_left_down);
                draw_centralized_network(&centralize_structure);
            } break;
        }
   
    EndDrawing();
}

CloseWindow();
}
