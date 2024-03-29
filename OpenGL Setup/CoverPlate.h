#pragma once
#ifndef COVERPLATE_H
#define COVERPLATE_H

#include "GameObject.h"

class CoverPlate : public GameObject {
public:
    CoverPlate(float startX, float startY, float objWidth, float objHeight, std::string texpath, bool orient);

    void draw() const override;

    bool orient;
};

#endif

