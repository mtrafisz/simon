#pragma once

#include "raylib.h"
#include <cstdint>
#include <vector>


const float scale = 0.8f;

const unsigned windowDimension = (600 * scale),
               borderSize = windowDimension / 30,
               buttonSize = (windowDimension - borderSize * 2) / 2,
               buttonBorderSize = buttonSize / 20;

Color colorFromHex(uint32_t hex);

Color colorLerp(Color a, Color b, float t);

const Color cBackground     = BLACK,
            cButtonBlue     = colorFromHex(0x02a5ffff),
            cButtonGreen    = colorFromHex(0x66cc33ff),
            cButtonRed      = colorFromHex(0xff3300ff),
            cButtonYellow   = colorFromHex(0xffcc00ff),
            cButtonHighlight= colorFromHex(0xffffffee),
            cTextScore      = colorFromHex(0xfffffff0),
            cTextGameOver   = RED;


class SimonButton {
private:
    Color color;
    Vector2 position;
    Sound sound;

    bool highlighted = false;
    float highlightTimer = 0.0f;

public:
    SimonButton(Color color, const Vector2& position, const char* soundPath);
    ~SimonButton();

    void playSound() const;

    void highlight();
    bool isHighlighted() const;

    bool isClicked() const;

    void update();
    void draw();

    void reset();
};


class Simon {
private:
    enum class GameState {
        Playing,
        GameOver
    };

    SimonButton button[4] = {                                                               // Assuming it runs from ./build/(build type)/
        SimonButton(cButtonBlue,    { borderSize, borderSize },                             "../../assets/blue.wav"),
        SimonButton(cButtonGreen,   { borderSize + buttonSize, borderSize },                "../../assets/green.wav"),
        SimonButton(cButtonRed,     { borderSize, borderSize + buttonSize },                "../../assets/red.wav"),
        SimonButton(cButtonYellow,  { borderSize + buttonSize, borderSize + buttonSize },   "../../assets/yellow.wav")
    };

    bool paused = false;
    float timeToUnpause = 0.0f;

    bool playingSequence = true;

    std::vector<int> sequence;
    std::vector<int> playerSequence;
    
    int sequenceLength = 0;
    int sequencePlayingIndex = 0;

    GameState gameState = GameState::Playing;

    bool compareSequences() const;

    void pushRandomNote();

    void pause(float time);

public:
    Simon();

    void update();
    void draw();

    void mouseInput();

    void reset();
};
