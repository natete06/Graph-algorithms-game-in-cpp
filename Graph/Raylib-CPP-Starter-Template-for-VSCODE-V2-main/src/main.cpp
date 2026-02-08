#include <raylib.h>

int main() {

    InitWindow(800, 800, "Type shiiii");
    // game speed/fps
    SetTargetFPS(60);

    // Game loop, runs until close icon is clicked or if esc is pressed
    while(!WindowShouldClose()) {



        BeginDrawing();
        EndDrawing();

    }


    CloseWindow();

    return 0;
}