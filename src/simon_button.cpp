#include "simon.h"

SimonButton::SimonButton(Color color, const Vector2& position, const char* soundPath) : color(color), position(position) {
    sound = LoadSound(soundPath);
}

SimonButton::~SimonButton() {
    UnloadSound(sound);
}

void SimonButton::playSound() const {
    PlaySound(sound);
}

void SimonButton::highlight() {
    highlighted = true;
    highlightTimer = 0.5f;
}
bool SimonButton::isHighlighted() const {
    return highlighted;
}

bool SimonButton::isClicked() const {
    // called after mouse input
    return CheckCollisionPointRec(GetMousePosition(), { position.x, position.y, (float)buttonSize, (float)buttonSize });
}

void SimonButton::update() {
    if (highlighted) {
        highlightTimer -= GetFrameTime();
        if (highlightTimer <= 0.0f) highlighted = false;
    }
}

void SimonButton::draw() {
    Color tempColor = color;
    if (highlighted) tempColor = colorLerp(color, cButtonHighlight, highlightTimer * 2.0f);

    DrawRectangle(position.x + buttonBorderSize, position.y + buttonBorderSize, buttonSize - buttonBorderSize * 2, buttonSize - buttonBorderSize * 2, tempColor);
}

void SimonButton::reset() {
    highlighted = false;
    highlightTimer = 0.0f;
}
