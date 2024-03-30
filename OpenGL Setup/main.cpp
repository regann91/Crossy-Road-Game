#include <GL/glew.h>
#include <gl/glut.h>
#include <iostream>

#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include "Character.h"

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
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    game.drawScene();

    glutSwapBuffers();  // Swap the front and back buffers to display the rendered image
}


// Keyboard input handling function
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        game.movePlayer(0, STEP);  // Move character up
        break;
    case GLUT_KEY_LEFT:
        game.movePlayer(-STEP, 0);  // Move character left
        break;
    case GLUT_KEY_RIGHT:
        game.movePlayer(STEP, 0);  // Move character right
        break;
    case GLUT_KEY_DOWN:
        game.movePlayer(0, -STEP);  // Move character down
        break;
    default:
        break;
    }
}

void asciiKeys(unsigned char key, int x, int y) {
    game.handleInput(static_cast<char>(key));
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
    // Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Crossy Roads!");
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Init of GLEW
    GLenum err = glewInit();
    if (err) {
        std::cout << "GLEW Init failed" << std::endl;
    }

    game.init();
    
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(asciiKeys);
    glutTimerFunc(0, timerUpdate, 0);  // Call timerUpdate function immediately and set up timer
    // Update loop
    glutMainLoop();

    return 0;
}