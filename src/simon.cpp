#pragma once

#include "simon.h"

Simon::Simon() {
    pushRandomNote();
    pause(1.0f);
}

void Simon::pushRandomNote() {
    sequence.push_back(GetRandomValue(0, 3));
    sequenceLength++;
    playingSequence = true;
}

void Simon::pause(float time) {
    paused = true;
    timeToUnpause = time;
}

bool Simon::compareSequences() const {
    for (int i = 0; i < playerSequence.size(); i++) {
        if (playerSequence[i] != sequence[i]) {
            return false;
        }
    }
    return true;
}

void Simon::update() {
    if (gameState == GameState::GameOver) return;

    if (paused) {
        if (timeToUnpause <= 0.0f) {
            paused = false;
            timeToUnpause = 0.0f;
        }
        else {
            timeToUnpause -= GetFrameTime();
        }
    } else {
        for (int i = 0; i < 4; i++) {
            button[i].update();
        }

        if (playingSequence && !paused) {
            if (sequencePlayingIndex == 0) {
                button[sequence[0]].highlight();
                button[sequence[0]].playSound();
                sequencePlayingIndex++;
            } else {
                if (!button[sequence[sequencePlayingIndex - 1]].isHighlighted()) {
                    if (sequencePlayingIndex < sequenceLength) {
                        button[sequence[sequencePlayingIndex]].highlight();
                        button[sequence[sequencePlayingIndex]].playSound();
                        sequencePlayingIndex++;
                    } else {
                        playingSequence = false;
                    }
                }
            }

            if (sequencePlayingIndex >= sequenceLength) {
                playingSequence = false;
                sequencePlayingIndex = 0;
            }

            if (!playingSequence) {
                pause(0.7f);
            }
        } else if (!paused) {
            if (!compareSequences()) {
                gameState = GameState::GameOver;
            } else if (playerSequence.size() == sequenceLength) {
                playerSequence.clear();
                pushRandomNote();

                for (int i = 0; i < 4; i++) {
                    button[i].reset();
                }

                pause(1.0f);
            }
        }
    }
}

void Simon::draw() {
    ClearBackground(cBackground);

    // print score
    DrawText(TextFormat("Score: %i", sequenceLength - 1), 5, 5, 20, cTextScore);

    switch (gameState) {
    case GameState::Playing:
        for (int i = 0; i < 4; i++) {
            button[i].draw();
        }
        break;
    case GameState::GameOver:
        DrawText("Game Over", windowDimension / 2 - 70, windowDimension / 2 - 25, 30, cTextGameOver);
        break;
    }
}

void Simon::mouseInput() {
    if (!paused && gameState == GameState::Playing) {
        for (int i = 0; i < 4; i++) {
            if (button[i].isClicked()) {
                button[i].highlight();
                button[i].playSound();
                playerSequence.push_back(i);
            }
        }
    }
}

void Simon::reset() {
    gameState = GameState::Playing;
    sequence.clear();
    playerSequence.clear();
    sequenceLength = 0;
    sequencePlayingIndex = 0;
    playingSequence = true;
    pushRandomNote();
}
