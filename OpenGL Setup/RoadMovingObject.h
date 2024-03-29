#include "GameObject.h"
#include "Wheel.h"

class RoadMovingObject : public GameObject {
public:
    // Constructor
    RoadMovingObject(float startX, float startY, float movingWidth, float movingHeight, std::string texPath, float movingSpeed, float laneW);

    // Override draw function
    void draw() const override;

    // Update function for car movement
    void update(float deltaTime);

    // Returns speed
    float getSpeed() const { return speed; }
    Wheel leftWheel;
    Wheel rightWheel;

private:
    // Speed of moving object
    float speed;
    // Width of the lane it is on
    float laneWidth;
};