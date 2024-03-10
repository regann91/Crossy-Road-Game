# CSED451 - Assignment 1 (Crossy Road Game)

Our rendition of the popular arcade game, Crossy Road.

You can move your character using the arrow keys (Up, Right, Left, Down).


## Authors

- [@regan91](https://www.github.com/regan91)
- [@Emy-En](https://www.github.com/Emy-En)

## Project environment

- Visual Studio 2019 
- the OpenGL (4.6) libraries provided in the initial setup (FreeGLUT 3.0.0, GLEW 2.1.0, GLM 0.9.9.7). 

## Project structure

- The *main* file manages the initialization and the looping of the OpenGL program and game.
- The *GameObject* class is a general class that helps rendering simple colored quads
- The *Character* class is a specialization of GameObject and represents the player character. It computes collisions and player movement.
- The *Game* class manages the rendition of all GameObjects (trees, moving objects/cars).
- The *Way* class manages both Roads and Rivers, and generates randomly the cars on them
- The MovingObject class (cars) manages the movement of said cars when time passes

