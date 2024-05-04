#pragma once
#include "Path.h"

class River : public Path {
public:
    // Constructor
    River(float roadY, float roadWidth);

    bool getsKilled(std::shared_ptr<Character> player) override;
};