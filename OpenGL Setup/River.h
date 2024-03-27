#pragma once
#include "Path.h"

class River : public Path {
public:
    // Constructor
    River(float roadY, float roadWidth);

    bool getsKilled(Character* player) override;

private:
    // Generates a template moving object for the path
    MovingObject createMovingObj(float initX, float initY, float speed) override;
};