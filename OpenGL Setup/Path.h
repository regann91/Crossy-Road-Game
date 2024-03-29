#pragma once
#include <vector>
#include "GameObject.h"
#include "RoadMovingObject.h"
#include "RiverMovingObject.h"
#include "Character.h"

class Path : public GameObject {
public:
    // Boulders/Trunks on the road/river
    std::vector<RoadMovingObject> RoadMovingObjects;
    std::vector<RiverMovingObject> RiverMovingObjects;

    // Constructor
    Path(float roadY, float roadWidth, std::string texPath, int nbObj = 3, float objW = 50.0);

    // Creates and initializes moving objects positions
    void initRoadMovingObjects();
    void initRiverMovingObjects();

    // Override the draw function
    void draw() const override;

    // Getter
    float getObjWidth() const { return objWidth; }

    // checks for collisions on way
    virtual bool getsKilled(Character* player);

    // Updates all object positions
    void update(float deltaTime);

private:
    int nbObjPerLane;   // Nb of moving objects per lane
    float objWidth;   // Width of lane moving objects

    // Generates a template moving object for the path
    virtual RoadMovingObject createRoadMovingObj(float initX, float initY, float speed);
    virtual RiverMovingObject createRiverMovingObj(float initX, float initY, float speed);
};