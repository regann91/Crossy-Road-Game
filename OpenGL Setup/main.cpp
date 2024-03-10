#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Character.h"
#include "Game.h"
#include "Tree.h"
#include "Way.h"
#include "TextureManager.h"

Game game;
Character player;
 
// Initialization function
void init() {
    glClearColor(0, 0, 0, 0);  // Set the clear color to white
    game.init();
    Character player = Character();
    player.updateCamera();
}

// Display function to render the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    glClearColor(0.3, 0.34, 0.53, 0);
    game.drawObjects();
    player.draw();

    glutSwapBuffers();  // Swap the front and back buffers to display the rendered image
}

// Reshape function, allows to keep aspect ratio
void myReshape(int w, int h) {

    // Original aspect ratio of viewport
    const float aspect_ratio = (float)WIDTH / (float)HEIGHT;

    float scale;
    // If AR is smaller -> window less wide / taller so need to reshape keeping in mind width
    // If AR is higher -> window wider / less tall so need to reshape keeping in mind height
    scale = (float)w / (float)h < aspect_ratio
        ? (float)w / (float)WIDTH
        : (float)h / (float)HEIGHT;


    float margin_x = (w - WIDTH * scale) / 2;
    float margin_y = (h - HEIGHT * scale) / 2;

    glViewport(margin_x, margin_y, WIDTH * scale, HEIGHT * scale);
}

// Update function for game logic (e.g., character and car movement, collision detection)
void update() {
    // Update all ways (moving boulders and trunks)
    game.updateWays();

    // Collision check from ways
    auto ways = game.getWays();

    // if player enters a way then 
    for (std::shared_ptr<Way> way : ways) {
        if (way->collided(player)) {
            std::cout << "You lost the game :(" << std::endl;
            exit(0);
        }
    }

    if (player.getY() >= 950) {
        std::cout << "Congratulations! You won the game!" << std::endl;
        exit(0);  
    }

    glutPostRedisplay();
}

// Timer update function with a single int parameter
void timerUpdate(int value) {
    update();  // Call the update function

    glutTimerFunc(DELTA_TIME, timerUpdate, 0);  // Call timerUpdate function every 10 milliseconds
}

// Tree checking
bool anyTreeCollided() {
    auto trees = game.getTrees();
    for (Tree tree : trees) {
        if (player.collidesWith(tree)) return true;
    }
    return false;
}

// Keyboard input handling function
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        player.move(0, MOVESTEP);  // Move character left
        if(anyTreeCollided()) player.move(0, -MOVESTEP);
        break;
    case GLUT_KEY_LEFT:
        player.move( -MOVESTEP/2, 0);  // Move character left
        if (anyTreeCollided()) player.move(MOVESTEP/2, 0);
        break;
    case GLUT_KEY_RIGHT:
        player.move( MOVESTEP/2, 0);  // Move character right
        if (anyTreeCollided()) player.move(-MOVESTEP/2, 0);
        break;
    case GLUT_KEY_DOWN:
        player.move( 0, -MOVESTEP);  // Move character down
        if (anyTreeCollided()) player.move(0, MOVESTEP);
        break;
    default:
        break;
    }

    glutPostRedisplay();  // Request a redraw to update the display
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Set up the display mode
    
    glutCreateWindow("Crossy Road Game");  // Create a window with the specified title
    glutInitWindowSize(WIDTH, HEIGHT);  // Set the initial window size

    init();  // Call the init function to set up OpenGL

    // Register the display, update, and keyboard functions
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutIdleFunc(update);
    glutTimerFunc(0, timerUpdate, 0);  // Call timerUpdate function immediately and set up timer
    glutSpecialFunc(specialKeys);
    glutMainLoop();  // Enter the GLUT main loop

    return 0;
}
