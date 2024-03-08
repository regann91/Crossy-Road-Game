#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Character.h"
#include "Road.h"
#include "Tree.h"
#include "Car.h"
#include "River.h"

// Example instances of game objects
Road road1(150.0);
Road road2(600.0);
River river1(0.0, 450.0, 400.0);
River river2(450.0, 450.0, 350.0);
Character player(400.0, 50.0, 50.0, 50.0);  // Initialize the player character
Tree tree1(100.0, 350.0, 35.0, 50.0);  // Initialize a tree
Tree tree2(100.0, 750.0, 35.0, 50.0);
Tree tree3(250.0, 300.0, 35.0, 50.0);
Tree tree4(250.0, 550.0, 35.0, 50.0);
Tree tree5(350.0, 400.0, 35.0, 50.0);
Tree tree6(450.0, 250.0, 35.0, 50.0);
Tree tree7(500.0, 700.0, 35.0, 50.0);
Tree tree8(550.0, 100.0, 35.0, 50.0);
Tree tree9(600.0, 350.0, 35.0, 50.0);
Tree tree10(700.0, 300.0, 35.0, 50.0);
std::vector<Tree> trees = { tree1, tree2, tree3, tree4, tree5, tree6, tree7, tree8, tree9, tree10 };



 
// Initialization function
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set the clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 800);  // Set up a 2D orthographic view

    road1.initCars();
    road2.initCars();
}

// Display function to render the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    road1.draw();   // Render the road
    road2.draw();
    river1.draw();
    river2.draw();
    for (const auto& tree : trees) {
        tree.draw();
    }
    player.draw();  // Render the character

    // Check for collision with cars on road 1
    for (const auto& car : road1.cars) {
        if (player.collidesWith(car)) {
            std::cout << "Game Over! You collided with a car on road 1." << std::endl;
            exit(0);  // Terminate the game
        }
    }

    // Check for collision with cars on road 2
    for (const auto& car : road2.cars) {
        if (player.collidesWith(car)) {
            std::cout << "Game Over! You collided with a car on road 2." << std::endl;
            exit(0);  // Terminate the game
        }
    }

    // Check for collision with river (falling into water)
    if (player.collidesWith(river1) || player.collidesWith(river2)) {
        std::cout << "Game Over! You fell into the river." << std::endl;
        exit(0);
    }

    glutSwapBuffers();  // Swap the front and back buffers to display the rendered image
}

// Update function for game logic (e.g., character and car movement, collision detection)
void update() {

    road1.update();  // Update cars on road 1
    road2.update();  // Update cars on road 2

    if (player.getY() >= 750.0) {
        std::cout << "Congratulations! You won the game!" << std::endl;
        exit(0);  
    }

    glutPostRedisplay();
}

// Timer update function with a single int parameter
void timerUpdate(int value) {
    update();  // Call the update function

    glutTimerFunc(10, timerUpdate, 0);  // Call timerUpdate function every 10 milliseconds
}

// Keyboard input handling function
void specialKeys(int key, int x, int y) {
    const float moveStep = 50.0;  // Adjust the step size as needed

    switch (key) {
    case GLUT_KEY_UP:
        player.move(0, moveStep);  // Move character up
        break;
    case GLUT_KEY_LEFT:
        player.move(-moveStep, 0);  // Move character left
        break;
    case GLUT_KEY_RIGHT:
        player.move(moveStep, 0);  // Move character right
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
    glutInitWindowSize(800, 600);  // Set the initial window size

    init();  // Call the init function to set up OpenGL

    // Register the display, update, and keyboard functions
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutTimerFunc(0, timerUpdate, 0);  // Call timerUpdate function immediately and set up timer
    glutSpecialFunc(specialKeys);
    glutMainLoop();  // Enter the GLUT main loop

    return 0;
}
