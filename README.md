# CSED451 - Assignment 4  (Crossy Road Game)

Our rendition of the popular arcade game, Crossy Road.

### Controls
You can move your character using the arrow keys (Up, Right, Left, Down). 
You can also move the camera using W, A, S, D, Z, Space (Forward, Left, Backwards, Right, Up, Down).

Pressing C reinitializes camera position.
Pressing R allows changing between different rendering modes (Color, Wireframe, Wireframe with hidden face removal).
Pressing V changes the viewing mode (Third person, First person, Side view, Above view).
Pressing X allows toggling between Gouraud & Phong shading.
Pressing T will toggle the application of diffuse texture mapping on and off.
Pressing N will toggle the application of normal mapping on and off.
Pressing P will activate cheat mode, allowing the character to pass through obstacles and not die when colliding with a car or the water.

### How to play
Your goal is to get to the flag across the rivers and roads! You can collect coins on the way, as well as special power-up shoes that boost your speed! But make sure not to get hit by a vehicle, nor to fall in the river on the way!!


## Authors

- [@regann91](https://www.github.com/regann91)
- [@Emy-En](https://www.github.com/Emy-En)

## Project environment

- Visual Studio 2019 
- the OpenGL (4.6) libraries provided in the initial setup (FreeGLUT 3.0.0, GLEW 2.1.0, GLM 0.9.9.7). 

## Project structure

### Game loop and rendering pipeline
- The *main* file manages the initialization and the looping of the OpenGL program and game.
- The *Game* class manages the creation and updating of all GameObjects (trees, moving objects/cars, player, collectibles), as well as manages game logic (collisions, timer updates, spawning of collectibles, game loop).
- The *Renderer* class manages the creation and rendering of the vicual world the game is taking place in.
- The *Camera* class keeps track for the Renderer of the projection and view matrices

### Special classes
- The *TextureManager* is the instance who manages the loading and storage of OpenGL textures. It can load a specific format of 32-bit ARGB .bmp files [UNUSED]
- The *MeshManager*  is the instance who manages the loading and storage of OpenGL VAO information. It can load meshes from .obj files or create one from a list of vertices and indices.
- The *ShaderManager*  is the instance who manages the loading and storage of OpenGL shader information. It can load GLSL shaders composed of a vertex.glsl and a fragment.glsl.
- The *TextDisplayer* class is a class that manages the drawing of text on screen or in the world in a specific bitmap font [UNUSED]

### Game objects
- The *GameObject* class is a general class that helps keeping track of game and rendering information (position, dimensions...).
- The *Renderable* class is a general class that helps the renderer with the drawing of a mesh and its information.

#### Player character
- The *Character* class is a specialization of GameObject and represents the player character. 

#### Collectibles
- The *Collectible* class is a specialization of *GameObject* and is used to generally represent collectible items and their behaviour when collected.
- The *Shoes* and *Coin* classes are specializations of *Collectible*, with the former being used as a Powerup who speeds up the player when active, and the second incrementing a game counter of collected coins.

#### Paths and moving objects
- The *Path* class is a general class that is used to render a 2 way path such as *Road* or a *River*. It manages the spawning of the different objects on top of it.
- The *Road* class is a specialization of the *Path*, where the player dies if in contact one of its moving objects (cars and trucks).
- The *River* class is a specialization of the *Path*, where the player dies if in contact with it and none of its moving objects (trunks).
- *The MovingObject* general class manages the movement of said cars and trunks when time passes.

#### Obstacles
- The *Tree* class is a specialization of *GameObject* and represents trees, a typical obstacle of the game that prevents player movement when collided.
