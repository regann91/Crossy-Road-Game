#pragma once
#include "Path.h"

class Road : public Path {
public:
    // Constructor
    Road(float roadY, float roadWidth);

    bool getsKilled(Character* player) override;
};