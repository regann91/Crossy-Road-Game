#include <GL/glew.h>
#include <gl/glut.h>
#include <iostream>

#include "TextureManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Game.h"
#include "Character.h"
#include "Renderable.h"

#define GL_CLAMP_TO_EDGE 0x812F
#define DELTA 50

Game game;

// Reshape function, allows to keep aspect ratio
void myReshape(int w, int h) {

    // Original aspect ratio of viewport
    const float aspect_ratio = VIEW_WIDTH / VIEW_HEIGHT;

    float scale;
    // If AR is smaller -> window less wide / taller so need to reshape keeping in mind width
    // If AR is higher -> window wider / less tall so need to reshape keeping in mind height
    scale = (float)w / (float)h < aspect_ratio
        ? (float)w / VIEW_WIDTH
        : (float)h / VIEW_HEIGHT;

    float margin_x = (w - VIEW_WIDTH * scale) / 2;
    float margin_y = (h - VIEW_HEIGHT * scale) / 2;

    glViewport(margin_x, margin_y, VIEW_WIDTH * scale, VIEW_HEIGHT * scale);
}

// Display function to render the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear the color buffer

    // Draw scene
    Renderer::instance()->drawScene(game);

    glutSwapBuffers();  // Swap the front and back buffers to display the rendered image
}

// Keyboard input handling function for movement
void handleInputSpecialKeys(int key, int x, int y) {
    int moves;
    switch (key) {
    case GLUT_KEY_UP:
        // Move character up
        moves = game.movePlayer(0, STEP); 
        Camera::instance()->moveCamera(0, 0, STEP * moves);
        break;
    case GLUT_KEY_LEFT:
        // Move character left
        moves = game.movePlayer(STEP, 0);
        Camera::instance()->moveCamera(STEP * moves, 0, 0);
        break;
    case GLUT_KEY_RIGHT:
        // Move character right
        moves = game.movePlayer(-STEP, 0);
        Camera::instance()->moveCamera(-STEP * moves, 0, 0);
        break;
    case GLUT_KEY_DOWN:
        // Move character down
        moves = game.movePlayer(0, -STEP); 
        Camera::instance()->moveCamera(0, 0, -STEP * moves);
        break;
    default:
        break;
    }
}

// AZERTY camera control - to change
void handleInputCharKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 'p':
        game.toggleCheatMode();
        break;
    case 'v':
        Camera::instance()->toggleViewMode();
        break;
    case 'r':
        Renderer::instance()->toggleRenderingMode();
        break;
    case 'w':
        Camera::instance()->moveCameraOnInput(0, 0, 5);
        break;
    case 's':
        Camera::instance()->moveCameraOnInput(0, 0, -5);
        break;
    case 'a':
        Camera::instance()->moveCameraOnInput(5, 0, 0);
        break;
    case 'd':
        Camera::instance()->moveCameraOnInput(-5, 0, 0);
        break;
    case 'z':
        Camera::instance()->moveCameraOnInput(0, 5, 0);
        break;
    case ' ':
        Camera::instance()->moveCameraOnInput(0, -5, 0);
        break;
    case 'c':
        Camera::instance()->resetInputOffset();
        break;
    case 'x':
        Renderer::instance()->toggleShadingMode();
        break;
    case 't':
        Renderer::instance()->toggleTexturing();
        break;
    case 'n':
        Renderer::instance()->toggleNormalMapping();
        break;
    default:
        break;
    }
}


// Timer update function with a single int parameter
void timerUpdate(int value) {
    game.update();  // Call the update function

    glutTimerFunc(DELTA_TIME, timerUpdate, 0);  // Call timerUpdate function every 10 milliseconds
}

// Idle GLUT callback func
void update() {
    game.update();
}

int main(int argc, char** argv)
{
    // INITIALIZATION of OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Crossy Roads!");
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // INITIALIZATION of GLEW
    GLenum err = glewInit();
    if (err) {
        std::cout << "GLEW Init failed" << std::endl;
    }

    // INITIALIZATION of instances
    game.init();
    Renderer::instance()->buildWorld(game);
    
    // INITIALIZATION of glut Loop 
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutSpecialFunc(handleInputSpecialKeys);
    glutKeyboardFunc(handleInputCharKeys);
    glutTimerFunc(0, timerUpdate, 0);  // Call timerUpdate function immediately and set up timer

    // Update loop
    glutMainLoop();

    return 0;
}