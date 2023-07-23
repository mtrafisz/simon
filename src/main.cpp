#include "simon.h"

int main() {
    InitWindow(windowDimension, windowDimension, "Simon");
    InitAudioDevice();

    SetTargetFPS(60);

    // test simon button
    Simon game;

    while (!WindowShouldClose()) {
        game.update();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            game.mouseInput();
        }
        if (IsKeyPressed(KEY_R)) {
            game.reset();
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
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