#include "simon.h"

#define MOUSE_INPUT_BUTTON MOUSE_LEFT_BUTTON
#define RESET_BUTTON KEY_R
#define QUIT_BUTTON KEY_ESCAPE

#define FPS 30

int main() {
    InitWindow(windowDimension, windowDimension, "Simon");
    InitAudioDevice();

    SetTargetFPS(FPS);

    Simon game;

    while (!WindowShouldClose()) {
        game.update();

        if (IsMouseButtonPressed(MOUSE_INPUT_BUTTON)) {
            game.mouseInput();
        }
        if (IsKeyPressed(RESET_BUTTON)) {
            game.reset();
        }
        if (IsKeyPressed(QUIT_BUTTON)) {
            break;
        }

        BeginDrawing();

        game.draw();

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}