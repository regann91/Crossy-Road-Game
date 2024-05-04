#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <map>
#include <string>
#include "Renderable.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"

// Singleton class that manages the drawing
class Renderer {
public:

    // Deleting copy constructor
    Renderer(const Renderer& obj) = delete;

    // Returns the (sinzgle) instance of TextureManager
    static Renderer* instance();

    // Draws the scene
    void drawScene(Game game);
    
private:
    // Private constructor
    Renderer();

    // Single instance of manager
    static Renderer* INSTANCE;

    std::shared_ptr<Renderable> ground;
};