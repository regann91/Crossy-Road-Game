# CSED451 - Assignment 1 (Crossy Road Game)

Our rendition of the popular arcade game, Crossy Road.

### Controls
You can move your character using the arrow keys (Up, Right, Left, Down).

### How to play
Your goal is to get to the flag across the rivers and roads! You can collect coins on the way, as well as special power-up shoes that boost your speed! But make sure not to get hit by a vehicle, nor to fall in the river on the way!!


## Authors

- [@regan91](https://www.github.com/regan91)
- [@Emy-En](https://www.github.com/Emy-En)

## Project environment

- Visual Studio 2019 
- the OpenGL (4.6) libraries provided in the initial setup (FreeGLUT 3.0.0, GLEW 2.1.0, GLM 0.9.9.7). 

## Project structure

### Game loop
- The *main* file manages the initialization and the looping of the OpenGL program and game.
- The *Game* class manages the rendering of all GameObjects (trees, moving objects/cars, player, collectibles), as well as manages game logic (collisions, timer updates, spawning of collectibles, game loop).

### Special classes
- The *TextureManager* is the instance who manages the loading and storage of OpenGL textures. It can load a specific format of 32-bit ARGB .bmp files.
- The *TextDisplayer* class is a class that manages the drawing of text on screen or in the world in a specific bitmap font.

### Game objects and rendering
- The *GameObject* class is a general class that helps rendering textured quads qna dkeeping track of game information (position...)

#### Player character
- The *Character* class is a specialization of GameObject and represents the player character. It possesses a few attributes of *BodyPart* and *GameObject* classes that make up the different parts of the character.
- The *BodyParts* class is a specialization of *GameObject* and manages the rendering of hierchical objects to the *Character*. It contains global rotation and position information as well as local, used for animation.
- The *Leg* and *Arm* classes are specializations of "BodyPart*, with special animations.

#### Collectibles
- The *Collectible* class is a specialization of *GameObject* and is used to generally represent collectible items and their behaviour when collected.
- The *Shoes* and *Coin* classes are specializations of *Collectible*, with the former being used as a Powerup who speeds up the player when active, and the second incrementing a game counter of collected coins.

#### Paths and moving objects
- The *Path* class is a general class that is used to render a 2 way path such as *Road* or a *River*. It manages the spawning of the different objects on top of it.
- The *Road* class is a specialization of the *Path*, where the player dies if in contact one of its moving objects (cars and trucks).
- The *River* class is a specialization of the *Path*, where the player dies if in contact with it and none of its moving objects (trunks).
- *The MovingObject* general class (cars) manages the movement of said cars when time passes.
- The *MovingObjectRiver* and *MovingObjectRoad* classes are specializations of *MovingObject* with special rendering, the latter being hierarchical.
*

#### Obstacles
- The *Tree* class is a specialization of *GameObject* and represents trees, a typical obstacle of the game that prevents player movement when collided.
