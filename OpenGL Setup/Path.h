#pragma once
#include <vector>
#include "GameObject.h"
#include "MovingObject.h"
#include "Character.h"

class Path : public GameObject {
public:
    // Boulders/Trunks on the road/river
    std::vector<MovingObject> movingObjects;

    // Constructor
    Path(float roadY, float roadZ, float roadDepth, glm::vec4 color, int nbObj = 3, float objD = 50.0);

    // Creates and initializes moving objects positions
    void initRoadMovingObjects();
    void initRiverMovingObjects();

    // Getter
    float getObjWidth() const { return objWidth; }

    // checks for collisions on way
    virtual bool getsKilled(std::shared_ptr<Character> player);

    // Updates all object positions
    void update(float deltaTime);

private:
    int nbObjPerLane;   // Nb of moving objects per lane
    float objWidth;   // Width of lane moving objects

    // Generates a template moving object for the path
    void createRoadMovingObj(float initX, float initY, float speed);
    void createRiverMovingObj(float initX, float initY, float speed);
};